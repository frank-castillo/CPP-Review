cmake_minimum_required(VERSION 3.28)
project(TestProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(TestProject main.cpp
        Const_Lesson.cpp
        StaticArrays.cpp)
