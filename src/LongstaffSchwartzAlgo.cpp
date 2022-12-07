#include <LongstaffSchwartzAlgo.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <MonteCarlo.h>
#include <LeastSquaresFitter.h>

using namespace std;

void DiscountCashflow(vector<double> &cashflow, const double r, const double dt, const int i)
{
    for (int j = 0; j < cashflow.size(); j++)
    {
        cashflow[j] *= exp(-r * dt * i);
    }
}

void UpdateCashflow(vector<double> &cashflow,
                    const vector<double> &inMoneyStockPrices,
                    const vector<int> &inMoneyPaths,
                    const vector<double> &predictedCashflow,
                    int K)
{
    vector<double> exerciseValues;
    for (double stockPrice : inMoneyStockPrices)
    {
        exerciseValues.push_back(PutOptionPayoff(stockPrice, K));
    }

    for (int i = 0; i < inMoneyPaths.size(); i++)
    {
        if (predictedCashflow[i] < exerciseValues[i]) {
//            std::cout<< "In money path: "<< inMoneyPaths[i] << "\n";
//            std::cout<< "Exercise Payoff: "<< exerciseValues[i] << "\n";
//            std::cout<< "Predicted Continuation value: "<< predictedCashflow[i] <<"\n";
            cashflow[inMoneyPaths[i]] = exerciseValues[i];
//            std::cout<< "Updated Cashflow: "<< cashflow[inMoneyPaths[i]]  <<"\n";
        }
    }
}


LongstaffSchwartzAlgo::LongstaffSchwartzAlgo()
{ // Constructor with parameters
    backwardPathsNum = 100000;
    forwardPathsNum = 100;
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

    // Get the expiration cashflow
    for (int i = 0; i < stockPricePaths.size(); i++)
    {
        double payoff = PutOptionPayoff(stockPricePaths[i].back(), K);
        cashflow.push_back(payoff);
//        cout << payoff << " ";
    }
//    cout << endl;

    // Backward fit loops
    for (int timestamp = callNum - 1; timestamp > 0; timestamp--) {
        // one step

        // 1. Discount the cashflow
        DiscountCashflow(cashflow, r, dt, 1);

//    for (double i : cashflow) {
//        cout << i << " ";
//    }
//    cout << endl;

        // 2. Find in money paths' stock prices and discounted cashflows
        cout << "Timestamp: " << timestamp << endl;
        vector<int> inMoneyPaths;
        // x and y for least squares
        vector<double> inMoneyStockPrices;
        vector<double> inMoneyDiscountedCashflows;
        for (int i = 0; i < stockPricePaths.size(); i++)
        {
            if(PutOptionPayoff(stockPricePaths[i][timestamp-1], K) > 0.0)
            {
                inMoneyPaths.push_back(i);
                inMoneyStockPrices.push_back(stockPricePaths[i][timestamp-1]);
                inMoneyDiscountedCashflows.push_back(cashflow[i]);
            }
        }

        // Print out in money paths
//    cout << "In money paths: " <<  " \n";
//    for (double i : inMoneyPaths) {
//        cout << i << " ";
//    }
//    cout << endl;
//    cout << "In money stock prices: " <<  " \n";
//    for (double i : inMoneyStockPrices) {
//        cout << i << " ";
//    }
//    cout << endl;

//        cout << "In-Money Paths' Discounted Cashflows: " <<  " \n";
//        for (double i : inMoneyDiscountedCashflows)
//        {
//            cout << i << " ";
//        }
//        cout << endl;

        // 3. Apply least squares method
        vector<double> coeff;
        PolyFit(inMoneyStockPrices, inMoneyDiscountedCashflows, coeff, 3);
        //

        // Print out coeff
//        cout << "Coeffs: " <<  " \n";
//        for (double i : coeff)
//        {
//            cout << i << " ";
//        }
//        cout << endl;


        // 4. Predict cashflow
        std::vector<double> predictedCashflow;
        PolyPredict(inMoneyStockPrices, coeff, predictedCashflow, 3);
//        cout << "Predicted Cashflows: " <<  " \n";
//        for (double i : predictedCashflow)
//        {
//            cout << i << " ";
//        }
//        cout << endl;


        // Calculate meanSquaredError
        std::cout<< "Loss: "<< "\n";
        std::cout << MeanSquaredError(inMoneyDiscountedCashflows, predictedCashflow) << std::endl;

        // 5. Update cashflow
        UpdateCashflow(cashflow, inMoneyStockPrices, inMoneyPaths, predictedCashflow, K);

//    std::cout<< "Cashflow: "<< "\n";
//    for (double c : cashflow)
//    {
//        std::cout<<  c << " ";
//    }
//    std::cout << endl;

        // 6. Calculate cashflow mean
        std::cout << "Cashflow mean: " << reduce(cashflow.begin(), cashflow.end()) / cashflow.size() << "\n";

    }
    return 0;
}

int LongstaffSchwartzAlgo::ForwardEvaluation()
{

}
