cmake_minimum_required(VERSION 3.18)

set(This ExampleTests)

set(Sources
    ExampleTests.cpp 
)

add_executable(${This} ${Sources})
target_link_libraries(
    ${This} 
    PUBLIC
    gtest_main
    GtestLearning
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
