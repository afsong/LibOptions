# Getting Started

This document will discuss how one can get started using the library.

## Example 1: Monte Carlo Stock Paths

Suppose that we want to generate Monte Carlo options price paths. The algorithm is designed to create different stock paths (a parameter passed in by the user).

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