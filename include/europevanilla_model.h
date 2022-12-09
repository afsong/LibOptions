#ifndef LIBOPTIONS_EUROPE_VANILLA_MODEL_H
#define LIBOPTIONS_EUROPE_VANILLA_MODEL_H
#include <constant_volatility.h>
#include <model.h>
#include <string>

namespace LibOptions {

struct EuropeVanillaModelConfig {
    double d_origPrice;
    std::shared_ptr<ConstantVolatility> d_volatility;
    double d_riskFreeRate;
    double d_strikePrice;
    double d_time;
    double d_dividend;
    int samplesize;
    bool iscall;
    std::string pricingmodeltype;
};
class EuropeVanillaModel : public Model {
public:
    EuropeVanillaModel(const EuropeVanillaModelConfig& config);
    double calc_value();
private:
    EuropeVanillaModelConfig d_config;
};

} // namespace LibOptions

#endif
