#ifndef LIBOPTIONS_EUROPE_DIGITAL_PAYOFF_H
#define LIBOPTIONS_EUROPE_DIGITAL_PAYOFF_H
#include <payoff.h>
#include <vector>
namespace LibOptions {

struct EuroDigitalPayoffConfig {
    double d_strikePrice;
    bool iscall;
};
class EuroDigitalPayoff : public Payoff {
public:
    EuroDigitalPayoff(const EuroDigitalPayoffConfig& config);
    std::vector<double> calc_payoff(std::vector<std::vector<double>> path);
private:
    EuroDigitalPayoffConfig d_config;
    std::vector<double> payoff;
};
} // namespace LibOptions

#endif
