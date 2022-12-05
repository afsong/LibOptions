//
// Created by Zhonglin Yang on 12/5/22.
//

#include <PathPlotter.h>
#include <pbPlots.hpp>
#include <supportLib.hpp>

int PlotAPath(vector<double> x, vector<double> y){
        bool success;
        StringReference *errorMessage = new StringReference();
        RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

        success = DrawScatterPlot(imageReference, 600, 400, &x, &y, errorMessage);

        if(success){
            vector<double> *pngdata = ConvertToPNG(imageReference->image);
            WriteToFile(pngdata, "example.png");
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