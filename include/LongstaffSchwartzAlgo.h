#ifndef LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
#define LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
#include <AmericanOption.h>
#include <vector>

class LongstaffSchwartzAlgo {
    private:
        int backwardPathsNum;
        int forwardPathsNum;
        int timestampNum;
//        AmericanOption product;
        double S0;
        double K;
        double r;
        double T;
        double sigma;
        double dt;
    public:
        LongstaffSchwartzAlgo();
        void BackwardFit(std::vector<std::vector<double>> &coeffs);
        double ForwardEvaluate(const std::vector<std::vector<double>> &coeffs);

};

void DiscountCashflow(std::vector<double> &cashflow, const double r, const double dt, const int i);

void UpdateCashflow(std::vector<double> &cashflow,
                    const std::vector<double> &inMoneyStockPrices,
                    const std::vector<double> &inMoneyPaths,
                    const std::vector<double> &predictedCashflow,
                    int K);

void PredictContinuationValues(const std::vector<std::vector<double>> &stockPricePaths,
                               const std::vector<std::vector<double>> &coeffs,
                               int timestampNum,
                               int forwardPathsNum,
                               std::vector<std::vector<double>> &predictedValues);

double SumOptimalExercisedPayoffs (const std::vector<std::vector<double>> &stockPricePaths,
                                   const std::vector<std::vector<double>> &predictedValues,
                                   int timestampNum,
                                   int forwardPathsNum,
                                   double K,
                                   double r,
                                   double dt);


#endif // LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
