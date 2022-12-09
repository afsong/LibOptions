#include <iostream>
#include <cstdlib>
#include <ctime>
#include <longstaff_schwartz_algo.h>
#include <monte_carlo.h>
#include <europevanilla_model.h>
#include <binary_tree.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    std::vector<std::vector<double>> coeffs;
    LibOptions::LongstaffConfig longstaffConfig;
    longstaffConfig.backwardPathsNum = 50000;
    longstaffConfig.backwardSeed = std::rand();
    longstaffConfig.forwardPathsNum = 50000;
    longstaffConfig.forwardSeed = std::rand();
    longstaffConfig.timestampNum = 100;
    longstaffConfig.S0 = 1.0;
    longstaffConfig.K = 1.0;
    longstaffConfig.T = 1.0;
    longstaffConfig.r = 0.04;
    longstaffConfig.sigma = 0.2;
    longstaffConfig.leastSquaresOrder = 10;
    longstaffConfig.plotGraphs = true;
    LibOptions::LongstaffSchwartzAlgo longstaffSchwartzAlgo = LibOptions::LongstaffSchwartzAlgo(longstaffConfig);
    longstaffSchwartzAlgo.BackwardFit(coeffs);
    longstaffSchwartzAlgo.ForwardEvaluate(coeffs);

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
    std::cout << "ameriput: "<<path.ameriput()<<std::endl;;

    std::vector<std::vector<double>> vect;

    for (int i = 0; i < 10; i++) {
        vect.push_back({});
        for (int j = 0; j < 5; j++) { vect[i].push_back(1); }
    }
    /*
    LibOptions::MonteCarloConfig monteConfig;
    monteConfig.d_origPrice = 1;
    monteConfig.d_numTimestamps = 10;
    monteConfig.d_time = 1;
    monteConfig.d_numPaths = 100;
    monteConfig.d_riskFreeRate = 0.04;
    monteConfig.d_volatility = 0.2;
    monteConfig.seed = 10;

    LibOptions::MonteCarloPath path(monteConfig);
    path.generateStockPaths();

    path.printPath();
    */

    // BSM Vanilla below
    LibOptions::EuropeVanillaModelConfig evConfig;
    evConfig.d_origPrice=100;
    evConfig.d_volatility=0.1;
    evConfig.d_riskFreeRate=0.02;
    evConfig.d_strikePrice=100;
    evConfig.d_time=3;
    evConfig.d_dividend=0;
    evConfig.samplesize=10000;
    evConfig.iscall=true;
    evConfig.pricingmodeltype= "bsm";
    LibOptions::EuropeVanillaModel evModel(evConfig);
    double price = evModel.calc_value();
    std::cout << "The price of EuroVanilla: " << price << std::endl;
   

    return 0;

}
