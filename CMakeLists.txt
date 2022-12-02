cmake_minimum_required(VERSION 3.14)
project(LibOptions)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_subdirectory(driver)
add_subdirectory(src)
add_subdirectory(test)
