#ifndef LIBOPTIONS_LEASTSQUARESFITTER_H
#define LIBOPTIONS_LEASTSQUARESFITTER_H

#include <cmath>
#include <iostream>
#include <vector>

namespace LibOptions {
class LeastSquaresFitter {
private:
    int order;
public:
    LeastSquaresFitter(int order);
    void PolyFit(const std::vector<double>& xs, const std::vector<double>& ys,
                 std::vector<double>& coeff);
    void PolyPredict(const std::vector<double>& xs,
                     std::vector<double>& predictedYs,
                     const std::vector<double>& coeff);
};

double MeanSquaredError(const std::vector<double>& actualValue,
                        const std::vector<double>& predictedValue);
} // namespace LibOptions

#endif // LIBOPTIONS_LEASTSQUARESFITTER_H
