#ifndef LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
#define LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
#include "AmericanOption.h"
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
        int BackwardFit();
        int ForwardEvaluation();
};

//void DiscountCashflow(vector<double> *cashflow, const double r, const double dt, const int i);


#endif // LIBOPTIONS_LONGSTAFFSCHWARTZALGO_H
