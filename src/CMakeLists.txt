find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(options
        pbPlots/pbPlots.cpp
        pbPlots/supportLib.cpp

        monte_carlo.cpp
        binary_tree.cpp
        least_squares_fitter.cpp
        longstaff_schwartz_algo.cpp
        
        AmericanOption.cpp
        PathPlotter.cpp)

target_link_libraries(options
        Eigen3::Eigen
)

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
