#include <dummy.h>
#include <MonteCarlo.h>
#include <iostream>
#include <pbPlots.hpp>
#include <supportLib.hpp>

//main function
using namespace std;
int main(int argc, char *argv[])
{
//    bool success;
//    StringReference *errorMessage = new StringReference();
//    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
//
//    vector<double> xs{-2, -1, 0, 1, 2};
//    vector<double> xs2{-1, 0, 1, 2, 3};
//    vector<double> ys{2, -1, -2, -1, 2};
//
//    success = DrawScatterPlot(imageReference, 600, 400, &xs, &ys, errorMessage);
//    success = DrawScatterPlot(imageReference, 600, 400, &xs2, &ys, errorMessage);
//
//    if(success){
//        vector<double> *pngdata = ConvertToPNG(imageReference->image);
//        WriteToFile(pngdata, "example2.png");
//        DeleteImage(imageReference->image);
//    }else{
//        cerr << "Error: ";
//        for(wchar_t c : *errorMessage->string){
//            wcerr << c;
//        }
//        cerr << endl;
//    }
//
//    return success ? 0 : 1;

    vector<vector<double>> vect;
    for (int i = 0; i < 10; i++)
    {
        vect.push_back({});
        for (int j = 0; j < 5; j++)
        {
            vect[i].push_back(1);
        }
    }
    vector<vector<double>> paths = GenerateStockPaths(100, 10, 1, 1, 0.04, 0.2);
    for (int i = 0; i < paths.size(); i++)
    {
        for (int j = 0; j < paths[i].size(); j++)
        {
            cout << paths[i][j] << " ";
        }
        cout << endl;
    }
    int ret = 0;
    std::cout << ret << std::endl;
    return 0;
}
