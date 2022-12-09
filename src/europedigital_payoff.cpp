#include <algorithm>
#include <cmath>
#include <europedigital_payoff.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

namespace LibOptions {

EuroDigitalPayoff::EuroDigitalPayoff(const EuroDigitalPayoffConfig& config)
    : d_config(config), payoff()
{}
std::vector<double>
EuroDigitalPayoff::calc_payoff(std::vector<std::vector<double>> path)
{
    for (int i = 0; i < path.size(); i++) {
        if (d_config.iscall) {
            payoff.push_back(
                path[i][path[i].size() - 1] > d_config.d_strikePrice ? 1.0
                                                                     : 0.0);
        }
        else {
            payoff.push_back(
                d_config.d_strikePrice > path[i][path[i].size() - 1] ? 1.0
                                                                     : 0.0);
        }
    }
    return payoff;
}
} // namespace LibOptions
