#include <Eigen/QR>
#include <cmath>
#include <vector>
#include <adv_least_squares_fitter.h>

namespace LibOptions {

    AdvLeastSquaresFitter::AdvLeastSquaresFitter(int order): order(order) {}

    void AdvLeastSquaresFitter::PolyFit(const std::vector<std::vector<double>>& xss,
                                        const std::vector<double>& ys,
                                        std::vector<double>& coeff)
    {
        int m = xss[0].size();
        // Create Matrix Placeholder of size n x (k * m),
        // n = number of datapoints, k = order of polynomial, m = number of elements in a xs
        Eigen::MatrixXd T(xss.size(), (order + 1) * m);
        Eigen::VectorXd V = Eigen::VectorXd::Map(&ys.front(), ys.size());
        Eigen::VectorXd result;

        // Check to make sure inputs are correct
        assert(xss.size() == ys.size());
        assert(xss.size() >= order + 1);

        // Populate the matrix
        for (size_t i = 0; i < xss.size(); ++i)
        {
            for (size_t j = 0; j < order + 1; ++j)
            {
                for (size_t l = 0; l < m; ++l)
                {
                    T(i, j * m + l) = pow(xss.at(i).at(l), j);
                }
            }
        }

        // Solve for linear least square fit
        result = T.householderQr().solve(V);
        coeff.resize((order + 1) * m);
        for (int k = 0; k < (order + 1) * m; k++)
        {
            coeff[k] = result[k];
        }
    }

    void AdvLeastSquaresFitter::PolyPredict(const std::vector<std::vector<double>>& xss,
                                            std::vector<double>& predictedYs,
                                            const std::vector<double>& coeff)
    {
        int m = xss[0].size();

        for (int i = 0; i < xss.size(); ++i)
        {
            double predictedY = 0.0;
            for (int j = 0; j < order + 1; ++j)
            {
                for (int l = 0; l < m; ++l)
                {
                    predictedY += coeff[j * m + l] * pow(xss.at(i).at(l), j);
                }
            }
            predictedYs.push_back(predictedY);
        }
    }


} // namespace LibOptions