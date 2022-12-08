#ifndef LIBOPTIONS_LEASTSQUARESFITTER_H
#define LIBOPTIONS_LEASTSQUARESFITTER_H
#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/QR>

using namespace std;


class LeastSquaresFitter {
    private:
        int order;
    public:
        LeastSquaresFitter(int order);
        void PolyFit(const vector<double> &xs, const vector<double> &ys, vector<double> &coeff);
        void PolyPredict(const vector<double> &xs, vector<double> &predictedYs,
                         const vector<double> &coeff);
};

double MeanSquaredError(const vector<double> &actualValue, const vector<double> &predictedValue);

#endif // LIBOPTIONS_LEASTSQUARESFITTER_H
