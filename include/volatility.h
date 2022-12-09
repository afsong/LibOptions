#ifndef LIBOPTIONS_VOLATILITY_H
#define LIBOPTIONS_VOLATILITY_H
#include <vector>
namespace LibOptions {

class Volatility {
public:
    virtual double local_vol(double S, double t) = 0;
};

} // namespace LibOptions

#endif
