#include <algorithm>
#include <europevanilla_model.h>
#include <bsm.h>
#include <europevanilla_payoff.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>

namespace LibOptions {

EuropeVanillaModel::EuropeVanillaModel(const EuropeVanillaModelConfig& config)
    : d_config(config)
{}
double EuropeVanillaModel::calc_value() {
    std::vector<std::vector<double>> paths;
    std::vector<double> payoffs;
    if (d_config.pricingmodeltype == "bsm") { 
        BSMConfig config;
        config.d_origPrice=d_config.d_origPrice;
        config.d_volatility = d_config.d_volatility;
        config.d_riskFreeRate = d_config.d_riskFreeRate;
        config.d_strikePrice=d_config.d_strikePrice;
        config.d_time=d_config.d_time;
        config.d_dividend=d_config.d_dividend;
        config.samplesize =d_config.samplesize;
        BSMPath bsmpath(config);
        paths = bsmpath.generateStockPaths();
        EuroVanillaPayoffConfig payoffconfig;
        payoffconfig.d_strikePrice=d_config.d_strikePrice;
        payoffconfig.iscall = d_config.iscall;
        EuroVanillaPayoff evpayoff(payoffconfig);
        payoffs = evpayoff.calc_payoff(paths);
        
    }
    else {
        throw new std::exception;
    }
    double sum = 0.0;
    double discount = exp(-d_config.d_riskFreeRate*d_config.d_time);
    for (int i = 0; i < payoffs.size(); i++) { sum += payoffs[i] * discount; }
    return sum / payoffs.size();
}

}
