#ifndef LIBOPTIONS_EUROPE_VANILLA_PAYOFF_H
#define LIBOPTIONS_EUROPE_VANILLA_PAYOFF_H
#include <payoff.h>
#include <vector>

namespace LibOptions {

struct EuroVanillaPayoffConfig {
    double d_strikePrice;
    bool iscall;
};
class EuroVanillaPayoff : public Payoff {

public:
    EuroVanillaPayoff(const EuroVanillaPayoffConfig& config);
    std::vector<double> calc_payoff(std::vector<std::vector<double>> path);
private:
    EuroVanillaPayoffConfig d_config;
    std::vector<double> payoff;
};
}



#endif
