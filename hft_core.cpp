// hft_core.cpp
// Build: g++ -std=c++20 -O3 -march=native -o hft_core hft_core.cpp -pthread
//
// Pipeline: market-data thread --(lock-free SPSC)--> strategy thread
// Demonstrates: cache-line alignment, no allocation/locks on the hot path,
// flat-array order book, tick-to-decision latency measurement.

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <random>
#include <thread>
#include <vector>

#ifdef __linux__
#include <pthread.h>
#include <sched.h>
#endif

constexpr size_t CACHELINE = 64;

static inline uint64_t now_ns() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::steady_clock::now().time_since_epoch()).count();
}

static void pin_thread(int core) {
#ifdef __linux__
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(core, &set);
    pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
#else
    (void)core;  // macOS has no hard affinity API
#endif
}

// ---------- Lock-free single-producer/single-consumer ring buffer ----------
template <typename T, size_t N>
class SPSCQueue {
    static_assert((N & (N - 1)) == 0, "N must be a power of two");
    alignas(CACHELINE) std::atomic<size_t> head_{0};  // consumer writes
    alignas(CACHELINE) std::atomic<size_t> tail_{0};  // producer writes
    alignas(CACHELINE) std::array<T, N> buf_;

public:
    bool push(const T& v) {
        size_t t = tail_.load(std::memory_order_relaxed);
        if (t - head_.load(std::memory_order_acquire) == N) return false;  // full
        buf_[t & (N - 1)] = v;
        tail_.store(t + 1, std::memory_order_release);
        return true;
    }
    bool pop(T& out) {
        size_t h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire)) return false;  // empty
        out = buf_[h & (N - 1)];
        head_.store(h + 1, std::memory_order_release);
        return true;
    }
};

// ---------- Market data ----------
enum Side : uint8_t { BID = 0, ASK = 1 };

struct MdUpdate {
    uint64_t ts_ns;  // when the update was "received"
    int32_t  price;  // in integer ticks
    int32_t  qty;    // 0 = remove level
    Side     side;
};

// ---------- Flat-array order book (price-indexed, no heap) ----------
struct Book {
    static constexpr int N = 4096;
    int32_t bid[N]{};
    int32_t ask[N]{};
    int best_bid = -1;
    int best_ask = N;

    void update(const MdUpdate& u) {
        if (u.side == BID) {
            // An aggressive bid sweeps resting asks at or below its price.
            for (int p = best_ask; p <= u.price && p < N; ++p) ask[p] = 0;
            while (best_ask < N && ask[best_ask] == 0) ++best_ask;

            bid[u.price] = u.qty;
            if (u.qty > 0) {
                best_bid = std::max(best_bid, u.price);
            } else if (u.price == best_bid) {
                while (best_bid >= 0 && bid[best_bid] == 0) --best_bid;
            }
        } else {
            for (int p = u.price; p <= best_bid; ++p) bid[p] = 0;
            while (best_bid >= 0 && bid[best_bid] == 0) --best_bid;

            ask[u.price] = u.qty;
            if (u.qty > 0) {
                best_ask = std::min(best_ask, u.price);
            } else if (u.price == best_ask) {
                while (best_ask < N && ask[best_ask] == 0) ++best_ask;
            }
        }
    }
    bool valid() const { return best_bid >= 0 && best_ask < N; }
    int spread() const { return best_ask - best_bid; }
};

// ---------- Simple market-making strategy ----------
// Quotes one tick inside the touch when the spread is wide enough.
struct Strategy {
    int my_bid = -1, my_ask = -1;
    uint64_t quotes_sent = 0;

    void on_book(const Book& b) {
        if (!b.valid() || b.spread() < 3) return;
        int new_bid = b.best_bid + 1;
        int new_ask = b.best_ask - 1;
        if (new_bid != my_bid || new_ask != my_ask) {
            my_bid = new_bid;
            my_ask = new_ask;
            ++quotes_sent;  // real system: encode + send order to gateway here
        }
    }
};

// ---------- Simulated feed (random-walk around a drifting mid) ----------
static void feed_thread(SPSCQueue<MdUpdate, 1 << 16>& q, uint64_t count) {
    pin_thread(1);
    std::mt19937 rng(42);
    int mid = 2048;
    for (uint64_t i = 0; i < count; ++i) {
        if (rng() % 8 == 0) mid = std::clamp(mid + (int)(rng() % 3) - 1, 500, 3500);
        int off = 1 + rng() % 10;
        MdUpdate u;
        u.side = (rng() & 1) ? ASK : BID;
        u.price = (u.side == BID) ? mid - off : mid + off;
        u.qty = (rng() % 4 == 0) ? 0 : 1 + rng() % 500;
        u.ts_ns = now_ns();
        while (!q.push(u)) { /* spin: queue full */ }
    }
}

int main() {
    constexpr uint64_t TICKS = 5'000'000;
    static SPSCQueue<MdUpdate, 1 << 16> queue;

    std::vector<uint32_t> lat;
    lat.reserve(TICKS);  // preallocate: no malloc on the hot path

    Book book;
    Strategy strat;

    std::thread feed(feed_thread, std::ref(queue), TICKS);
    pin_thread(2);

    uint64_t processed = 0;
    MdUpdate u;
    const uint64_t t0 = now_ns();
    while (processed < TICKS) {
        if (!queue.pop(u)) continue;  // busy-poll, never sleep
        book.update(u);
        strat.on_book(book);
        lat.push_back((uint32_t)(now_ns() - u.ts_ns));
        ++processed;
    }
    const double secs = (now_ns() - t0) / 1e9;
    feed.join();

    std::sort(lat.begin(), lat.end());
    auto pct = [&](double p) { return lat[(size_t)(p * (lat.size() - 1))]; };

    std::printf("ticks:        %llu (%.2f M/s)\n", (unsigned long long)processed, processed / secs / 1e6);
    std::printf("quotes sent:  %llu\n", (unsigned long long)strat.quotes_sent);
    std::printf("queue->decision latency (ns): p50=%u p99=%u p99.9=%u max=%u\n",
                pct(0.50), pct(0.99), pct(0.999), lat.back());
    return 0;
}
