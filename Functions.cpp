//
// Created by juanf on 2024-03-04.
//

#include <cfloat>
#include <iostream>

using std::cout, std::endl, std::cin;
constexpr double pi = 3.14159265;

// Function Declarations - kind of function prototype
// Tells the compiler a function exists so that it can use it without a body yet being present
// Body of the funtion must be declared in order to compute a result or perform a task (Function Definition)
// Also called forward declaration
double CalculateArea(double radius);
double CalculateDynamicArea(double radius, double pi = 3.14);
double CalculateCircumference(double radius);
double SurfaceArea(double radius, double height);

void SayHello();

// Adding a default exit number in case none is provided, preventing a bug
int FibonacciSequence(int fibIndex = 1);

// Overloaded function declaration
// As you can see, the function has the same name and retur type, but the arguments are different, each performing a different computation
// but used for the same thing
double Area(double radius);
double Area(double radius, double height);

void DisplayArray(int array[], int length)
{
    for(int i = 0; i < length; ++i)
    {
        cout << array[i] << endl;
    }
}

void DisplayArray(char string[], int length)
{
    for(int i = 0; i < length; ++i)
    {
        cout << string[i] << endl;
    }
}

// Pass by reference
void AreaByReference(double radius, double& result);

int main()
{
    // Functions allow us to compartmentalize and organize a program's execution logic
    // Enables us to split the contents of an application into logical blocks that are invoked sequentially
    // Functions can take parameters and return values based on their needs
    // It must be invoked in order to peform its task
    // Great for code reusability!

    /*
     * A function is composed of a return type, a name, and optional parameters
     * returntype MyFunctionName(parameters)
     *
     * If a function does not return anything to the function that invoked it, mark the return type as void
     * Parameters are optional. They should be delimited by commas, and a type has to be specified
     * void AnotherFunction(float valueA, int valueB)
     * float valueA and int valueB are two separate arguments, of different type
     * Arguments are part of a functions parameter list
     *
     * FUNCTIONS CAN ONLY HAVE A SINGLE RETURN TYPE!
     *
     * Function definitions, are declared inside a statement block
     * Return staments are mandatory unless the return type is void
     *
     * Calling a function == Invoking a function
     *
     * Function parameters are like local variables - they are only valid inside the function's scope
     * Unless passed by reference or pointer, the compiler creates a local copy of the arguments for use inside the function
     *
     * Functions can have multiple return statements, and based on the logic of your computation, you might need to return a result right away
     * or have to wait until later to return. Be careful with it though, as it can get complicated to debug if there are many return paths
     */

    // Implementation examples
    cout << "Functions Implementation!" << endl;

    double radius {3};
    double height {6.5};

    cout << "\n\nArea and circumference of a circle" << endl;
    cout << "Radius is: " << radius << endl;
    cout << "Area is: " << CalculateArea(radius) << endl;
    cout << "Circumference is: " << CalculateCircumference(radius) << endl;

    cout << "\n\nSurface are of a cylinder" << endl;
    cout << "Radius is: " << radius << endl;
    cout << "Height is: " << height << endl;
    cout << "Surface area is: " << SurfaceArea(radius, height) << endl;

    cout << "\n" << endl;
    SayHello();

    /*
     * Functions support parameters with default values
     * These parameters function in a curious way. They can be given to the function on their invoking, or if no parameter is given
     * the function will make use of the default value assigned to it on the declaration
     *
     * Parameters with a default value become optional, giving the programmer the ability to either modify the base value or carry on a process
     * with a preset value
     *
     * Funtions can have multiple default value arguments. HOWEVER! They should all be at the end of the arguments list in a function declaration
     * double Area(double radius, double pi = 3.1416, double height = 10); This is proper syntax
     * double Area(double radius = 3, double pi, double height = 10); This is WRONG!
     */

    cout << "\n\nUsing default values in a function" << endl;
    double userPi{FLT_MIN};

    cout << "Enter a custom pi value: " << endl;
    cin >> userPi;

    cout << "Area of circle with radius: " << radius << " using your custom pi value: " << CalculateDynamicArea(radius, userPi) << endl;
    cout << "Area of circle with radius: " << radius << " using default pi value: " << CalculateDynamicArea(radius) << endl;

    // As seen above, the function call is the same, however one does provide a second argument while the other does not, with the compiler reverting to the default value
    // Definitions do not need to specifiy the default value again, only the declaration does

    //------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------

    /*
     * RECURSION
     * Functions that invoke themselves
     * Dangerous to work with if not well structured
     * Recursive functions need a clearly defined exit condition, where it returns without invoking itself again
     *
     * IN THE CASE THERE IS AN ABSENCE OF AN EXIT CONDITION OR A BUG IN THE EXIT CONDITION
     * The program will become stuck in the recursive call, constantly invoking itself over and over again
     * This will stop once your program breaks due to a stack overflow
     *
     * BE CAREFUL!
     */

    cout << "\n\nRecursion Implementation!" << endl;
    cout << "Enter 0-based index of desired Fibonacci number: " << endl;
    int index {INT_MIN};
    cin >> index;

    cout << "Fibonacci number is: " << FibonacciSequence(index) << endl;

    // USING FUNCTIONS WITH DIFFERENT FORMS OF DATA

    // Function Overloading
    // Functions with the same name and return type but with different parameters or sets of parameters are called
    // OVERLOADED FUNCTIONS
    // These overloaded functions are useful in applications where a function with a particular name/function, that returns a specific type and value
    // needs to be invoked with a different set of parameters, but in the end, it outputs the same or similar result

    cout << "\n\nFunction overloading" << endl;
    cout << "Enter z for cylinder area calculation, enter c for circle area calculation" << endl;
    char input {'\0'};
    cin >> input;

    if(input == 'z')
    {
        // Use of overloaded function
        cout << "Radius: " << radius << endl;
        cout << "Height: " << height << endl;
        cout << "Area of cylinder: " << Area(radius, height) << endl;
    }
    else if(input == 'c')
    {
        // Use of base function
        cout << "Radius: " << radius << endl;
        cout << "Area of circle: " << Area(radius) << endl;
    }
    else
    {
        cout << "Not a valid option" << endl;
    }

    // Passing in an array of values
    const int MAX_LENGTH{5};
    int numbers[MAX_LENGTH] {1,2,3,4,5};
    char theString[MAX_LENGTH] {'a','b','c','d','\0'}; // Good practice to add null character!

    DisplayArray(numbers, MAX_LENGTH);
    DisplayArray(theString, MAX_LENGTH);

    // Passing arguments as reference
    // Useful when you need a function to work on a variable that modifies a value available outside the function
    // Instead of making a copy of the argument's value, the functions works directly with the original value/memory contents
    // Use the & next to a vartiable type to indicate to the compiler that the argument is to be passed as a reference and not a copy
    // This is the best way to simulate multiple returns, as the function's logic can modify the value of multiple variables at once with no need to
        //  return and just making use of the reference functionality

    cout << "\n\nPass by reference implementation" << endl;

    double areaResult{FLT_MIN};
    AreaByReference(radius, areaResult);
    cout << "The area of the circle is: " << areaResult << endl;

    return 0;
}
// Function definitions
double CalculateArea(double radius)
{
    return pi * radius * radius;
}

double CalculateCircumference(double radius)
{
    return 2 * pi * radius;
}

double SurfaceArea(double radius, double height)
{
    double area = (2 * (pi * radius * radius)) + (2 * pi * radius * height);
    return area;
}

void SayHello()
{
    cout << "Hello World! I am a void, no arguments function." << endl;
}

double CalculateDynamicArea(double radius, double pi)
{
    return pi * radius * radius;
}

int FibonacciSequence(int fibIndex)
{
    if(fibIndex < 2)
    {
        return fibIndex;
    }
    else // recursion if fibIndex >= 2
    {
        // recursive call
        return FibonacciSequence(fibIndex - 1) + FibonacciSequence(fibIndex - 2);
    }
}

double Area(double radius)
{
    return pi * radius * radius;
}

double Area(double radius, double height)
{
    // Makes use of base function, showcasing reusability thanks to functions
    return 2 * Area(radius) + 2 * pi * radius * height;
}

void AreaByReference(double radius, double &result)
{
    // Notice how we are not returning a value yet we are modifying the original value of the memory location assigned to result
    result = pi * radius * radius;
}
