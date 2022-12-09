#include <iostream>
#include <LongstaffSchwartzAlgo.h>
#include <monte_carlo.h>
#include <binary_tree.h>

//main function
using namespace std;

int main(int argc, char *argv[])
{
    vector<vector<double>> coeffs;
    LibOptions::LongstaffConfig longstaffConfig;
    longstaffConfig.backwardPathsNum = 10000;
    longstaffConfig.backwardSeed = 2;
    longstaffConfig.forwardPathsNum = 10000;
    longstaffConfig.forwardSeed = 3;
    longstaffConfig.timestampNum = 20;
    longstaffConfig.S0 = 1.0;
    longstaffConfig.K = 1.0;
    longstaffConfig.T = 1.0;
    longstaffConfig.r = 0.04;
    longstaffConfig.sigma = 0.2;
    longstaffConfig.leastSquaresOrder = 10;
    LibOptions::LongstaffSchwartzAlgo longstaffSchwartzAlgo = LibOptions::LongstaffSchwartzAlgo(longstaffConfig);
    longstaffSchwartzAlgo.BackwardFit(coeffs);
    longstaffSchwartzAlgo.ForwardEvaluate(coeffs);
//
//    LibOptions::BinaryTreeConfig treeConfig;
//    treeConfig.d_origPrice = 29;
//    treeConfig.d_numTimestamps = 1;
//    treeConfig.d_strikePrice = 30;
//    treeConfig.d_numSteps = 2;
//    treeConfig.d_riskFreeRate = 0.03;
//    treeConfig.d_volatility = 0.25;
//
//    LibOptions::BinaryTreePath path(treeConfig);
//    path.generateStockPaths();
//    path.printPath();
//    std::cout << "europecall: "<<path.europecall()<< std::endl;
//    std::cout << "europeput: "<<path.europeput()<<std::endl;;
//    std::cout << "americall: "<<path.americall()<<std::endl;;
//    std::cout << "ameriput: "<<path.ameriput()<<std::endl;;

//    LibOptions::MonteCarloConfig monteConfig;
//    monteConfig.d_origPrice = 1;
//    monteConfig.d_numTimestamps = 10;
//    monteConfig.d_time = 1;
//    monteConfig.d_numPaths = 100;
//    monteConfig.d_riskFreeRate = 0.04;
//    monteConfig.d_volatility = 0.2;
//    monteConfig.seed = 10;
//
//    LibOptions::MonteCarloPath monteCarloPath(monteConfig);
//    monteCarloPath.generateStockPaths();
//    monteCarloPath.printPath();

    return 0;

}
