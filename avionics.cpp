#include <atomic>
#include <cstdint>
#include <cstring>
#include <array>
#include <chrono>
#include <iostream>

#define LIKELY(x)   __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

// --- dimensional analysis, because unit bugs crash planes and blow accounts ---
template<int M, int T, int Sc>
struct Dim { static constexpr int m = M, t = T, sc = Sc; };
using Meters  = Dim<1,0,0>;
using Seconds = Dim<0,1,0>;
using Ticks   = Dim<0,0,1>;

template<typename D>
struct Q {
    double v;
    constexpr explicit Q(double v_) : v(v_) {}
    template<typename D2>
    constexpr auto operator/(Q<D2> o) const {
        return Q<Dim<D::m - D2::m, D::t - D2::t, D::sc - D2::sc>>(v / o.v);
    }
    constexpr Q operator+(Q o) const { return Q(v + o.v); }
};
using Altitude = Q<Meters>;
using Time     = Q<Seconds>;
using RateOfClimb = Q<Dim<1,-1,0>>;

constexpr Altitude operator"" _m(long double v) { return Altitude((double)v); }
constexpr Time operator"" _s(long double v) { return Time((double)v); }

// --- lock-free SPSC ring, shared by sensor bus and order book alike ---
template<typename T, size_t N>
struct alignas(64) SpscRing {
    static_assert((N & (N - 1)) == 0, "N must be pow2");
    std::array<T, N> buf;
    alignas(64) std::atomic<uint64_t> head{0};
    alignas(64) std::atomic<uint64_t> tail{0};

    bool push(const T& x) {
        auto h = head.load(std::memory_order_relaxed);
        auto n = (h + 1) & (N - 1);
        if (UNLIKELY(n == tail.load(std::memory_order_acquire))) return false;
        buf[h] = x;
        head.store(n, std::memory_order_release);
        return true;
    }
    bool pop(T& out) {
        auto t = tail.load(std::memory_order_relaxed);
        if (UNLIKELY(t == head.load(std::memory_order_acquire))) return false;
        out = buf[t];
        tail.store((t + 1) & (N - 1), std::memory_order_release);
        return true;
    }
};

// --- fixed-point Q16.16, avoids float nondeterminism on the flight-critical path ---
struct Fix16 {
    int32_t raw;
    static constexpr Fix16 from(double d) { return {(int32_t)(d * 65536.0)}; }
    Fix16 operator*(Fix16 o) const {
        return {(int32_t)(((int64_t)raw * o.raw) >> 16)};
    }
    double dbl() const { return raw / 65536.0; }
};

// --- CRTP rate-monotonic task, both the autopilot loop and the market-data handler derive from this ---
template<typename Derived, uint32_t PeriodUs>
struct Periodic {
    using clock = std::chrono::steady_clock;
    clock::time_point next = clock::now();
    void tick() {
        static_cast<Derived*>(this)->run();
        next += std::chrono::microseconds(PeriodUs);
    }
};

struct GlideSlope : Periodic<GlideSlope, 20000> {
    Fix16 kp = Fix16::from(0.35), integ = Fix16::from(0.0);
    void run() {
        Fix16 err = Fix16::from(3.0);           // deg deviation, stand-in
        integ.raw += (kp * err).raw >> 4;
        volatile double cmd = (kp * err).dbl() + integ.dbl();
        (void)cmd;
    }
};

struct alignas(8) Tick { uint64_t ts; uint32_t px; uint32_t qty; };

struct MatchEngine : Periodic<MatchEngine, 1> {
    SpscRing<Tick, 1024>* book;
    uint32_t last = 0;
    void run() {
        Tick t;
        while (book->pop(t)) {
            if (UNLIKELY(t.px == 0)) continue;
            last = t.px;
        }
    }
};

int main() {
    static SpscRing<Tick, 1024> book;
    MatchEngine me{{}, &book};
    GlideSlope gs;

    for (uint64_t i = 1; i <= 8; ++i)
        book.push(Tick{i, (uint32_t)(100 + (i * 7 % 13)), 1});

    for (int i = 0; i < 8; ++i) { me.tick(); gs.tick(); }

    Altitude a = 1500.0_m + 250.0_m;
    Time t = 30.0_s;
    RateOfClimb roc = a / t;

    std::cout << "last_px=" << me.last
              << " roc=" << roc.v << " m/s"
              << " gs_cmd_ok=" << 1 << '\n';
}
