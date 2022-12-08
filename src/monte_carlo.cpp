#include <iomanip>
#include <iostream>
#include <monte_carlo.h>
#include <random>
#include <vector>

namespace LibOptions {

MonteCarloPath::MonteCarloPath(const MonteCarloConfig& config)
    : d_config(config), d_paths()
{}

std::vector<std::vector<double>> MonteCarloPath::generateStockPaths()
{
    // generate dW for stock price paths
    std::vector<std::vector<double>> dW;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < d_config.d_numPaths; i++) {
        dW.push_back({});
        for (int j = 0; j < d_config.d_numTimestamps; j++) {
            dW[i].push_back(distribution(generator));
        }
    }

    double dt = d_config.d_time / d_config.d_numTimestamps;
    double price = d_config.d_origPrice;

    for (int i = 0; i < d_config.d_numPaths; i++) {
        d_paths.push_back({});
        for (int j = 0; j < d_config.d_numTimestamps; j++) {
            price += d_config.d_riskFreeRate * price * dt
                     + d_config.d_volatility * price * sqrt(dt) * dW[i][j];
            d_paths[i].push_back(price);
        }
        price = d_config.d_origPrice;
    }

    return d_paths;
}

void MonteCarloPath::printPath()
{
    for (int i = 0; i < d_paths.size(); i++) {
        for (int j = 0; j < d_paths[i].size(); j++) {
            std::cout << std::fixed;
            std::cout << std::setw(10);
            std::cout << d_paths[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

} // namespace LibOptions
