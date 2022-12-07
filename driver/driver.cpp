#include <iostream>
#include <MonteCarlo.h>
#include <LongstaffSchwartzAlgo.h>
#include <LeastSquaresFitter.h>


//main function
using namespace std;
int main(int argc, char *argv[])
{
    LongstaffSchwartzAlgo longstaffSchwartzAlgo = LongstaffSchwartzAlgo();
    longstaffSchwartzAlgo.BackwardFit();

    return 0;
}
