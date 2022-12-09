#ifndef LIBOPTIONS_AMERICAN_OPTION_H
#define LIBOPTIONS_AMERICAN_OPTION_H

class AmericanOption {};
double PutOptionPayoff(double S, double K);
double CallOptionPayoff(double S, double K);
double DPayoff(double S, double K);
double D2Payoff(double S, double K);
double SmoothDigit(double S, double K);
double SmoothDirac(double S, double K);

#endif // LIBOPTIONS_AMERICAN_OPTION_H
