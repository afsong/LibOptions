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

    void generateStockPaths();

    [[nodiscard]] const DoubleVector<double>& getStockPaths() const;
    [[nodiscard]] DoubleVector<double>& getStockPaths();

    void printPath();
private:
    MonteCarloConfig d_config;
    DoubleVector<double> d_paths;
};

inline const StockPath& MonteCarloPath::getStockPaths() const
{
    return d_paths;
}

inline StockPath& MonteCarloPath::getStockPaths()
{
    return d_paths;
}

} // namespace LibOptions

#endif // LIBOPTIONS_MONTECARLO_H
