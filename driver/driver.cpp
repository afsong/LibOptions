#include <iostream>
#include <MonteCarlo.h>
#include <LongstaffSchwartzAlgo.h>
#include <LeastSquaresFitter.h>


//main function
using namespace std;
int main(int argc, char *argv[])
{
    vector<vector<double>> coeffs;
    LongstaffSchwartzAlgo longstaffSchwartzAlgo = LongstaffSchwartzAlgo();
    longstaffSchwartzAlgo.BackwardFit(coeffs);
    longstaffSchwartzAlgo.ForwardEvaluate(coeffs);

    return 0;
}
