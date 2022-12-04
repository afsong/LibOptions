#include <vector>
#include <random>

using namespace std;
vector<vector<double>> GenerateStockPaths(int path_num, int timestamp_num, double S0, double T, double r, double sigma) {
    //generate dW for stock price paths
    vector<vector<double>> dW;

    default_random_engine generator;
    normal_distribution<double> distribution(0.0,1.0);

    for (int i = 0; i < path_num; i++) {
        dW.push_back({});
        for (int j = 0; j < timestamp_num; j++) {
            dW[i].push_back(distribution(generator));
        }
    }

    double dt = T / timestamp_num;
    vector<vector<double>> paths;
    double S = S0;

    for (int i = 0; i < path_num; i++) {
        paths.push_back({});
        for (int j = 0; j < timestamp_num; j++) {
            S += r * S *dt + sigma * S * sqrt(dt) * dW[i][j];
            paths[i].push_back(S);
        }
        S = S0;
    }

    return paths;
}