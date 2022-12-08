add_library(options
    monte_carlo.cpp
    binary_tree.cpp)

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
