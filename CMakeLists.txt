cmake_minimum_required(VERSION 3.9)
project(LearningCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -std:c++latest)

add_executable(LearningCPP main.cpp Sudoku.cpp Sudoku.hpp)