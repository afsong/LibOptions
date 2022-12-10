#include <cstdlib>
#include <ctime>
#include <vector>
#include <longstaff_schwartz_algo.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));

    std::vector<std::vector<double>> coeffs;
    LibOptions::LongstaffConfig longstaffConfig;
    longstaffConfig.backwardPathsNum = 500000;
    longstaffConfig.backwardSeed = std::rand();
    longstaffConfig.forwardPathsNum = 500000;
    longstaffConfig.forwardSeed = std::rand();
    longstaffConfig.timestampNum = 100;
    longstaffConfig.S0 = 1.0;
    longstaffConfig.K = 1.0;
    longstaffConfig.T = 1.0;
    longstaffConfig.r = 0.04;
    longstaffConfig.sigma = 0.20;
    longstaffConfig.leastSquaresOrder = 10;
    longstaffConfig.plotGraphs = true;
    LibOptions::LongstaffSchwartzAlgo longstaffSchwartzAlgo
        = LibOptions::LongstaffSchwartzAlgo(longstaffConfig);
    longstaffSchwartzAlgo.BackwardFit(coeffs);
    longstaffSchwartzAlgo.ForwardEvaluate(coeffs);

}
