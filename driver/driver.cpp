#include <dummy.h>
#include <MonteCarlo.h>
#include <iostream>
#include <LongstaffSchwartzAlgo.h>

//main function
using namespace std;
int main(int argc, char *argv[])
{

//    vector<vector<double>> paths = GenerateStockPaths(10000, 100, 1, 1, 0.04, 0.2);
//    for (int i = 0; i < paths.size(); i++)
//    {
//        for (int j = 0; j < paths[i].size(); j++)
//        {
//            cout << paths[i][j] << " ";
//        }
//        cout << endl;
//    }
//    int ret = 0;
//    std::cout << ret << std::endl;
//    return 0;
    LongstaffSchwartzAlgo longstaffSchwartzAlgo = LongstaffSchwartzAlgo();
    longstaffSchwartzAlgo.BackwardFit();


}
