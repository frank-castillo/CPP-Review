cmake_minimum_required(VERSION 3.28)
project(CPP_Review)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPP_Review Basics/main.cpp
        Basics/Const_Lesson.cpp
        Basics/Arrays_DataContainers/StaticArrays.cpp
        Basics/Arrays_DataContainers/DynamicArrays.cpp
        Basics/Arrays_DataContainers/CharacterString_vs_Strings.cpp
        Basics/Statements_Expressions_Operators.cpp
        Basics/ProgramFlow.cpp
        Basics/Functions.cpp
        Basics/Pointers_DynamicMemoryAllocation.cpp)
