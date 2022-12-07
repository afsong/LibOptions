#ifndef LIBOPTIONS_LEASTSQUARESFITTER_H
#define LIBOPTIONS_LEASTSQUARESFITTER_H
#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/QR>
using namespace std;
class LeastSquaresFitter {};

void PolyFit(const std::vector<double> &xs,
             const std::vector<double> &ys,
             std::vector<double> &coeff,
             int order);

void PolyPredict(const std::vector<double> &xs,
                 const std::vector<double> &coeff,
                 std::vector<double> &predictedYs,
                 int order);

double MeanSquaredError(const vector<double> &actualValue, const vector<double> &predictedValue);

#endif // LIBOPTIONS_LEASTSQUARESFITTER_H
