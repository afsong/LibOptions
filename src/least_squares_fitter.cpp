#include <Eigen/QR>
#include <cmath>
#include <vector>
#include <least_squares_fitter.h>

namespace LibOptions {

LeastSquaresFitter::LeastSquaresFitter(int order): order(order) {}

// from:
// https://towardsdatascience.com/least-square-polynomial-fitting-using-c-eigen-package-c0673728bd01
void LeastSquaresFitter::PolyFit(const std::vector<double>& xs,
                                 const std::vector<double>& ys,
                                 std::vector<double>& coeff)
{
    // Create Matrix Placeholder of size n x k, n= number of datapoints, k =
    // order of polynomial, for exame k = 3 for cubic polynomial
    Eigen::MatrixXd T(xs.size(), order + 1);
    Eigen::VectorXd V = Eigen::VectorXd::Map(&ys.front(), ys.size());
    Eigen::VectorXd result;

    // Check to make sure inputs are correct
    assert(xs.size() == ys.size());
    assert(xs.size() >= order + 1);

    // Populate the matrix
    for (size_t i = 0; i < xs.size(); ++i) {
        for (size_t j = 0; j < order + 1; ++j) { T(i, j) = pow(xs.at(i), j); }
    }

    // Solve for linear least square fit
    result = T.householderQr().solve(V);
    coeff.resize(order + 1);
    for (int k = 0; k < order + 1; k++) { coeff[k] = result[k]; }
}

void LeastSquaresFitter::PolyPredict(const std::vector<double>& xs,
                                     std::vector<double>& predictedYs,
                                     const std::vector<double>& coeff)
{
    for (int i = 0; i < xs.size(); ++i) {
        double predictedY = 0.0;
        for (int j = 0; j < order + 1; ++j) {
            predictedY += coeff[j] * pow(xs.at(i), j);
        }
        predictedYs.push_back(predictedY);
    }
}

double MeanSquaredError(const std::vector<double>& actualValue,
                        const std::vector<double>& predictedValue)
{
    assert(actualValue.size() == actualValue.size());

    double error = 0.0;
    for (int i = 0; i < actualValue.size(); i++) {
        error += pow(actualValue.at(i) - predictedValue.at(i), 2);
    }

    return error / actualValue.size();
}

} // namespace LibOptions
