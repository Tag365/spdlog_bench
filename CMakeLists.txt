cmake_minimum_required(VERSION 3.18)
project(benchmark_spdlog CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(spdlog REQUIRED)
add_executable(benchmark_spdlog
        split.h
        split.cpp
        main.cpp
)
