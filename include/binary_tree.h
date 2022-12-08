#ifndef LIBOPTIONS_BINARY_TREE_H
#define LIBOPTIONS_BINARY_TREE_H

#include <path_generator.h>

namespace LibOptions {

struct BinaryTreeConfig {
    double d_origPrice;
    double d_numTimestamps;
    double d_strikePrice;
    double d_numSteps;
    double d_riskFreeRate;
    double d_volatility;

};

class BinaryTreePath : public PathGenerator {
public:
    BinaryTreePath(const BinaryTreeConfig& config);

    std::vector<std::vector<double>> generateStockPaths();
    void printPath();
    double europecall();
    double europeput();
    double americall();
     double ameriput();

private:
    BinaryTreeConfig d_config;
    std::vector<std::vector<double>> d_paths;
    double d_p ;
    double d_d ;
    int d_statusFlg = 0;
};

}

#endif
