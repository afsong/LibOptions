add_library(options 
    dummy.cpp
        MonteCarlo.cpp ../include/MonteCarlo.h StockPathsGenerator.cpp ../include/StockPathsGenerator.h pbPlots.cpp ../include/pbPlots.hpp supportLib.cpp ../include/supportLib.hpp PathPlotter.cpp ../include/PathPlotter.h AmericanOption.cpp ../include/AmericanOption.h LongstaffSchwartzAlgo.cpp ../include/LongstaffSchwartzAlgo.h)

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
