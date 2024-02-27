//
// Created by juanf on 2024-02-25.
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

using std::cout;
using std::endl;
using std::string;

template<typename T>
void printTypeInfo(T value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "The value is an integral type: " << value << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "The value is a floating point type: " << value << std::endl;
    } else {
        std::cout << "The value is of an unknown type." << std::endl;
    }
}

int main() {

    // Use of conditional evaluation expressions and constructs (If, Switch, If constexpr)
    {
        {
            // If... Else
            // A construct for conditional execution
            // Based on wether a conditional variable evaluates to true or false, certain code statements will be excuted or ignored

            bool willMultiply;
            const int num1 {10};
            const int num2 {10};
            int result {0};

            std::srand(std::time(nullptr));

            willMultiply = rand() % 2;

            if(willMultiply) {
                result = num1 * num2;
            }
            else {
                result = num1 + num2;
            }

            cout << "Result of conditional operation: " << result << endl;
        }

        // In C++, when evaluating a conditional expression, any value that is nonzero(0, null, nullptr, empty, etc.) will be considered true
        // Else constructs are optional. They are not needed in situations where there is nothing to be executed in the event of a false result.

        // IF statements, just any other expressions, are bound to a scope.
        // Statements inside an If construct, are considered to be compound statements/blocks, and as such, once outside the scope, the data
        // will cease to exist and the memory will be released (make sure to ensure proper memory cleaning when allocating memory dynamically)
        {
            cout << "\n\nSafe char[] management" << endl;
            cout << "Input a line of text: " << endl;
            string userInput {};
            char copyInput[20] {};

            //std::getline(std::cin, userInput);
            userInput = "C++ is awesome!";

            if(userInput.length() < 20) {
                // All the statements inside this if block will cease to exist in memory once outside of this scope...
                cout << "Input within bounds. Creating copy!" << endl;
                userInput.copy(copyInput, userInput.length());
                cout << "Copy input contains: " << copyInput << endl;
            }
            else {
                cout << "Text bounds exceeded... Cannot copy!" << endl;
            }

            // From C++17 and on, if statement initialization was added.
            if(char otherBuffer[20]; userInput.length() < 20) {
                // Now the buffer for the static char array will only exist within the scope of this if construct block
                // If you try to use it outside this scope, the program will fail to compile
                // You can still use the initialized buffer under other if else, else blocks that belong to that if construct
                cout << "Input within bounds. Creating copy!" << endl;
                userInput.copy(otherBuffer, userInput.length());
                cout << "Copy input contains: " << otherBuffer << endl;
            }
            else if(userInput.length() > 20) {
                userInput.copy(otherBuffer, userInput.length());
            }

            userInput = "A new string!";
            // Trying to compile this statement will fail, as the otherBuffer variable no longer exists (out of scope, deallocated)
            // userInput.copy(otherBuffer, userInput.length());

            // All variables and memory inside this scope will cease to exist and be released once outside this block
            // Something important to understand early on as it will affect the execution of nested statements
        }

        // Nested IF statements
        {
            // Nested If statements
            // Useful when the evaluation of a condition is dependant on the evaluation of a previous conditional value
            // Be aware of scopes and where variables are being initialized to ensure proper program flow
            std::srand(std::time(nullptr));

            const float num1 {static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 10.0f)};
            const float num2 {static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 10.0f)};
            bool willMultiply = rand() % 2;
            float result {0};

            // Top if statement
            if(!willMultiply) {
                // Nested If statement to check if the divisor is non-zero
                // Any variable or expressions created inside this scope, will not be visible to the top if statement
                // They will be visible to all consecutive nested if staments inside each respective construct
                if(num2 != 0) {
                    result = num1 / num2;
                }
                else {
                    cout << "Can not divide by zero!" << endl;
                }
            }
            else {
                // Else construct that belongs to the top statement
                result = num2 + num1;
            }
        }

        // Switch construct
        {
            // Conditional processing with Switch-case statements
            // Another type of construct
            // Enables to check a particular expression against a host of possible constants and perform different actions for each of those values

            // Code evaluates the expression and checks for each of the case labels following it for equality (expresion == case label)
            // Each labes has to be constant
            // Program will execute statements inside the case lable block that match the equality (expression == case label)
            // Makes use of special keyword: break. This keyword indicates the program to exit the block of code that belongs to the construct and execute the next statements
            //      Breaks are not compulsory. However, if not placed, the code will then go and evaluate all the remaining case labels until there are no more case labels
            //      or a default case label is reached
            // Default labels are executed when the expression does not equate to any of the labels in the switch construct

            cout << "\n\nSwitch constructs!" << endl;

            std::srand(std::time(nullptr));

            enum DaysOfTheWeek {
                Sunday = 0,
                Monday,
                Tuesday,
                Wednesday,
                Thursday,
                Friday,
                Saturday
            };

            const DaysOfTheWeek day = static_cast<DaysOfTheWeek>(rand() & 8);

            switch (day)
            {
                // Inside this block, it is an internal scope, so variables declared inside are not visible to the top scope
                case Sunday:
                    // When declaring variables inside a switch, separate initialization as to avoid cross initialization errors
                    // The errors occurs because you are jumping past the initialization of the variable when going from case to case
                    unsigned short switchVar;
                    switchVar = 10;
                    cout << "It is Sunday!" << endl;
                    break;
                case Monday:
                    // Variable is visible here as all the implementation of a switch statement is considered to be in the same scope
                    // Unless indicated by statement blocks, the concept of separate scopes per case is not valid and all lives in a global switch space
                    switchVar = 20;
                    cout << "Its is Monday!" << endl;
                    break;
                case Tuesday: {
                    // However, if statement blocks are used, the compiler interprets it as a separate nested scope
                    // Therefore, contrary to myVar, expressions inside this scope will cease to exist once outside the case
                    unsigned short thisVar {20};
                    cout << "Its is Tuesday!" << endl;
                    break;
                }
                case Wednesday:
                    // If you uncomment the line below, you get an error: Cannot resolve symbol as the variable only exists in Tuesday's scope
                    //thisVar = 30;
                    cout << "Its is Wednesday!" << endl;
                    break;
                case Thursday:
                    cout << "Its is Thursday!" << endl;
                    break;
                case Friday:
                    cout << "Its is Friday!" << endl;
                    break;
                case Saturday:
                    cout << "Its is Saturday!" << endl;
                    break;
                default:
                    cout << "Not a valid day of the week! Try again..." << endl;
                    break;
            }

            // Variable does not exist in this scope as it was declared in the switch construct
            //myVar = 10;

            // IMPORTANT NOTES!
            // DON’T add two cases with the same label as it won’t make sense and won’t compile.
            // DO not rely solely on sequence and avoid break statements, this can break functionality! Always add them for the sake of safety
        }

        // Conditional execution with conditional operator
        {
            // Conditional operator is similar to a compact if-else construct
            // Also called ternary operator, as it takes three operands
            // It follows this structure:
            // (conditional expression evaluated to a bool) ? expression if evaluation == true : expression if evaluation == false
            const short num1 {20};
            const short num2 {50};
            short max = (num1 > num2) ? num1 : num2; // The result will be 50, as 50 is the greater number

            // The stement above encapsulates the following construct:
            if(num1 > num2) {
                max = num1;
            }
            else {
                max = num2;
            }

            // As can be seen, ternary operators save a lot of space in coding, but they should be written in a clear manner as to not confuse people
        }

        // Conditional compilation
        {
            // C++ 17 addition
            // Uses if constexpr
            // Gets the compiler to validate the conditional expression
            // Then code within a conditional if constexpr that is not to be executed is ignored by the compiler and is not part of the executable
            // Helpful on template classes
            // See example templetized function at the top ^

            printTypeInfo(10);    // Will trigger the integral type branch
            printTypeInfo(3.14);  // Will trigger the floating point type branch
            printTypeInfo("Hello World");  // Will trigger the unknown type branch

            // Because all the arguments provided are literals, they count as constants, and as such, the compiler will evaluate the conditions and have the result reeady
        }
    }

    // Use of loops
    {
        // Loops are ways to repeat the execution of code
        // They can vary from very simple loops, to advanced implementations that make use of nested loops, threads, and network replication
        // Also called iterations. Any statement that triggers a loop is called an iterative statement

        // Go To loop
        {
            // Rudimentary loop
            // Instructs code to continue execution from a particular, labeled point in code
            // Can be used to go backwards and re-execute certain staments

            // Simple declaration of the loop
            //Start: // Create a label that will be the identifying point of code to execute
            //result += num1;
            //goto Start; // Use the goto keyword to jump to that labeled point and continue execution from there

            // Simple but dangerous!
            // The code above will never exit and will continue to run perpetually because of memory overflow resetting the values of the integer
            // You should make sure to invoke goto with a statement that can valuate to false and end the loop, or have a return statement in the repeated piece of code
            //      that will exit the loop

            const short num1 = 5;
            unsigned int result{0};
            const char repeatCharacter = 'y';
            char input {};

            cout << "\n\nGo To loop implementation!" << endl;
            cout << "value to be added in each loop iteration: " << num1 << endl;
            cout << "Current value: " << result << endl;
        RepeatCalculation:
            result += 5;
            cout << "Current value: " << result << endl;
            cout << "Want to repeat the process? (y/n)" << endl;
            std::cin >> input;
            //input = 'n';

            if(input == repeatCharacter) {
                goto RepeatCalculation;
            }

            cout << "Goodbye!" << endl;

            // HOWEVER!!!! DO NOT USE GOTO!
            // It is a messy way of creating code flow and can become unpredictable and volatile with dynamic memory that was not released
            // Use the better ways to code loops as explained in the following cases
        }

        // While loops
        {
            // Construct that repeats the execution of code as long as a condition evaluates to true
            // Important to design the code in the while loop with the faculty to evaluate the condition to false and exit the construct

            const short num1 = 5;
            unsigned int result{0};
            const char repeatCharacter = 'y';
            char input {};

            cout << "\n\nWhile loop implementation!" << endl;
            cout << "value to be added in each loop iteration: " << num1 << endl;
            cout << "Current value: " << result << endl;

            // The condition in the loop determines when to exit the loop
            // Always make ensure there is a way out of the loop
            while(input != repeatCharacter) {
                result += 5;
                cout << "Current value: " << result << endl;
                cout << "Want to exit? (y/n)" << endl;
                std::cin >> input;
                //input = repeatCharacter;
            }

            cout << "Goodbye!" << endl;
        }

        // Do-While loops
        {
            // Similar syntax and exit conditions as a while loop
            // The only difference is that this loop will trigger the contents inside of the construct at least once
            //      before evaluating the loop condition

            const short num1 = 5;
            unsigned int result{0};
            const char repeatCharacter = 'y';
            char input {'y'}; // Pay attention to this line!

            cout << "\n\nDo While loop implementation!" << endl;
            cout << "value to be added in each loop iteration: " << num1 << endl;
            cout << "Current value: " << result << endl;

            // Even though the char input was initialized with the character to finalize the loop, the segment inside the loop
            // will run once before and then ask the user for input, ensuring that the initial calculation will happen even if
            // the condition to exit the loop was already set
            do {
                result += 5;
                cout << "Current value: " << result << endl;
                cout << "Want to exit? (y/n)" << endl;
                std::cin >> input;
                //input = repeatCharacter;
            }while(input != repeatCharacter);

            cout << "Goodbye!" << endl;
        }

        // For loops
        {
            // Sophisticated loop that allows for an initialization statement executed once, a check for an exit condition, and an action to be performed
            //      at the end of every iteration

            // Syntax is as follows:
            /*
            for (initial expression executed only once;
                exit condition executed at the beginning of every loop;
                loop expression executed at the end of every loop)
            {
                DoSomething;
            }
             */

            // Helpful construct that allows programmers to define a counter with an initial value
            // Check that value against the exit condition of the loop every iteration
            // Modify the value of the variable at the end of the loop in order to reach the exit condition

            cout << "\n\nFor Loop implementation" << endl;
            const int MAX_ARRAY_SIZE {5};
            const int myArray[MAX_ARRAY_SIZE] = {0,1,2,3,4};

            for(int i = 0; i < MAX_ARRAY_SIZE; ++i) {
                cout << "Element of array number [" << i << "] is: " << myArray[i] << endl;
            }

            // The variable that helps access the elements in a collection such as an array is called an iterator
            // The scope of an iterator declared in the for loop is limited to that specific construct and will not exist outside of it

            // Due to the nature of for loops, there are multiple ways to declare them and use them
            // One such case is the use of a for loop without a loop expression (The third parameter of the declaration)

            cout << "\n\nFor loop with no loop expression" << endl;
            for(char userSelection = 'm'; userSelection != 'x';) {
                cout << "Enter two integers" << endl;
                int num1, num2 = 0;
                std::cin >> num1;
                std::cin >> num2;

                cout << num1 << " X " << num2 << " = " << num1 * num2 << endl;
                cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;

                cout << "Press x to exit or any other key to iterate the loop" << endl;
                //std::cin >> userSelection;
                userSelection = 'x';
            }

            cout << "Out of loop with no loop expression" << endl;

            // You can initialize multiple variables in a for loop within the first initialization expression
            // You can also modify the value of multiple variables in the loop expression
            cout << "\n\nLoop with multiple variables being initialized and modified" << endl;

            for(int counterA = 0, counterB = 5; counterA <= 5; ++counterA, --counterB) {
                cout << "First variable value: " << counterA << endl;
                cout << "Second variable value: " << counterB << endl;
            }
        }

        // Range based for loops
        {
            // Added in C++ 11
            // Simpler way to write and read collections
            // Uses the same keyword as a for loop

            // Syntax for it:
            // for(varType variable : seqeunce )
            // {
            //     Use variable for logic pertaining to the element inside the logic...
            // }

            cout << "\n\nRange based for loop implementation!" << endl;

            const int someNums[] = { 1, 101, -1, 40, 2040 };

            for (int aNum : someNums) // range based for
            {
                cout << "The array elements are " << aNum << endl;
            }

            // Can be simplified by using the auto keyword to make it variable type deducting and speed your workflow
            for (auto aNum : someNums) // range based for
            {
                cout << "The array elements are " << aNum << endl;
            }

            int someOtherNums[] = { 1, 101, -1, 40, 2040 };

            for (const int aNum : someNums)
                   cout << aNum << ' '; cout << endl;

            for (auto anElement : { 5, 222, 110, -45, 2017 })
                cout << anElement << ' ';
            cout << endl;

            char charArray[] = { 'h', 'e', 'l', 'l', 'o' };
             for (auto aChar : charArray)
                 cout << aChar << ' ';
            cout << endl;

            double moreNums[] = { 3.14, -1.3, 22, 10101 };
            for (auto anElement : moreNums)
                cout << anElement << ' ';
            cout << endl;

            string sayHello{ "Hello World!" };
            for (auto anElement : sayHello)
                cout << anElement << ' ';
            cout << endl;
        }

    }


    return 0;
}