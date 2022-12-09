#include <algorithm>
#include <cmath>
#include <constant_volatility.h>
#include <iomanip>
#include <iostream>
#include <vector>
namespace LibOptions {

ConstantVolatility::ConstantVolatility(const double sigma): sigma(sigma) {}

double ConstantVolatility::local_vol(double S, double t)
{
    return sigma;
}
} // namespace LibOptions
