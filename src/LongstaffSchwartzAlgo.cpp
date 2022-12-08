#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <LeastSquaresFitter.h>
#include <AmericanOption.h>
#include <monte_carlo.h>
#include <LongstaffSchwartzAlgo.h>

using namespace std;

void LibOptions::DiscountCashflow(std::vector<double> &cashflow, const double r, const double dt, const int i)
{
    for (int j = 0; j < cashflow.size(); j++)
    {
        cashflow[j] *= exp(-r * dt * i);
    }
}

void LibOptions::UpdateCashflow(vector<double> &cashflow,
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
            cashflow[inMoneyPaths[i]] = exerciseValues[i];
        }
    }
}


void LibOptions::PredictContinuationValues(const std::vector<std::vector<double>> &stockPricePaths,
                               const std::vector<std::vector<double>> &coeffs,
                               int timestampNum,
                               int forwardPathsNum,
                               int order,
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
        LeastSquaresFitter fitter = LeastSquaresFitter(order);
        fitter.PolyPredict(currentStockPrices, currentPredictedContinuationValues, coeffs.at(timestampNum-i-2));
        predictedValues.push_back(currentPredictedContinuationValues);
    }
}

double LibOptions::SumOptimalExercisedPayoffs (const std::vector<std::vector<double>> &stockPricePaths,
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
                sumValue += currentPayoff * exp(-r * dt * j);
                sumNum += 1;
                break;
            }
        }
    }
    return sumValue;
}


LibOptions::LongstaffSchwartzAlgo::LongstaffSchwartzAlgo(const LibOptions::LongstaffConfig &longstaffConfig)
{ // Constructor with parameters
    backwardPathsNum = longstaffConfig.backwardPathsNum;
    forwardPathsNum = longstaffConfig.forwardPathsNum;
    timestampNum = longstaffConfig.timestampNum;
    S0 = longstaffConfig.S0;
    K = longstaffConfig.K;
    T = longstaffConfig.T;
    r = longstaffConfig.r;
    sigma = longstaffConfig.sigma;
    leastSquaresOrder = longstaffConfig.leastSquaresOrder;
    dt = longstaffConfig.T / longstaffConfig.timestampNum;
    std::cout << "Longstaff-Schwartz American Option Config"<< "\n";
    std::cout << "Backward paths number: "<< backwardPathsNum << "\n";
    std::cout << "Forward paths number: "<< forwardPathsNum << "\n";
    std::cout << "Timestamps number: "<< timestampNum << "\n";
    std::cout << "S0: "<< S0 << ", ";
    std::cout << "K: "<< K << ", ";
    std::cout << "T: "<< T << ", ";
    std::cout << "r: "<< r << ", ";
    std::cout << "sigma: "<< sigma << ", ";
    std::cout << "dt: "<< dt << "\n";
    std::cout << "Least squares method order: "<< leastSquaresOrder << "\n";
    std::cout << std::endl;
}

void LibOptions::LongstaffSchwartzAlgo::BackwardFit(std::vector<std::vector<double>> &coeffs)
{
    std::cout << "Backward fitting starts " << std::endl;

    // Generate stock price paths
    LibOptions::MonteCarloConfig monteConfig;
    monteConfig.d_numPaths = backwardPathsNum;
    monteConfig.d_numTimestamps = timestampNum;
    monteConfig.d_origPrice = S0;
    monteConfig.d_time = T;
    monteConfig.d_riskFreeRate = r;
    monteConfig.d_volatility = sigma;

    LibOptions::MonteCarloPath monteCarloPath(monteConfig);

    vector<vector<double>> stockPricePaths = monteCarloPath.generateStockPaths();

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
        cout << "At timestamp " << timestamp << " ";
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

        LeastSquaresFitter fitter = LeastSquaresFitter(leastSquaresOrder);

        // 3. Apply least squares method
        vector<double> coeff;
        fitter.PolyFit(inMoneyStockPrices, inMoneyDiscountedCashflows, coeff);

        coeffs.push_back(coeff);

        // 4. Predict cashflow
        std::vector<double> predictedCashflow;
        fitter.PolyPredict(inMoneyStockPrices, predictedCashflow, coeff);

        // Calculate meanSquaredError
//        std::cout<< "Loss: "<< " ";
//        std::cout << MeanSquaredError(inMoneyDiscountedCashflows, predictedCashflow) << std::endl;

        // 5. Update cashflow
        UpdateCashflow(cashflow, inMoneyStockPrices, inMoneyPaths, predictedCashflow, K);

        // 6. Calculate cashflow mean
        std::cout << "cashflow mean is " << reduce(cashflow.begin(), cashflow.end()) / cashflow.size() << "\n";
    }
    std::cout << "Backward fitting ends " << "\n" <<std::endl;
}

double LibOptions::LongstaffSchwartzAlgo::ForwardEvaluate(const std::vector<std::vector<double>> &coeffs)
{
    std::cout << "Forward evaluation starts " << std::endl;
    // 1. Generate stock price paths for forward evaluation
    LibOptions::MonteCarloConfig monteConfig;
    monteConfig.d_numPaths = forwardPathsNum;
    monteConfig.d_numTimestamps = timestampNum;
    monteConfig.d_origPrice = S0;
    monteConfig.d_time = T;
    monteConfig.d_riskFreeRate = r;
    monteConfig.d_volatility = sigma;

    LibOptions::MonteCarloPath monteCarloPath(monteConfig);

    vector<vector<double>> stockPricePaths = monteCarloPath.generateStockPaths();

    assert(timestampNum == coeffs.size() + 1);

    // 2. Predict all expected continuation values
    std::vector<std::vector<double>> predictedValues;
    PredictContinuationValues(stockPricePaths, coeffs, timestampNum, forwardPathsNum, leastSquaresOrder, predictedValues);

    // 3. Calculate option values based on optimal stop rules
    double optionValues = SumOptimalExercisedPayoffs(stockPricePaths,
                                                     predictedValues,
                                                     timestampNum, forwardPathsNum,
                                                     K, r, dt) / forwardPathsNum;

    std::cout << "Forward evaluation ends " << std::endl;
    std::cout << "Forward evaluated option values: " << optionValues  << "\n" << std::endl;
    return optionValues;
}
