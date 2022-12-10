#include <vector>
#include <random>
#include <longstaff_schwartz_algo.h>

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10000.0);
    int backwardSeed = int(dist(mt));
    int forwardSeed = int(dist(mt));

    LibOptions::LongstaffConfig longstaffConfig{};
    longstaffConfig.backwardPathsNum = 500000;
    longstaffConfig.backwardSeed = backwardSeed;
    longstaffConfig.forwardPathsNum = 500000;
    longstaffConfig.forwardSeed = forwardSeed;
    longstaffConfig.timestampNum = 100;
    longstaffConfig.S0 = 1.0;
    longstaffConfig.K = 1.0;
    longstaffConfig.T = 1.0;
    longstaffConfig.r = 0.04;
    longstaffConfig.sigma = 0.20;
    longstaffConfig.leastSquaresOrder = 10;
    longstaffConfig.plotGraphs = true;

    auto longstaffSchwartzAlgo = LibOptions::LongstaffSchwartzAlgo(longstaffConfig);

    std::vector<std::vector<double>> coeffs;
    longstaffSchwartzAlgo.BackwardFit(coeffs);
    longstaffSchwartzAlgo.ForwardEvaluate(coeffs);
}
