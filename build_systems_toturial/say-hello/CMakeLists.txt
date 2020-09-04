add_library(
    say-hello
    src/say-hello/hello.hpp
    src/say-hello/hello.cpp
    )

target_include_directories(say-hello PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
