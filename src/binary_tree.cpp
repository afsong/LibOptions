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
              
    double d = 1 / mu;
    double P = (exp(d_config.d_riskFreeRate * d_config.d_numTimestamps
                    / d_config.d_numSteps)
                - d)
               / (mu - d);
    d_paths.push_back({});
    d_paths[0].push_back(d_config.d_origPrice * pow(d, d_config.d_numSteps));

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

} // namespace LibOptions
