#include <algorithm>
#include <bsm.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
namespace LibOptions {

BSMPath::BSMPath(const BSMConfig& config)
    : d_config(config), d_paths()
{}

std::vector<std::vector<double>> BSMPath::generateStockPaths() {
    double drift = d_config.d_origPrice
                  * exp((d_config.d_riskFreeRate - d_config.d_dividend
                         - 0.5 * pow(d_config.d_volatility, 2))
                        * d_config.d_time);
    // create a Mersenne Twister random number generator seeded by 1234
    std::mt19937 mt_rand(1234);
    std::normal_distribution<double> dis_standard_normal(
        0.0, sqrt(d_config.d_time));
    for (int i = 0; i < d_config.samplesize; i++) {
        std::vector<double> path = {};
        path.push_back(drift * exp(dis_standard_normal(mt_rand)*d_config.d_volatility));
        d_paths.push_back(path);
    }
    return d_paths;
}
void BSMPath::printPath() {
    for (int i = 0; i < d_paths.size(); i++) {
        std::cout << std::fixed;
        std::cout << std::setw(10);
        std::cout << d_paths[i][0] << " ";            
        std::cout << std::endl;
    }
}

}