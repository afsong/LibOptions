#ifndef LIBOPTIONS_MONTECARLO_H
#define LIBOPTIONS_MONTECARLO_H

#include <path_generator.h>
#include <vector>

namespace LibOptions {

struct MonteCarloConfig {
    double d_origPrice;
    double d_numTimestamps;
    double d_time;
    double d_numPaths;
    double d_riskFreeRate;
    double d_volatility;
    int seed;
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
