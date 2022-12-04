add_library(options 
    dummy.cpp
        MonteCarlo.cpp ../include/MonteCarlo.h StockPathsGenerator.cpp ../include/StockPathsGenerator.h pbPlots.cpp ../include/pbPlots.hpp supportLib.cpp ../include/supportLib.hpp)

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
