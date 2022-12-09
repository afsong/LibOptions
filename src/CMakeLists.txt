find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(options
        pbPlots/pbPlots.cpp
        pbPlots/supportLib.cpp
        monte_carlo.cpp
        binary_tree.cpp
        least_squares_fitter.cpp
        longstaff_schwartz_algo.cpp
        
        american_option.cpp
        path_plotter.cpp
        
        bsm.cpp 
        europevanilla_payoff.cpp 
        europedigital_payoff.cpp 
        europevanilla_model.cpp
        constant_volatility.cpp
        binary_tree_modern.cpp
)

target_link_libraries(options
        Eigen3::Eigen
)

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
