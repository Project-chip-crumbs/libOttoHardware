cmake_minimum_required(VERSION 2.8)
project(libStakHardware)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

file(GLOB src "src/**/*.cpp")

add_library(StakHardware ${src})