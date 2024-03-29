cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

project(project1)

add_executable(project1 src/main.cpp src/big_real.hpp src/big_real.cpp src/test.hpp src/test.cpp src/pi_calculation.hpp src/pi_calculation.cpp)
