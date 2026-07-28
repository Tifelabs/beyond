#include "quant.hpp"
#include <iostream>

int main() {
    quant::Series<double> prices;
    for (double p : {100.0, 102.0, 101.0, 105.0, 103.0, 108.0, 107.0})
        prices.push(p);

    auto rets = prices.returns();
    std::cout << "mean return: " << rets.mean() << "\n";
    std::cout << "stddev: " << rets.stddev() << "\n";
    std::cout << "sharpe: " << rets.sharpe() << "\n";
    std::cout << "historical VaR 95%: " << rets.historicalVaR(0.95) << "\n";
    std::cout << "parametric VaR 99%: " << rets.parametricVaR(0.99) << "\n";

    quant::EMA<double> ema(0.3);
    for (double p : {100.0, 102.0, 101.0, 105.0}) ema.update(p);
    std::cout << "EMA: " << ema.get() << "\n";

    double f = quant::fractionalKelly<double>(0.55, 2.0, 1.0, 0.5);
    std::cout << "fractional kelly size: " << f << "\n";

    quant::BetaBelief<double> tokenSafety;
    tokenSafety.update(true);
    tokenSafety.update(true);
    tokenSafety.update(false);
    std::cout << "belief mean: " << tokenSafety.mean()
              << " var: " << tokenSafety.variance() << "\n";

    return 0;
}