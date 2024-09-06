//
// Created by juanf on 2024-09-05.
//

#include <cassert>
#include<iostream>

// Module 14

using std::cout, std::endl, std::string, std::cin;

// Macro variables
#define ARRAY_LENGTH 20 // Macro constant
#define PI 3.1416
#define MY_DOUBLE double
#define FAV_WHISKY "Forty Creek"

// Better alternative
const int ARRAY_SIZE = 25; // Replace for constexpr to instantiate at compile time
const double SMALL_PI = 3.1416; // Replace for constexpr to instantiate at compile time
typedef double A_DOUBLE;
const string WHISKY_BRAND = "Forty Creek";

// Macro method/function
#define SQUARE(x)((x)*(x))
#define AREA_CIRCLE(r) ((r)*(r)*PI)
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

int Module14_Macros_main()
{
    // The preprocessor and the compiler
    /*
     * - Preprocessor, runs before the compiler does.
     * - You can influence what is compiled through the use of preprocessor directives.
     * - Directives start with the (#) sign.
     * - The most common ones are include directives which you have been using so far to get access vectors, strings,
     *   amongst other types and algorithms.
     * - Another really common one is the (#define) directive which allows us to set macro constants and functions.
     *
     * - Macros (defined constants) under the hood just execute text substitution. The preprocessor does nothing
     *   intelligent. It simply replaces the identifier with other text, without validating the replacement.
     */

    // Using the Macro #define to define constants
    {
        /*
         * - This directive instructs the preprocessor to replace every instance of the Macro with the value it defines.
         * - Declaring macros is really simple:
         *   - #define identifier replacement-text
         *
         * - If you look at the top, we have defined the macro ARRAY_LENGTH 20.
         *  - Now, everytime the preprocessor encounters the text ARRAY_LENGTH, it will replace the text with the value
         *    it is defining. Whether it be a static array declaration, a variable, or even a loop.
         *
         * - Take another look at the top and analyze the other macros. As you can notice, the macro not only defines
         *   values, but it can also define types, strings, char*, and a multitude of other types!
         */

        cout << "Macro constants implementation!" << endl;

        int arr[ARRAY_LENGTH]= {0}; // Array declared with a macro constant using #define
        double radiuses[ARRAY_LENGTH]; // After preprocessor runs, the constant value is put in place of the text
        string names[ARRAY_LENGTH];

        for(int i = 0; i < ARRAY_LENGTH; ++i) // It even works on loops!
        {
            arr[i] = i + 1;
            cout << arr[i] << endl;
        }

        cout << "Array length: " << sizeof(arr)/sizeof(int) << endl;

        MY_DOUBLE radius = 0; // Macro for a type == double
        cout << "Enter radius: ";
        cin >> radius;
        cout << "Area is: " << PI * radius * radius << endl; // Use of macro that defines PI

        string myWhisky = FAV_WHISKY; // Macro for a string
        cout << "My favourite Whisky is: " << myWhisky << endl;

        const char* newString{FAV_WHISKY}; // Can also be used with old C-style strings
        cout << newString << endl;

        cout << "\n\n" << endl;

        /*
         * - Pretty handy right? However, these text replacements do have their drawbacks.
         * - The preprocessor does not check for the correctness of the substitution, it delegates that task to the
         *   compiler. However, you won't know about this error until later on when attempting to build the application.
         * - Another sort of issue that we can encounter is the vague definition of the macro type. Take PI for example.
         *   Is it a double, a float? The answer is neither. The preprocessor does not know the type, all it knows is
         *   that PI is a text substitution for the sequence 3.1416.
         *
         * - The better option is to just declare global const variables with a defined type and value. You can also
         *   make use of the typedef keyword to define an alias for a type:
         *   - typedef double MY_DOUBLE;
         */
    }

    // Using macros for protection against multiple inclusion (Circular Inclusion)
    {
        /*
         * - C++ programmers use another type of file knows ass header file to declare classes, methods, interfaces,
         *   and other elements to easily access them throughout an application.
         * - Methods and other logic operations are then declared in a paired .cpp file that includes the header file
         *   through the (#include<header>) preprocessor directive.
         * - This then allows multiple files to be aware of other data structures and implementations, allowing for more
         *   complex and modular designs. Unfortunately, there is a big risk associated with this, and that is, circular
         *   dependencies.
         *
         * - Circular dependency is an issue that presents itself when two files have #include references to one
         *   another (e.g. Class1 includes Class2, and Class2 includes Class1). This gets the compiler stuck in a
         *   recursive loop and prevents any compilation from happening.
         * - In order to avoid this issue, we can use macros in conjunction with the preprocessor directives [#ifndef]
         *   and [#endif]
         *
         * - #ifndef translates to: If-not-define. It is a conditional processing command that instructs the
         *   preprocessor to continue only if the identifier has not been defined. This check ensures that the
         *   preprocessor works on the lines that follow only once.
         *
         * - #endif marks the end of this conditional preprocessing instruction for the preprocessor.
         *
         * - Let's put into practice!
         *
         * =============================================================================================================
         * - Header 1 includes Header 2, which at the same time includes Header 1. In order to solve the circular
         *   problem we would do the following:
         *
         *   HEADER1.h
         *   #ifndef HEADER1_H_ -> multiple inclusion guard
         *   #define HEADER1_H_ -> preprocessor will read the following lines just once!
         *   #include<Header2.h>
         *
         *   class MyFirstClass{};
         *
         *   #endif -> end of header1.h
         *
         *   HEADER2.h
         *   #ifndef HEADER2_H_ -> multiple inclusion guard
         *   #define HEADER2_H_ -> preprocessor will read the following lines just once!
         *   #include<Header1.h>
         *
         *   class MySecondClass{};
         *
         *   #endif -> end of header2.h
         *
         * ============================================================================================================
         *
         * - When the preprocessor enters header1 in the first run and encounters the #ifndef statement, it notices that
         *   the macro HEADER1_H_ has not been defined and proceeds with the next lines.
         *  - The following lines define the macro header, ensuring that a second preprocessor run of this file
         *    terminates at the first line containing #ifndef.
         *  - The same will happen to header 2.
         *
         *  - This is one of the most common use of macro-based functionalities in the world of C++.
         *
         *  - C++20 introduced the concept of modules.
         *  - Modules provide a modern way of reusing code that was previously contained in header files.
         *  - They do not require multiple inclusion guards and drastically reduce the time required for compilation of
         *    particularly large code bases.
         *  - This topic will be further analyzed on its own module (Module 31).
         */
    }

    // Using #define to write macro methods
    {
        /*
         * - The processor at times can be used to write simple methods that perform simple logical operations.
         * - The syntax of macro functions is quite similar to that of a regular methods, with the biggest difference
         *   being the invocation method.
         *  - Macro methods are expanded inline before compilation, which can help improve code performance by
         *    eliminating the overhead of invoking a method.
         */

        cout << "Macro methods implementation" << endl;
        cout << "Enter an integer:";
        int number;
        cin >> number;

        cout << "Square of " << number << " is = " << SQUARE(number) << endl;
        cout << "Area of circle with radius " << number << " is: " << AREA_CIRCLE(number) << endl;

        cout << "Enter another integer:";
        int number2;
        cin >> number2;

        cout << "MIN(" << number << "," << number2 << ") = " << MIN(number, number2) << endl;
        cout << "MAX(" << number << "," << number2 << ") = " << MAX(number, number2) << endl;

        /*
         * - As previously mentioned, macros are not type sensitive, and macro functions can therefore cause many issues
         *   mainly when incompatible types are used and the lack of control for the return type.
         *
         * - Something you might have noticed whem looking at the macros, is the overuse of parentheses.
         * - #define MIN(a,b) (((a)<(b))?(a):(b))
         * - There are parentheses for every single element of the calculation, but why?
         * - That is because of how the macro gets evaluated as a text substitution mechanism by the preprocessor.
         *
         * - When we make the call for the macro method, in reality this is what gets sent to the compiler after the
         *   preprocessor realizes the substitution:
         *   - cout << (((number) < (number2)) ? (number) : (number2)) << endl;
         *
         * - If we were to use the macro without the parentheses, the implementation of the methos would be completely
         *   different!
         * - Lets use the area macro method to better exemplify the need of the parentheses.
         *   - #define AREA_CIRCLE(r) ((r)*(r)*PI)
         *
         * - If were to remove the parentheses and then make an inner calculation to get the value of r:
         *   - #define AREA_CIRCLE(r) (PI*r*r)
         *   - AREA_CIRCLE(4+6)
         * - The substitution result would look something like this:
         *   - (PI * 4+6 * 4+6) != (PI * 10 *10) -> This is the expected calculation we wanted.
         * - This would then get even crazier as the rules of operator precedence take over. In C++ multiplacations
         *   happen before addition, therefore, once the compiler is ready to run the calculation, this is what it would
         *   actually receive:
         *   - (PI * 4 + 24 * 6) NOTHING CLOSE TO THE ORIGINAL EXPECTED BEHAVIOUR!
         *
         * - In the absence of parenthese, plaintext conversion wreaks havoc on the programming logic and introduces
         *   many errors. Thus, the excesive use of parentheses is needed to keep the rules of operator precedence and
         *   properly evaluate the expression.
         *   - Once parentheses are added, this is what the compiler receives:
         *   - (PI * (4+6) * (4*6)) -> (PI * 10 * 10) -> Parentheses help to keep the order of operations!
         */
    }

    // Using the assert macro to validate expressions
    {
        /*
         * - The assert macro enables us to check for valid expressions or variable values.
         * - In order to use asserts, you do the following:
         *  - #include<cassert>
         *  - assert(expression that evaluates to true or false);
         */

        //char* sayHello = new (std::nothrow) char[25];

        // std::throw used with new in C++ to prevent it from throwing an exception if memory allocation fails.
        // Instead, it returns nullptr if allocation fails.

        //assert(sayHello != nullptr); // This will throw a message if pointer is Null

        /*
         * - assert() ensures that you are notified if the pointer is invalid.
         * - assert() is a great debugging feature, allowing you to validate input parameters of functions, validate
         *   memory was properly allocated, amongst other things.
         */

        //delete[] sayHello;
    }

    // Advantages and disadvantages of using macro methods
    {
        /*
         * - Macros are great tools to writing utility functions that can take on a variety of types and do not require
         *   complex processing to perform its operations. The macros we have in this file can accept int, float,
         *   double, and other numeric types, enticing code reusability.
         *
         * - Macro methods are also expanded inline before compilation, and thus, perform better as there is no overhead
         *   when compared to regular methods.
         *
         * - Unfortunately, macros do not support any form of type safety, which can compromise program quality.
         * - If complex macros are used, debugging them also becomes a major issue as they are expanded before compile
         *   time and not during run time
         */
    }

    // Final thoughts on Macros
    {
        /*
         * - Although a handy tool, use macros as infrequently as possible. You are better off writing a utility class
         *   that handles multiple operations or declaring other functions inline to optimize them. If you still decide
         *   to use macros, be careful and thorough with their implementation to minimize the risks to your application.
         * - Prefer the use of const variables rather than macros
         * - Macros are not type safe.
         * - Don't forget to surround with parentheses each variable in a macro function definition.
         * - Use asserts! They are a great debugging tool and the fun part is that they do not make it to the release
         *   build, they are only for testing.
         */
    }

    return 0;
}