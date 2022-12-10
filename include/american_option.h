#ifndef LIBOPTIONS_AMERICAN_OPTION_H
#define LIBOPTIONS_AMERICAN_OPTION_H

#include <vector>

namespace LibOptions {
class AmericanOption {};


struct AmericanOptionConfig{
    virtual ~AmericanOptionConfig() = default;
};

struct AmericanPutOptionConfig : AmericanOptionConfig{
    double K;
};

double OptionPayoff(int option, double S, double K);
double PutOptionPayoff(double S, double K);
double CallOptionPayoff(double S, double K);
//double AmericanOptionPayoff(const std::vector<std::vector<double>> stocksPricePaths,
//                            int timestamp,
//                            int option,
//                            AmericanOptionConfig &config);
//
//double AmericanPutOptionPayoff(const std::vector<std::vector<double>> stocksPricePaths,
//                               int timestamp,
//                               AmericanPutOptionConfig &config);

} // namespace LibOptions

#endif // LIBOPTIONS_AMERICAN_OPTION_H
