#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>

template <typename T>
static T clampVal(T v, T lo, T hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

struct Lane {
    std::string name;
    std::atomic<int> queueLen{0};
    std::atomic<int> served{0};
    int arrivalRatePerMin = 0;

    Lane(std::string n, int rate) : name(std::move(n)), arrivalRatePerMin(rate) {}
};

static std::mutex coutMutex;
static std::atomic<bool> running{true};

static std::string rgb(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}
static std::string reset() { return "\033[0m"; }
static std::string severityColor(int q) {
    int r = clampVal(q * 12, 0, 255);
    int g = clampVal(255 - q * 12, 0, 255);
    return rgb(r, g, 40);
}

void arrivalWorker(Lane* lane, int simSpeed) {
    std::random_device rd;
    std::mt19937 rng(rd() ^ static_cast<unsigned>(
        std::hash<std::thread::id>{}(std::this_thread::get_id())));

    while (running.load(std::memory_order_relaxed)) {
        double meanMs = 60000.0 / std::max(1, lane->arrivalRatePerMin) / simSpeed;
        std::exponential_distribution<double> interArrival(1.0 / meanMs);
        int waitMs = static_cast<int>(clampVal(interArrival(rng), 5.0, 5000.0));
        std::this_thread::sleep_for(std::chrono::milliseconds(waitMs));
        if (!running.load(std::memory_order_relaxed)) break;
        lane->queueLen.fetch_add(1, std::memory_order_relaxed);
    }
}

class TrafficController {
public:
    TrafficController(std::vector<std::unique_ptr<Lane>> lanes,
                       int minGreenSec, int maxGreenSec, int satFlowPerHr, int simSpeed)
        : lanes_(std::move(lanes)), minGreen_(minGreenSec), maxGreen_(maxGreenSec),
          satFlow_(satFlowPerHr), simSpeed_(simSpeed) {
        for (auto& l : lanes_)
            arrivalThreads_.emplace_back(arrivalWorker, l.get(), simSpeed_);
    }

    ~TrafficController() {
        running.store(false, std::memory_order_relaxed);
        for (auto& t : arrivalThreads_)
            if (t.joinable()) t.join();
    }

    void run(int cycles) {
        for (int i = 0; i < cycles && running.load(); ++i) step();
    }

private:
    std::vector<std::unique_ptr<Lane>> lanes_;
    std::vector<std::thread> arrivalThreads_;
    int minGreen_, maxGreen_, satFlow_, simSpeed_;
    int cycle_ = 0;
    std::unordered_map<int, int> lastServed_;

    void step() {
        int idx = pickNextLane();
        int green = allocateGreen(idx);
        ++cycle_;
        log(idx, green, /*phase=*/"GREEN");
        serveDuring(idx, green);
        lastServed_[idx] = cycle_;
    }

    int pickNextLane() {
        int best = 0;
        double bestScore = -1.0;
        for (size_t i = 0; i < lanes_.size(); ++i) {
            int waitedCycles = cycle_ - lastServed_[static_cast<int>(i)];
            double waitFactor = 1.0 + 0.08 * waitedCycles;
            double score = lanes_[i]->queueLen.load(std::memory_order_relaxed) * waitFactor;
            if (score > bestScore) {
                bestScore = score;
                best = static_cast<int>(i);
            }
        }
        return best;
    }

    int allocateGreen(int idx) {
        int demand = lanes_[idx]->queueLen.load(std::memory_order_relaxed);
        int needed = (demand * 3600) / std::max(1, satFlow_);
        return clampVal(needed, minGreen_, maxGreen_);
    }

    void serveDuring(int idx, int greenSec) {
        Lane* lane = lanes_[idx].get();
        double capacityPerStep = static_cast<double>(satFlow_) / 3600.0;
        double carry = 0.0;
        int stepMs = std::max(1, (1000 / std::max(1, simSpeed_)));

        for (int s = 0; s < greenSec && running.load(); ++s) {
            std::this_thread::sleep_for(std::chrono::milliseconds(stepMs));
            carry += capacityPerStep;
            int wholeVehicles = static_cast<int>(carry);
            if (wholeVehicles > 0) {
                int current = lane->queueLen.load(std::memory_order_relaxed);
                int cleared = std::min(wholeVehicles, current);
                if (cleared > 0) {
                    lane->queueLen.fetch_sub(cleared, std::memory_order_relaxed);
                    lane->served.fetch_add(cleared, std::memory_order_relaxed);
                }
                carry -= wholeVehicles;
            }
        }
    }

    void log(int idx, int green, const char* phase) const {
        std::lock_guard<std::mutex> lk(coutMutex);
        std::cout << rgb(80, 160, 255) << "cycle " << cycle_ << reset()
                  << " -> " << rgb(255, 200, 60) << lanes_[idx]->name << reset()
                  << " " << phase << " " << green << "s"
                  << " queue=" << lanes_[idx]->queueLen.load();
        for (const auto& l : lanes_) {
            if (l->name != lanes_[idx]->name) {
                int q = l->queueLen.load(std::memory_order_relaxed);
                std::cout << " | " << l->name << ":" << severityColor(q) << q << reset();
            }
        }
        std::cout << '\n';
    }
};

int main() {
    std::vector<std::unique_ptr<Lane>> lanes;
    lanes.push_back(std::make_unique<Lane>("North", 12));
    lanes.push_back(std::make_unique<Lane>("South", 9));
    lanes.push_back(std::make_unique<Lane>("East",  15));
    lanes.push_back(std::make_unique<Lane>("West",  6));

    TrafficController controller(std::move(lanes),
        /*minGreen*/10, /*maxGreen*/45, /*satFlowPerHr*/1800, /*simSpeed*/20);
    controller.run(15);
    return 0;
}