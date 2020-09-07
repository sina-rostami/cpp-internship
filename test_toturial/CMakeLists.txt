cmake_minimum_required(VERSION 3.18)

set(This GtestLearning)

project(${This} C CXX )

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 2a)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # for mixing libraries together to make executable

enable_testing() # we're gonna have unit tests

