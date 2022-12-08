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
        if (predictedCashflow[i] < exerciseValues[i])
        {
//            std::cout<< "In money path: "<< inMoneyPaths[i] << "\n";
//            std::cout<< "Exercise Payoff: "<< exerciseValues[i] << "\n";
//            std::cout<< "Predicted Continuation value: "<< predictedCashflow[i] <<"\n";
            cashflow[inMoneyPaths[i]] = exerciseValues[i];
//            std::cout<< "Updated Cashflow: "<< cashflow[inMoneyPaths[i]]  <<"\n";
        }
    }
}


void PredictContinuationValues(const std::vector<std::vector<double>> &stockPricePaths,
                               const std::vector<std::vector<double>> &coeffs,
                               int timestampNum,
                               int forwardPathsNum,
                               std::vector<std::vector<double>> &predictedValues)
{
    vector<double> currentStockPrices;
    vector<double> currentPredictedContinuationValues;
    for (int i = 0; i < timestampNum - 1; i++)
    {
        currentStockPrices.clear();
        currentPredictedContinuationValues.clear();
        for (int j = 0; j < forwardPathsNum; j++)
        {
            currentStockPrices.push_back(stockPricePaths[j][i]);
        }
        PolyPredict(currentStockPrices, coeffs.at(timestampNum-i-2), currentPredictedContinuationValues, 3);
        predictedValues.push_back(currentPredictedContinuationValues);
    }
}

double SumOptimalExercisedPayoffs (const std::vector<std::vector<double>> &stockPricePaths,
                                   const std::vector<std::vector<double>> &predictedValues,
                                   int timestampNum,
                                   int forwardPathsNum,
                                   double K,
                                   double r,
                                   double dt)
{
    double sumValue = 0.0;
    int sumNum = 0;
    for (int i = 0; i < forwardPathsNum; i++)
    {
        for (int j = 0; j < timestampNum - 1; j++)
        {
            double currentPayoff = PutOptionPayoff(stockPricePaths[i][j], K);
            if (currentPayoff > 0 && currentPayoff > predictedValues[j][i] ) {
//                std::cout << "Path number: " << i << " ";
//                std::cout << "Exercise timestamp: " << j << "\n";
//                std::cout << "Stock price: " << stockPricePaths[i][j] << " ";
//                std::cout << "Current payoff: " << currentPayoff << " ";
//                std::cout << "Predicted continuation value: " << predictedValues[j][i] << "\n";
//                std::cout << std:: endl;
                sumValue += currentPayoff * exp(-r * dt * j);
                sumNum += 1;
                break;
            }
        }
    }
    return sumValue;
//    std::cout << "Option value: " << sumValue / forwardPathsNum << "\n";
//    std::cout << "Num of exercised: " << sumNum << "\n";
//    std::cout << std:: endl;
}


LongstaffSchwartzAlgo::LongstaffSchwartzAlgo()
{ // Constructor with parameters
    backwardPathsNum = 100000;
    forwardPathsNum = 100000;
    timestampNum = 50;
    S0 = 1.0;
    K = 1.0;
    r = 0.04;
    T = 1.0;
    sigma = 0.2;
    dt = T / timestampNum;
}

void LongstaffSchwartzAlgo::BackwardFit(std::vector<std::vector<double>> &coeffs)
{
    std::cout << "Backward fitting starts " << std::endl;
    // Generate stock price paths
    vector<vector<double>> stockPricePaths = GenerateStockPaths(backwardPathsNum,
                                                                timestampNum,
                                                                S0, T, r, sigma);

    int callNum = timestampNum;

    vector<double> cashflow;

    // Get the expiration cashflow
    for (int i = 0; i < stockPricePaths.size(); i++)
    {
        double payoff = PutOptionPayoff(stockPricePaths[i].back(), K);
        cashflow.push_back(payoff);
    }

    // Backward fit loops
    for (int timestamp = callNum - 1; timestamp > 0; timestamp--) {

        // 1. Discount the cashflow
        DiscountCashflow(cashflow, r, dt, 1);

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

        // 3. Apply least squares method
        vector<double> coeff;
        PolyFit(inMoneyStockPrices, inMoneyDiscountedCashflows, coeff, 3);

        coeffs.push_back(coeff);

        // 4. Predict cashflow
        std::vector<double> predictedCashflow;
        PolyPredict(inMoneyStockPrices, coeff, predictedCashflow, 3);

        // Calculate meanSquaredError
        std::cout<< "Loss: "<< " ";
        std::cout << MeanSquaredError(inMoneyDiscountedCashflows, predictedCashflow) << std::endl;

        // 5. Update cashflow
        UpdateCashflow(cashflow, inMoneyStockPrices, inMoneyPaths, predictedCashflow, K);

        // 6. Calculate cashflow mean
        std::cout << "Cashflow mean: " << reduce(cashflow.begin(), cashflow.end()) / cashflow.size() << "\n";

    }
}

double LongstaffSchwartzAlgo::ForwardEvaluate(const std::vector<std::vector<double>> &coeffs)
{
    std::cout << "Forward evaluation starts " << std::endl;
    // 1. Generate stock price paths for forward evaluation
    vector<vector<double>> stockPricePaths = GenerateStockPaths(forwardPathsNum,
                                                                timestampNum,
                                                                S0, T, r, sigma);

    assert(timestampNum == coeffs.size() + 1);

    // 2. Predict all expected continuation values
    std::vector<std::vector<double>> predictedValues;
    PredictContinuationValues(stockPricePaths, coeffs, timestampNum, forwardPathsNum, predictedValues);

    // 3. Calculate option values based on optimal stop rules
    double optionValues = SumOptimalExercisedPayoffs(stockPricePaths,
                                                     predictedValues,
                                                     timestampNum, forwardPathsNum,
                                                     K, r, dt) / forwardPathsNum;

    std::cout << "Forward evaluated option values: " << optionValues  << std::endl;
    return optionValues;
}
