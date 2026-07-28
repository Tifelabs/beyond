#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace quant {

// generic time series stats, works with float/double/long double
template <typename T = double>
class Series {
    std::vector<T> data;

public:
    void push(T x) { data.push_back(x); }
    size_t size() const { return data.size(); }
    const std::vector<T>& raw() const { return data; }

    T mean() const {
        if (data.empty()) throw std::runtime_error("empty series");
        return std::accumulate(data.begin(), data.end(), T(0)) / data.size();
    }

    T variance() const {
        T m = mean();
        T sum = 0;
        for (auto x : data) sum += (x - m) * (x - m);
        return sum / (data.size() - 1);
    }

    T stddev() const { return std::sqrt(variance()); }

    // simple returns from a price series
    Series<T> returns() const {
        Series<T> r;
        for (size_t i = 1; i < data.size(); i++)
            r.push((data[i] - data[i-1]) / data[i-1]);
        return r;
    }

    T sharpe(T riskFreeRate = 0) const {
        return (mean() - riskFreeRate) / stddev();
    }

    // historical VaR at given confidence, e.g. 0.95
    T historicalVaR(T confidence) const {
        std::vector<T> sorted = data;
        std::sort(sorted.begin(), sorted.end());
        size_t idx = static_cast<size_t>((1 - confidence) * sorted.size());
        return -sorted[idx];
    }

    // parametric (Gaussian) VaR
    T parametricVaR(T confidence) const {
        static const T z95 = 1.645, z99 = 2.326;
        T z = (confidence >= 0.99) ? z99 : z95;
        return z * stddev() - mean();
    }
};

// exponential moving average, templated on numeric type
template <typename T = double>
class EMA {
    T alpha, value;
    bool initialized = false;

public:
    explicit EMA(T alpha_) : alpha(alpha_), value(0) {}

    T update(T x) {
        if (!initialized) { value = x; initialized = true; }
        else value = alpha * x + (1 - alpha) * value;
        return value;
    }

    T get() const { return value; }
};

// Kelly criterion sizing, templated so you can use float for speed or double for precision
template <typename T = double>
T kellyFraction(T winProb, T winPayoff, T lossPayoff) {
    if (lossPayoff <= 0) throw std::invalid_argument("lossPayoff must be positive");
    T b = winPayoff / lossPayoff;
    T f = winProb - (1 - winProb) / b;
    return std::max(T(0), f); // clamp negative kelly to 0
}

// fractional Kelly, scales down full Kelly for risk control
template <typename T = double>
T fractionalKelly(T winProb, T winPayoff, T lossPayoff, T fraction = 0.5) {
    return kellyFraction(winProb, winPayoff, lossPayoff) * fraction;
}

// Bayesian update for a Beta-distributed probability estimate (e.g. token "safety" score)
template <typename T = double>
struct BetaBelief {
    T alpha = 1, beta = 1; // uniform prior

    void update(bool success) {
        if (success) alpha += 1;
        else beta += 1;
    }

    T mean() const { return alpha / (alpha + beta); }

    T variance() const {
        T s = alpha + beta;
        return (alpha * beta) / (s * s * (s + 1));
    }
};

} // namespace quant