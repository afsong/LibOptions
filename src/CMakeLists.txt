add_library(options 
    dummy.cpp
)

# PROJECT_SOURCE_DIR - macro for project root dir
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)
