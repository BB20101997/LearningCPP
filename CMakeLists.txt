cmake_minimum_required(VERSION 3.9)
project(LearningCPP)

set(CMAKE_CXX_STANDARD 17)
if(MSVS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++17")
endif(MSVS)

include_directories(hearder)

add_executable(LearningCPP main.cpp Sudoku.cpp hearder/Sudoku.hpp)