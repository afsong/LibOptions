#include <LongstaffSchwartzAlgo.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <MonteCarlo.h>
#include <LeastSquaresFitter.h>

using namespace std;

void DiscountCashflow(vector<double> &cashflow, const double r, const double dt, const int i) {
    for (int j = 0; j < cashflow.size(); j++) {
        cashflow[j] *= exp(-r * dt * i);
    }
}

LongstaffSchwartzAlgo::LongstaffSchwartzAlgo() { // Constructor with parameters
    backwardPathsNum = 100;
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



    // one step
    // Discount the cashflow
    DiscountCashflow(cashflow, r, dt, 1);

//    for (double i : cashflow) {
//        cout << i << " ";
//    }
//    cout << endl;

    cout << "Timestamp: " << 99 << endl;
    vector<int> inMoneyPaths;
    // x and y for least squares
    vector<double> inMoneyStockPrices;
    vector<double> inMoneyDiscountedCashflows;
    for (int i = 0; i < stockPricePaths.size(); i++)
    {
        if(PutOptionPayoff(stockPricePaths[i][98], K) > 0.0) {
            inMoneyPaths.push_back(i);
            inMoneyStockPrices.push_back(stockPricePaths[i][98]);
            inMoneyDiscountedCashflows.push_back(cashflow[i]);
        }
    }

    // print out in money paths
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
    cout << "In-Money Paths' Discounted Cashflows: " <<  " \n";
    for (double i : inMoneyDiscountedCashflows) {
        cout << i << " ";
    }
    cout << endl;

    // least squares method
    vector<double> coeff;
    PolyFit(inMoneyStockPrices, inMoneyDiscountedCashflows, coeff, 3);
    //

    //
    cout << "Coeffs: " <<  " \n";
    for (double i : coeff) {
        cout << i << " ";
    }
    cout << endl;


    std::vector<double> predictedCashflow;
    PolyPredict(inMoneyStockPrices, coeff, predictedCashflow, 3);
    cout << "Predicted Cashflows: " <<  " \n";
    for (double i : predictedCashflow) {
        cout << i << " ";
    }
    cout << endl;


    std::cout<< "Loss: "<< "\n";
    std::cout << MeanSquaredError(inMoneyDiscountedCashflows, predictedCashflow) << std::endl;


    // Backward fit loops
//    for (int i = callNum - 1; i > 0; i--) {
//        // Discount the cashflow
//        DiscountCashflow(cashflow, r, dt, i);
//    }
    return 0;
}

int LongstaffSchwartzAlgo::ForwardEvaluation()
{

}
