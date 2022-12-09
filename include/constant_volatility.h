#ifndef LIBOPTIONS_CONSTANT_VOLATILITY_H
#define LIBOPTIONS_CONSTANT_VOLATILITY_H
#include <vector>
#include <volatility.h>
namespace LibOptions {

class ConstantVolatility : public Volatility {
public:
    ConstantVolatility(double sigma);
    double local_vol(double S, double t);
private:
    double sigma;
};

} // namespace LibOptions

#endif
