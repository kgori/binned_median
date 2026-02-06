cmake_minimum_required(VERSION 3.20)
project(binned_median)

set(CMAKE_CXX_STANDARD 20)

add_executable(binned_median main.cpp)

install(TARGETS binned_median RUNTIME DESTINATION bin)
