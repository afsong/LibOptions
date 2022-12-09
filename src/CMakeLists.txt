add_library(options
        pbPlots/pbPlots.cpp
        pbPlots/supportLib.cpp
        monte_carlo.cpp
        binary_tree.cpp
        LeastSquaresFitter.cpp
        LongstaffSchwartzAlgo.cpp
        AmericanOption.cpp
        PathPlotter.cpp)

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
