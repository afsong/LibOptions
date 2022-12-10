# Getting Started

This document will discuss how one can get started using the library.

## Example 1: Monte Carlo Stock Paths

Suppose that we want to generate Monte Carlo stock price paths. The algorithm is designed to create different stock paths (a parameter passed in by the user).

The following simple program can illustrate the intended usage.

```C++
#include <monte_carlo.h>

int main(int argv, char *argv[])
{
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
}
```

First note that all structs and classes are inside the `LibOptions` namespace to avoid collision.

In order to create Monte Carlo Paths, users must provide some basic parameters. In this example, we start with original price of 1, consider the price over the span of 10 years, and want to generate 100 paths in total. This configuration object is then passed to the path generator itself (i.e. `LibOptions::MonteCarloPath`) which provides 2 API - `generateStockPaths` and `printPath`.

## Example 2: Price American Put Option Using Longstaff and Schwartz's Monte Carlo Approach
We implemented the Longstaff and Schwartz's Monte Carlo American option pricing algorithm in LongstaffSchwartzAlgo class. 

To estimate an American put option's price using the algorithm, the user should can see the following sample program. 

All config fields should be set in a LongstaffConfig struct. The user need to determine how many stock price paths he or she wants to simulate for both backward fitting phase and forward evaluation phase. Also, S0, K, T, r, and sigma which are required for Monte Carlo simulation should also be provided. 

For the least squares method which is used to estimate the conditional expection functions, the polynomials' order is also required. 

Additonaly, if the user want to see the cash flows and losses curves along the backward fitting steps, the plotGraph should be set to true. The two plotting graphs will be stored in the executable file's directory after the backward fitting phase finishs successfully.  

``` C++
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
```
Call `BackwardFit`, the algorithm will start doing backward fitting from the last timestamp to the starting timestamp. The the least squares regression method's polynomials (or conditional expection functions) will be stored in the 2D vector `coeffs`, so if the user wants to forward evalute the American put option again using a new set of stock price paths, the exact same `coeffs` should be passed whe the `ForwardEvaluate` function.   
