#include <iostream>

#include <monte_carlo.h>
#include <europevanilla_model.h>

int main(int argc, char* argv[])
{
    std::vector<std::vector<double>> vect;

    for (int i = 0; i < 10; i++) {
        vect.push_back({});
        for (int j = 0; j < 5; j++) { vect[i].push_back(1); }
    }
    /*
    LibOptions::MonteCarloConfig monteConfig;
    monteConfig.d_origPrice = 1;
    monteConfig.d_numTimestamps = 10;
    monteConfig.d_strikePrice = 1;
    monteConfig.d_numPaths = 100;
    monteConfig.d_riskFreeRate = 0.04;
    monteConfig.d_volatility = 0.2;

    LibOptions::MonteCarloPath path(monteConfig);
    path.generateStockPaths();

    path.printPath();
    */

    // BSM Vanilla below
    LibOptions::EuropeVanillaModelConfig evConfig;
    evConfig.d_origPrice=100;
    evConfig.d_volatility=0.1;
    evConfig.d_riskFreeRate=0.02;
    evConfig.d_strikePrice=100;
    evConfig.d_time=3;
    evConfig.d_dividend=0;
    evConfig.samplesize=10000;
    evConfig.iscall=true;
    evConfig.pricingmodeltype= "bsm";
    LibOptions::EuropeVanillaModel evModel(evConfig);
    double price = evModel.calc_value();
    std::cout << "The price of EuroVanilla: " << price << std::endl;
   

    return 0;
}
