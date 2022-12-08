#ifndef LIBOPTIONS_MONTECARLO_H
#define LIBOPTIONS_MONTECARLO_H

#include <vector>

using namespace std;
vector<vector<double>>  GenerateStockPaths(int path_num, int timestamp_num, double S0, double T, double r, double sigma);

#endif // LIBOPTIONS_MONTECARLO_H
