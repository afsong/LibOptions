add_library(options
    monte_carlo.cpp "bsm.cpp" "europevanilla_payoff.cpp" "europedigital_payoff.cpp" "europevanilla_model.cpp")

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
