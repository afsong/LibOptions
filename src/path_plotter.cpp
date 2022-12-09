#include "pbPlots/pbPlots.hpp"
#include "pbPlots/supportLib.hpp"
#include <iostream>
#include <path_plotter.h>
#include <vector>

namespace LibOptions {
namespace Utils {

int plotPath(std::vector<double>& x, std::vector<double>& y,
             const std::filesystem::path& filename)
{
    StringReference* errorMessage = new StringReference();
    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    bool success
        = DrawScatterPlot(imageReference, 600, 400, &x, &y, errorMessage);

    if (success) {
        std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, filename);
        DeleteImage(imageReference->image);
    }
    else {
        std::cerr << "Error: ";
        for (wchar_t c: *errorMessage->string) { std::wcerr << c; }
        std::cerr << std::endl;
    }

    return success ? 0 : 1;
}

} // namespace Utils
} // namespace LibOptions
