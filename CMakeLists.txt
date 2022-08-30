
cmake_minimum_required(VERSION 3.16)

project(performance-benchmarks VERSION 0.1.0)

set(BENCHMARK_ENABLE_TESTING OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -fno-omit-frame-pointer -std=c++17 -fno-rtti")

include_directories(benchmark/include)
add_subdirectory(benchmark)

add_subdirectory(1.intro)
