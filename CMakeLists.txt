cmake_minimum_required(VERSION 3.28)
project(CPP_Review)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPP_Review main.cpp
        Const_Lesson.cpp
        Arrays_DataContainers/StaticArrays.cpp
        Arrays_DataContainers/DynamicArrays.cpp
        Arrays_DataContainers/CharacterString_vs_Strings.cpp
        Statements_Expressions_Operators.cpp
        ProgramFlow.cpp
        Functions.cpp)
