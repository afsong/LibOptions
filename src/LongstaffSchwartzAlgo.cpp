#include "LongstaffSchwartzAlgo.h"
#include "vector"
#include "MonteCarlo.h"
#include <iostream>

using namespace std;

LongstaffSchwartzAlgo::LongstaffSchwartzAlgo() { // Constructor with parameters
    backwardPathsNum = 10000;
    forwardPathsNum = 10000;
    timestampNum = 100;
    S0 = 1.0;
    K = 1.0;
    r = 0.04;
    T = 1.0;
    sigma = 0.2;
    dt = 0.01;
}

int LongstaffSchwartzAlgo::BackwardFit()
{
    // Generate stock price paths
    vector<vector<double>> stockPricePaths = GenerateStockPaths(backwardPathsNum,
                                                                timestampNum,
                                                                S0, T, r, sigma);

    vector<double> means;
    vector<double> losses;

    int timestampNumBetweenCalls = 0;
    int end = 0;
    int begin = 0;
    int callNum = 0;

    callNum = timestampNum;
    timestampNumBetweenCalls = 1;

    vector<double> cashflow;

    for (int i = 0; i < stockPricePaths.size(); i++)
    {
        double payoff = PutOptionPayoff(stockPricePaths[i].back(), K);
        cashflow.push_back(payoff);
        cout << payoff << " ";
    }
    cout << endl;

}

int LongstaffSchwartzAlgo::ForwardEvaluation()
{

}