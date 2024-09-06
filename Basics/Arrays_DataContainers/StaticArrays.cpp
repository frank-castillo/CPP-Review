//
// Created by juanf on 2024-02-13.
//

// Module 04

#include <iostream>

using namespace std;

constexpr int Square(const int number) {
    return number * number;
}

int StaticArrays_main() {
    const int ARRAY_LENGTH = 5;

    // Hard coded value
    int myNumbers[ARRAY_LENGTH] = {5, 10, 0, -101, 20};

    // Computation performed at compile time through a constexpr.
    int moreNumbers[Square(ARRAY_LENGTH)];

    // Modifying an array
    myNumbers[4] = 10;
    moreNumbers[4] = 10;

    // This is a way to declare multidimensional arrays, initializing every array individually.
    int multiSolarPanels[2][3] = {{0,1,2},{3,4,5}};
    // [0][1][2]
    // [3][4][5]

    for(const auto& multiSolarPanel : multiSolarPanels) {
        for(const auto& j : multiSolarPanel) {
            std::cout << "multidimensional declared: Panel number: " << j << std::endl;

        }
    }

    // However, because memory is still contiguous, we can declare a multidimensional array the same way
    // we would a one-dimensional array.
    int multiButLinearSolarPanels[2][3] = {0,1,2,3,4,5};

    // Type of variable => const int(&variable)[3]
    // Declared this way to make reference to the row array and make the compiler aware of the second array.
    // int specifies the type of elements in the array.
    // [x] specifies the number of elements (size) of the array.
    // (&variable) declares the variable as a reference to an array. Use the parentheses to properly associate the reference
    //      Otherwise compiler might understand it as an array of references.
    for(const int(&panel)[3] : multiButLinearSolarPanels) {
        for (const int& j: panel) {
            std::cout << "One-dimensioanl declared multi dimensional: Panel number: " << j << std::endl;
        }
    }

    return 0;
}
