cmake_minimum_required(VERSION 4.3)
project(HW3_2526B)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW3_2526B
        main.cpp
        Person.cpp
        Person.h
        TaskManager.h)
