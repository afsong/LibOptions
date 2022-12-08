#include <MonteCarlo.h>
#include <iostream>
#include <LongstaffSchwartzAlgo.h>
#include <LeastSquaresFitter.h>
#include <monte_carlo.h>
#include <binary_tree.h>

//main function
using namespace std;
int main(int argc, char *argv[])
{
    vector<vector<double>> coeffs;
    LongstaffSchwartzAlgo longstaffSchwartzAlgo = LongstaffSchwartzAlgo();
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
    std::cout << "americall: "<<path.ameriput()<<std::endl;;

    return 0;

}
