cmake_minimum_required(VERSION 3.10)
project(Algos)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "g++")

set(ALL_SOURCES
    ArcGraph/ArcGraph.cpp
    ListGraph/ListGraph.cpp
    MatrixGraph/MatrixGraph.cpp
    SetGraph/SetGraph.cpp
)

set(ALL_HEADERS_DIRS
    AbstGraph/
    ArcGraph/
    ListGraph/
    MatrixGraph/
    SetGraph/
)

include_directories(${ALL_HEADERS_DIRS})
add_executable(task1.out main.cpp ${ALL_SOURCES})
