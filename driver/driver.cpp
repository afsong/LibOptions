#include <dummy.h>
#include <MonteCarlo.h>
#include <iostream>
#include <LongstaffSchwartzAlgo.h>
#include <Eigen/Dense>
#include <Eigen/Core>

int print_eigen(Eigen::MatrixX3d m)
{
    // Eigen Matrices do have rule to print them with std::cout
    std::cout << m << std::endl;
    return 0;
}

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

    Eigen::Matrix3d test; //3 by 3 double precision matrix initialization

    // Let's make it a symmetric matrix
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            test(i,j) = (i+1)*(1+j);
    }

    // Print
    print_eigen(test);

    return 0;

}
