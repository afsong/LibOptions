#ifndef LIBOPTIONS_BINARY_TREE_MODERN_H
#define LIBOPTIONS_BINARY_TREE_MODERN_H

#include <path_generator.h>
#include <vector>
#include <volatility.h>
namespace LibOptions {


struct BinaryTreeModernConfig {
    double d_origPrice;
    Volatility d_volatility;
    double d_riskFreeRate;
    double d_strikePrice;
    double d_time;
    int d_steps;
    double d_dividend;
};
class BinaryTreeModern : public PathGenerator {
public:
    BinaryTreeModern(const BinaryTreeModernConfig& config);
    std::vector<std::vector<double>> generateStockPaths();
    void printPath();
private:
    BinaryTreeModernConfig d_config;
    std::vector<std::vector<double>> d_paths;
    std::vector<std::vector<double>> d_prob_paths;
};

} // namespace LibOptions

#endif
