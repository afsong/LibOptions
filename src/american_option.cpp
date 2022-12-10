#include <iostream>
#include <algorithm>
#include <vector>
#include <american_option.h>
#include <cmath>

namespace LibOptions {

double OptionPayoff(int option, double S, double K) {
    if (option == 1) {
        return PutOptionPayoff(S, K);
    } else {
        return CallOptionPayoff(S, K);
    }
}

double PutOptionPayoff(double S, double K)
{
    return std::max(K - S, 0.0);
}

double CallOptionPayoff(double S, double K)
{
    return std::max(S - K, 0.0);
}

//double AmericanOptionPayoff(const std::vector<std::vector<double>> stocksPricePaths,
//                            int timestamp,
//                            int option,
//                            AmericanOptionConfig &config)
//{
//    if (option == 1) {
//        AmericanPutOptionConfig *americanPutOptionConfig = dynamic_cast<AmericanPutOptionConfig*>(&config);
//        AmericanPutOptionPayoff(stocksPricePaths, timestamp, *americanPutOptionConfig);
//    }
//
//}
//
//double AmericanPutOptionPayoff(const std::vector<std::vector<double>> stocksPricePaths,
//                               int timestamp,
//                               AmericanPutOptionConfig &config)
//{
//    double S = stocksPricePaths.at(0).at(timestamp);
//    double K = config.K;
//    std::cout << K << std::endl;
//    return std::max(result, 0.0);
//}

} // namespace LibOptions
