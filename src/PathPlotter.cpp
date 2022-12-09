#include <PathPlotter.h>
#include <pbPlots.hpp>
#include <supportLib.hpp>

#include <iostream>
#include <vector>
using namespace std;

int PlotAPath(vector<double> x, vector<double> y, string filename){
        bool success;
        StringReference *errorMessage = new StringReference();
        RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

        success = DrawScatterPlot(imageReference, 600, 400, &x, &y, errorMessage);

        if(success){
            vector<double> *pngdata = ConvertToPNG(imageReference->image);
            WriteToFile(pngdata, filename);
            DeleteImage(imageReference->image);
        }else{
            cerr << "Error: ";
            for(wchar_t c : *errorMessage->string){
                wcerr << c;
            }
            cerr << endl;
        }

        return success ? 0 : 1;
}