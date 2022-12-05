//
// Created by Zhonglin Yang on 12/5/22.
//

#ifndef LIBOPTIONS_AMERICANOPTION_H
#define LIBOPTIONS_AMERICANOPTION_H

class AmericanOption {};
double PutOptionPayoff(double S, double K);
double CallOptionPayoff(double S, double K);
double DPayoff(double S, double K);
double D2Payoff(double S, double K);
double SmoothDigit(double S, double K);
double SmoothDirac(double S, double K);

#endif // LIBOPTIONS_AMERICANOPTION_H
