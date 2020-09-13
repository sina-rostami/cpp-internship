cmake_minimum_required(VERSION 3.18)

set(This GtestLearning)

project(${This})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # for mixing libraries together to make executable

enable_testing() # we're gonna have unit tests

add_subdirectory(gtest)


set(Sources
    ExampleTests.cpp 
)

set(MyTest "GolTest")

add_executable(${MyTest} ${Sources})

target_link_libraries(
    ${MyTest}
    PUBLIC
    gtest_main
)

add_test(  # for calling make test
    NAME ${MyTest}
    COMMAND ${MyTest}
)

