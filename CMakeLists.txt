cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
project(tictactoe C)

set(CMAKE_C_STANDARD 23)

add_executable(tictactoe main.c)
