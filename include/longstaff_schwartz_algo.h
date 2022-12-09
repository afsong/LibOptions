#ifndef LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
#define LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
#include <iostream>
#include <vector>
#include <least_squares_fitter.h>


namespace LibOptions {

using namespace std;

struct LongstaffConfig {
    int backwardPathsNum;
    int backwardSeed;
    int forwardPathsNum;
    int forwardSeed;
    int timestampNum;
    double S0;
    double K;
    double T;
    double r;
    double sigma;
    int leastSquaresOrder;
    bool plotGraphs;
};

class LongstaffSchwartzAlgo {
private:
    int backwardPathsNum;
    int backwardSeed;
    int forwardPathsNum;
    int forwardSeed;
    int timestampNum;
    double S0;
    double K;
    double T;
    double r;
    double sigma;
    double dt;
    int leastSquaresOrder;
    bool plotGraphs;
public:
    LongstaffSchwartzAlgo(const LibOptions::LongstaffConfig &longstaffConfig);

    void BackwardFit(vector<vector<double>> &coeffs);

    double ForwardEvaluate(const vector<vector<double>> &coeffs);

};

void DiscountCashflow(vector<double> &cashflow, const double r, const double dt, const int i);

void UpdateCashflow(vector<double> &cashflow,
                    const vector<double> &inMoneyStockPrices,
                    const vector<int> &inMoneyPaths,
                    const vector<double> &predictedCashflow,
                    int K);

void PredictContinuationValues(const vector<vector<double>> &stockPricePaths,
                               const vector<vector<double>> &coeffs,
                               int timestampNum,
                               int forwardPathsNum,
                               int order,
                               vector<vector<double>> &predictedValues);

double SumOptimalExercisedPayoffs(const vector<vector<double>> &stockPricePaths,
                                  const vector<vector<double>> &predictedValues,
                                  int timestampNum,
                                  int forwardPathsNum,
                                  double K,
                                  double r,
                                  double dt);
}

#endif // LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
