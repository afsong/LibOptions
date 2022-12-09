#include <algorithm>
#include <binary_tree.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
namespace LibOptions {
BinaryTreePath::BinaryTreePath(const BinaryTreeConfig& config)
    : d_config(config), d_paths()
{}

std::vector<std::vector<double>> BinaryTreePath::generateStockPaths()
{
    double mu = exp(d_config.d_volatility
                    * sqrt(d_config.d_numTimestamps / d_config.d_numSteps));
    d_statusFlg = 1;
    d_d = 1 / mu;

    d_p = (exp(d_config.d_riskFreeRate * d_config.d_numTimestamps
               / d_config.d_numSteps)
           - d_d)
          / (mu - d_d);

    d_paths.push_back({});
    d_paths[0].push_back(d_config.d_origPrice * pow(d_d, d_config.d_numSteps));

    for (int i = 1; i < d_config.d_numSteps + 1; i++) {
        d_paths[0].push_back(d_paths[0][i - 1] * pow(mu, 2));
    }

    return d_paths;
}

void BinaryTreePath::printPath()
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

double BinaryTreePath::europecall()
{
    if (!d_statusFlg) { generateStockPaths(); }
    std::vector<double> values;
    values.push_back(std::max(d_paths[0][0] - d_config.d_strikePrice, 0.0));
    for (int i = 0; i < d_paths.size(); i++) {
        for (int j = 1; j < d_paths[i].size(); j++) {
            values.push_back(
                std::max(d_paths[i][j] - d_config.d_strikePrice, 0.0));
        }
    }
    for (int i = d_paths.size() - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            values[j] = (d_p * values[j + 1] + (1 - d_p) * values[j])
                        * exp(-d_config.d_riskFreeRate
                              * d_config.d_numTimestamps / d_config.d_numSteps);
        }
    }
    return values[0];
}

double BinaryTreePath::europeput()
{
    if (!d_statusFlg) { generateStockPaths(); }
    std::vector<double> values;
    values.push_back(std::max(d_config.d_strikePrice - d_paths[0][0], 0.0));
    for (int i = 0; i < d_paths.size(); i++) {
        for (int j = 1; j < d_paths[i].size(); j++) {
            values.push_back(
                std::max(d_config.d_strikePrice - d_paths[i][j], 0.0));
        }
    }
    for (int i = d_paths.size() - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            values[j] = (d_p * values[j + 1] + (1 - d_p) * values[j])
                        * exp(-d_config.d_riskFreeRate
                              * d_config.d_numTimestamps / d_config.d_numSteps);
        }
    }
    return values[0];
}

double BinaryTreePath::americall()
{
    if (!d_statusFlg) { generateStockPaths(); }
    std::vector<double> values;
    std::vector<double> prices = d_paths[0];

    values.push_back(std::max(prices[0] - d_config.d_strikePrice, 0.0));
    for (int i = 0; i < d_paths.size(); i++) {
        for (int j = 1; j < d_paths[i].size(); j++) {
            values.push_back(
                std::max(d_paths[i][j] - d_config.d_strikePrice, 0.0));
        }
    }

    for (int i = d_paths.size() - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            prices[j] = prices[j + 1] * d_d;
            values[j] = std::max(
                (d_p * values[j + 1] + (1 - d_p) * values[j])
                    * exp(-d_config.d_riskFreeRate * d_config.d_numTimestamps
                          / d_config.d_numSteps),
                prices[j] - d_config.d_strikePrice);
        }
    }
    return values[0];
}

double BinaryTreePath::ameriput()
{
    if (!d_statusFlg) { generateStockPaths(); }
    std::vector<double> values;
    std::vector<double> prices = d_paths[0];
    values.push_back(std::max(d_config.d_strikePrice - prices[0], 0.0));
    for (int i = 0; i < d_paths.size(); i++) {
        for (int j = 1; j < d_paths[i].size(); j++) {
            values.push_back(
                std::max(d_config.d_strikePrice - d_paths[i][j], 0.0));
        }
    }

    for (int i = d_paths.size() - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            prices[j] = prices[j + 1] * d_d;
            values[j] = std::max(
                (d_p * values[j + 1] + (1 - d_p) * values[j])
                    * exp(-d_config.d_riskFreeRate * d_config.d_numTimestamps
                          / d_config.d_numSteps),
                d_config.d_strikePrice - prices[j]);
        }
    }
    return values[0];
}

} // namespace LibOptions
