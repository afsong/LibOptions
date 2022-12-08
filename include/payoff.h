#ifndef LIBOPTIONS_PAYOFF_H
#define LIBOPTIONS_PAYOFF_H

namespace LibOptions {

class Payoff {
public:
    virtual std::vector<double>
    calc_payoff(std::vector<std::vector<double>> path) = 0;
};



}
#endif