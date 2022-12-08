#include <iostream>

#include <monte_carlo.h>
#include<binary_tree.h>
int main(int argc, char* argv[])
{
    // std::vector<std::vector<double>> vect;

    // for (int i = 0; i < 10; i++) {
    //     vect.push_back({});
    //     for (int j = 0; j < 5; j++) { vect[i].push_back(1); }
    // }
    
    // LibOptions::MonteCarloConfig monteConfig;
    // monteConfig.d_origPrice = 1;
    // monteConfig.d_numTimestamps = 10;
    // monteConfig.d_strikePrice = 1;
    // monteConfig.d_numPaths = 100;
    // monteConfig.d_riskFreeRate = 0.04;
    // monteConfig.d_volatility = 0.2;

    // LibOptions::MonteCarloPath path(monteConfig);
    // path.generateStockPaths();

    // path.printPath();

   
    LibOptions::BinaryTreeConfig treeConfig;
    treeConfig.d_origPrice = 29;
    treeConfig.d_numTimestamps = 1;
    treeConfig.d_strikePrice = 30;
    treeConfig.d_numSteps = 2;
    treeConfig.d_riskFreeRate = 0.03;
    treeConfig.d_volatility = 0.25;

    LibOptions::BinaryTreePath path(treeConfig);
    path.generateStockPaths();
    path.printPath();
    std::cout << "europecall: "<<path.europecall()<< std::endl;
    std::cout << "europeput: "<<path.europeput()<<std::endl;;
    std::cout << "americall: "<<path.americall()<<std::endl;;
    std::cout << "americall: "<<path.ameriput()<<std::endl;;
    return 0;
}
