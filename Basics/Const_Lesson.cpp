//
// Created by juanf on 2024-02-13.
//
#include <iostream>

consteval double GetPi() {
    return 22.0 / 7;
}

consteval double GetPiByValues(double a, double b) {
    return a / b;
}

constexpr double XPi(int x) {
    return x * GetPi();
}

constexpr double Div_Expr(double a, double b) {
    return a / b;
}

const double pi = Div_Expr(22, 7);

// This is not compiling because constexpr need const arguments in order to compile
// double a = 22, b = 7;
// This fixes the issue:
constexpr double a = 22, b = 7;

// This is also assigned at compile time as we are feeding const arguments into the function
const double c = GetPiByValues(a, b);

// Evaluated and assigned at compile time because of variable a being a constexpr
double d = XPi(a);

/**
 * \brief
 */
enum YourCards {
    Ace,
    Jack,
    Queen = 45,
    King
};

void CompareSizeOfIntegers() {
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of unsigned int: " << sizeof(unsigned int) << " bytes" << std::endl;
    std::cout << "Size of long int: " << sizeof(long int) << " bytes" << std::endl;
}

void ComputeAreaAndCircumferenceOfCircle() {
    double radius = 0;
    double diameter = 0;

    std::cout << "Input the radius of the circle: ";
    std::cin >> radius;

    diameter = radius * 2;
    const double area = pi * radius * radius;

    std::cout << "Diameter of circle: " << diameter << " Area of circle: " << area << std::endl;
}

int amain()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << pi << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;

    // This line here gets replaced at compile time by the actual value of pi
    constexpr double piValue = GetPi();
    std::cout << piValue << std::endl;

    // This line happens at run time, as the variable is not set to constexpr/const
    // Compiler will ignore constexpr and process as a regular function
    int multiple = 5;
    double runtimeVariable = XPi(multiple);
    std::cout << "Pi's value multiplied by plain integer, at runtime, not compilation: " << runtimeVariable << std::endl;

    CompareSizeOfIntegers();
    ComputeAreaAndCircumferenceOfCircle();

    return 0;
}

