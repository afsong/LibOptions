#ifndef LIBOPTIONS_BSM_H
#define LIBOPTIONS_BSM_H
#include <path_generator.h>
namespace LibOptions {

struct BSMConfig {
    double d_origPrice;
    double d_volatility;
    double d_riskFreeRate;
    double d_strikePrice;
    double d_time;
    double d_dividend;
    int samplesize;
};
class BSMPath : public PathGenerator {
public:
    BSMPath(const BSMConfig& config);
    std::vector<std::vector<double>> generateStockPaths();
    void printPath();
private:
    BSMConfig d_config;
    std::vector<std::vector<double>> d_paths;
};

}






#endif
