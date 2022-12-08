#include <algorithm>
#include <europevanilla_payoff.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>

namespace LibOptions {

EuroVanillaPayoff::EuroVanillaPayoff(const EuroVanillaPayoffConfig& config)
    : d_config(config), payoff()
{}
std::vector<double> EuroVanillaPayoff::calc_payoff(std::vector<std::vector<double>> path)
{
    for (int i = 0; i < path.size(); i++) {
        if (d_config.iscall) { 
            payoff.push_back(std::max(path[i][path[i].size() - 1]
                             - d_config.d_strikePrice,0.0));
        }
        else {
            payoff.push_back(std::max(d_config.d_strikePrice - path[i][path[i].size() - 1],0.0));
        }
    }
    return payoff;
}
}