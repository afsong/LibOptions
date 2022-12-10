#ifndef LIBOPTIONS_ADV_LEAST_SQUARES_FITTER_H
#define LIBOPTIONS_ADV_LEAST_SQUARES_FITTER_H

#include <cmath>
#include <iostream>
#include <vector>

namespace LibOptions {
    class AdvLeastSquaresFitter {
        private:
            int order;
        public:
            AdvLeastSquaresFitter(int order);
            void PolyFit(const std::vector<std::vector<double>>& xss,
                         const std::vector<double>& ys,
                         std::vector<double>& coeffs);
            void PolyPredict(const std::vector<std::vector<double>>& xss,
                             std::vector<double>& predictedYs,
                             const std::vector<double>& coeffs);
    };
}



#endif //LIBOPTIONS_ADV_LEAST_SQUARES_FITTER_H
