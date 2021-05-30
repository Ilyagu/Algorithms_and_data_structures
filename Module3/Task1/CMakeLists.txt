cmake_minimum_required(VERSION 3.16.3)
project(Task1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Task1
        arcGraph.cpp
        arcGraph.hpp
        iGraph.hpp
        listGraph.cpp
        listGraph.hpp
        matrixGraph.cpp
        matrixGraph.hpp
        setGraph.cpp
        setGraph.hpp
        task1.cpp)
