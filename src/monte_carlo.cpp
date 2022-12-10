#include <iomanip>
#include <iostream>
#include <monte_carlo.h>
#include <random>
#include <vector>

#include <double_vector.h>

namespace LibOptions {

MonteCarloPath::MonteCarloPath(const MonteCarloConfig& config)
    : d_config(config), d_paths(d_config.d_numPaths, d_config.d_numTimestamps)
{}

void MonteCarloPath::generateStockPaths()
{
    // generate dW for stock price paths
    DoubleVector<double> dW(d_config.d_numPaths, d_config.d_numTimestamps);

    std::default_random_engine generator(d_config.seed);
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < d_config.d_numPaths; i++) {
        for (int j = 0; j < d_config.d_numTimestamps; j++) {
            dW.set(i, j, distribution(generator));
        }
    }

    double dt = d_config.d_time / d_config.d_numTimestamps;
    double price = d_config.d_origPrice;

    for (int i = 0; i < d_config.d_numPaths; i++) {
        for (int j = 0; j < d_config.d_numTimestamps; j++) {
            price += d_config.d_riskFreeRate * price * dt
                     + d_config.d_volatility * price * sqrt(dt) * dW.get(i, j);
            d_paths.set(i, j, price);
        }
        price = d_config.d_origPrice;
    }
}

void MonteCarloPath::printPath()
{
    for (int i = 0; i < d_paths.height(); i++) {
        for (int j = 0; j < d_paths.width(); j++) {
            std::cout << std::fixed;
            std::cout << std::setw(10);
            std::cout << d_paths.get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

} // namespace LibOptions
