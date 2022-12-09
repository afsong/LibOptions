#include <algorithm>
#include <binary_tree_modern.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
namespace LibOptions {

BinaryTreeModern::BinaryTreeModern(const BinaryTreeModernConfig& config)
    : d_config(config), d_paths(), d_prob_paths()
{}

double binary_tree_node_up(double F, double S, double vol, double dt,
    double Sd)
{
    return F + pow(S, 2) * pow(vol, 2) * dt / (F - Sd);
}
double binary_tree_node_down(double F, double S, double vol,
                             double dt, double Su)
{
    return F - pow(S, 2) * pow(vol, 2) * dt / (Su - F);
}

double binary_tree_prob_up(double F, double Su, double Sd)
{
    return (F - Sd) / (Su - Sd);
}
double binary_tree_prob_down(double F, double Su, double Sd)
{
    return (Su - F) / (Su - Sd);
}

std::vector<std::vector<double>> BinaryTreeModern::generateStockPaths() {
    d_prob_paths.push_back({1.0});
    d_paths.push_back({d_config.d_origPrice});
    double dt
        = d_config.d_time / d_config.d_steps;
    for (int i = 2; i <= d_config.d_steps + 1; i++) {
        if (i % 2 == 0) { 
            std::vector<double> storage(i);
            std::vector<double> prob_storage(2*i-2);
            int mid =(int) i / 2;
            double vol = d_config.d_volatility.local_vol(
                d_paths[i - 2][mid - 1], dt * (i - 2));
            storage[mid]
                = d_paths[i - 2][mid - 1] * exp(-vol * sqrt(dt));
            storage[mid - 1] = d_paths[i - 2][mid - 1] * exp(-vol * sqrt(dt));
            prob_storage[i - 2] = binary_tree_prob_up(
                d_paths[i - 2][mid - 1]
                    * exp((d_config.d_riskFreeRate - d_config.d_dividend) * dt),
                storage[mid - 1], storage[mid]);
            prob_storage[i - 1] = 1 - prob_storage[i - 2];
            for (int j = mid - 2; j >= 0; j--) { 
                S = d_paths[i - 2][j];
                F = S
                    * exp((d_config.d_riskFreeRate - d_config.d_dividend) * dt);
                storage[j] = binary_tree_node_up(
                    F, S,
                    d_config.d_volatility.local_vol(S,
                                                    dt * (i - 2)),dt,storage[j+1]);
                prob_storage[2 * j] = binary_tree_prob_up(
                    F,storage[j], storage[j+1]);
                prob_storage[2 * j + 1] = 1 - prob_storage[2 * j];
            }
            for (int j = mid +1; j <= i-1; j++) {
                S = d_paths[i - 2][j - 1];
                F = S
                    * exp((d_config.d_riskFreeRate - d_config.d_dividend) * dt);
                storage[j] = binary_tree_node_down(
                    F, S, d_config.d_volatility.local_vol(S, dt * (i - 2)), dt,
                    storage[j - 1]);
                prob_storage[2 * j - 2]
                    = binary_tree_prob_up(F, storage[j - 1], storage[j]);
                prob_storage[2 * j - 1] = 1 - prob_storage[2 * j];
            }
            d_paths.push_back(storage);
            std::vector<double> prob(i);
            prob[0] = d_prob_paths[i - 2][0] * prob_storage[0];
            for (int j = 1; j <= i - 2; j++) {
                prob[j] = d_prob_paths[i - 2][j - 1] * prob_storage[2 * j - 1]
                          + d_prob_paths[i - 2][j] * prob_storage[2 * j];
            }
            prob[i - 1] = d_prob_paths[i - 2][i - 2] * prob_storage[2 * i - 2];
            d_prob_paths.push_back(prob);
        }
        else {
            std::vector<double> storage(i);
            std::vector<double> prob_storage(2 * i - 2);
            int mid = (int)i / 2;
            storage[mid] = d_config.d_origPrice;
            for (int j = mid - 1; j >= 0; j--) {
                S = d_paths[i - 2][j];
                F = S
                    * exp((d_config.d_riskFreeRate - d_config.d_dividend) * dt);
                storage[j] = binary_tree_node_up(
                    F, S, d_config.d_volatility.local_vol(S, dt * (i - 2)), dt,
                    storage[j + 1]);
                prob_storage[2 * j]
                    = binary_tree_prob_up(F, storage[j], storage[j + 1]);
                prob_storage[2 * j + 1] = 1 - prob_storage[2 * j];
            }
            for (int j = mid + 1; j <= i - 1; j++) {
                S = d_paths[i - 2][j - 1];
                F = S
                    * exp((d_config.d_riskFreeRate - d_config.d_dividend) * dt);
                storage[j] = binary_tree_node_down(
                    F, S, d_config.d_volatility.local_vol(S, dt * (i - 2)), dt,
                    storage[j - 1]);
                prob_storage[2 * j - 2]
                    = binary_tree_prob_up(F, storage[j - 1], storage[j]);
                prob_storage[2 * j - 1] = 1 - prob_storage[2 * j];
            }
            d_paths.push_back(storage);
            std::vector<double> prob(i);
            prob[0] = d_prob_paths[i - 2][0] * prob_storage[0];
            for (int j = 1; j <= i - 2; j++) {
                prob[j] = d_prob_paths[i - 2][j - 1] * prob_storage[2 * j - 1]
                          + d_prob_paths[i - 2][j] * prob_storage[2 * j];
            }
            prob[i - 1] = d_prob_paths[i - 2][i - 2] * prob_storage[2 * i - 2];
            d_prob_paths.push_back(prob);
        }
    }
    std::vector<std::vector<double>> result;
    result.push_back(d_paths[d_paths.size() - 1]);
    result.push_back(d_prob_paths[d_prob_paths.size() - 1]);
    return result;
}

} // namespace LibOptions