#include <AmericanOption.h>
#include <algorithm>
#include <math.h>

using namespace std;

double PutOptionPayoff(double S, double K) {
    return max(K-S, 0.0);
}

double CallOptionPayoff(double S, double K) {
    return max(S-K, 0.0);
}

double DPayoff(double S, double K) {
    return SmoothDigit(S, K);
}

double D2Payoff(double S, double K) {
    return SmoothDirac(S, K);
}

double SmoothDigit(double S, double K) {
    double a = 0.00001;
    return -1.0 / (1.0 + exp(-(K-S)/a));
}

double SmoothDirac(double S, double K) {
    double a = 0.00001;
    return exp(-(K-S)/a) / (a * pow(1.0 + exp(-(K-S)/a),2));
}
