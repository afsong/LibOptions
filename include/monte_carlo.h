#ifndef LIBOPTIONS_MONTECARLO_H
#define LIBOPTIONS_MONTECARLO_H

#include <vector>
#include <path_generator.h>

namespace LibOptions {

struct MonteCarloConfig {
    double d_origPrice;
    int d_numTimestamps;
    double d_strikePrice;
    int d_numPaths;
    double d_riskFreeRate;
    double d_volatility;
};

class MonteCarloPath : public PathGenerator {
public:
    MonteCarloPath(const MonteCarloConfig& config);

    std::vector<std::vector<double>> generateStockPaths();
    void printPath();

private:
    MonteCarloConfig d_config;
    std::vector<std::vector<double>> d_paths;
};

} // namespace LibOptions

#endif // LIBOPTIONS_MONTECARLO_H
