cmake_minimum_required(VERSION 3.15)
project(ShaleDB)

add_executable(test test.cpp
        test.cpp)

target_include_directories(test PRIVATE ./include)

target_compile_features(test PRIVATE cxx_std_17)

target_include_directories(ShaleDB PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})