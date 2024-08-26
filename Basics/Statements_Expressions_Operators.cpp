//
// Created by juanf on 2024-02-21.
//

#include <iostream>
#include <compare>
#include <bitset>

using std::cout;
using std::endl;

int Week05_main() {

    // Compound statement, also called a block
    // Delimited by {}, defined internally by programmer
    // Creates a scope for variables and methods, grouping statements that belong together -> be aware of scope!
    // If statements and loops make use of blocks for their logic
    {
        // Ways to write string literals statements
        cout << "Hello World" << endl;

        cout << "Hello"
                " World" << endl;

        // Be careful with the spacing of the second line
        // Any spacing will still be counted as a string literal space
        cout << "Hello \
World" << endl;

        // This case scenario will print extra tab spacing in the console (compiler dependant!)
        cout << "Hello \
            World" << endl;
    }

    {
        // Operators
        // Tools to process and transform data. We can also make decisions on the basis of the data we have.

        //Assignment Operator =
        // Replaces the value of the left operand with the one on the right operand
        int daysInYear {365};
        daysInYear = 366;

        // L-Value vs R-Value (left operand vs right operand
        // L values make reference to a location in memory (e.g variable name)
        //     - So basically they are handles/addresses to memory
        // R values are the data/information contained at that specific address, the raw content
        //
        // All L-values can be R-values, but not all r-values can be l-values
        // 365 = daysInYear
        // ^ is not a valid statement and as such won't compile

        // Mathematical operators +, -, *, / , %
        // Useful to perform arithmetic operations between operands
        const int number1 {22};
        const int number2 {5};
        int result {INT_MIN};

        result = number1 + number2; // 27
        result = number1 - number2; // 17
        result = number1 * number2; // 110
        result = number1 / number2; // 4
        result = number1 % number2; // 2
        // Modulo Operator works best with integers, as it returns the remainder of a division operator

        {
            // Increment and decrement operators (++, --)
            int num1 {100};
            cout << "Current value of number pre operators: " << num1 << endl;

            cout << "Postfix increment operator is invoked and l-value is: " << num1++ << endl;
            cout << "L-value ater postfix operator is applied: " << num1 << endl;
            cout << "Prefix increment operator is invoked and l-value is: " << ++num1 << endl;

            cout << "Postfix decrement operator is invoked and l-value is: " << num1-- << endl;
            cout << "L-value after postfix operator is applied: " << num1-- << endl;
            cout << "Prefix decrement operator is invoked and l-value is: " << --num1 << endl;

            // So how do they work?
            // Postfix operators assign the r-value (100) first to the l-value (variable num1) and after the assignment
            // was done, the r-value is incremented

            // Prefix operators first increment/decrement the value of the r-value (num1 + 1), and once it was modified,
            // the assigment to the l-value happens

            // Prefix operators are preferred as theoretically, it takes less processing power as the compiler does not
            // have to store the previous value of the variable before invoking the operators. On primitive data types
            // this performance optimization is negligible but on big objects/structs, it may help ease the compiler's
            // processing
        }

        {
            // Equality Operators (==, !=)
            // Result of evaluating if a certain condition has or not been fulfilled
            // The result of such equality check is a boolean
            int yourAge {100};
            bool checkEquality = (yourAge == 100); // True
            bool checkInequality = (yourAge != 20); // True
            checkEquality = (yourAge == 20); // False
            checkInequality = (yourAge != 100); // False
        }

        {
            // Relational Operators (<, >, <=, >=)
            // Helpful to check for inequality of a variable against a value
            // The result of these relational operators is a bool
            const int currentYear {2024};
            bool relationalCheck {false};

            relationalCheck = currentYear < 2025; // True, as one of the operands is smaller than the other
            relationalCheck = currentYear > 2023; // True, as one of the operands is greater than the other
            relationalCheck = currentYear >= 2024; //  True, as both operands have the same primitive value
            relationalCheck = currentYear <= 2025; //  True, as one of the operands is less than or equal to the other
        }

        {
            // Three-way comparison operator (<=>, also called the spaceship operator)
            // Modern way of speeding up relational checks
            // it combines all relational operands in one and, based on the output, reveals the relation between operands
            // Computes from left to right, using the first operand as the base for the relational checks
            // If the output of the operator is < 0, then operand 1 is less than operand 2
            // if the output is > 0, then operand 1 is greater than operand 2
            // if the output is == 0, then both operands have the same value

            const int num1 {10};
            const int num2 {20};
            auto threeWayComparison = (num1 <=> num2);

            if(threeWayComparison < 0) {
                cout << "num1 is less than num2" << endl;
            }
            else if (threeWayComparison > 0) {
                cout << "Num1 is greater than num2" << endl;
            }
            else if(threeWayComparison == 0) {
                cout << "Both numbers are equal" << endl;
            }
        }

        {
            // Logical operations using operators

            // Logical NOT operation
            // Supported by operator !
            // Works on a single operand
            // It inverses the supplied boolean flag
            bool logicalNot = true;
            cout << "Current bool flag: " << logicalNot << endl;
            logicalNot = !logicalNot;
            cout << "NOT operator applied! Current bool flag: " << logicalNot << endl;
            logicalNot = !logicalNot;
            cout << "NOT operator applied! Current bool flag: " << logicalNot << endl;

            // AND, OR, and XOR operators require 2 operands

            // Logical AND operation
            // Evaluates to true only when each operand evaluates to true
            // Supported by operator &&
            /*
             * Operand 1    Operand 2   Result of O1 AND O2
             * false        false       false
             * true         false       false
             * false        true        false
             * true         true        true
             *
             * if(O1 && 02) -> Perform logic
             */

            // Logical OR operation
            // Evaluates to true when at least one of the operands evaluates to true
            // Supported by operator ||
            /*
             * Operand 1    Operand 2   Result of O1 AND O2
             * false        false       false
             * true         false       true
             * false        true        true
             * true         true        true
             *
             * if(cheap || discounted) -> Buy the item
             */

            // Logical XOR operation
            // Exclusive OR
            // Evaluates to true when any operand is true, BUT! Is false when both are true, hence the EXCLUSIVE OR
            // Supported by operator ^
            /*
             * Operand 1    Operand 2   Result of O1 AND O2
             * false        false       false
             * true         false       true
             * false        true        true
             * true         true        false
             *
             * if(cheap ^ latestModel) -> Buy the item
             * buy an item if cheap or if its the latest model, but if its both cheap and the latest model, be wary!
             */
        }

        {
            // BITWISE OPERATORS
            // NOT (~)
            // AND (&)
            // OR (|)
            // XOR (^)

            // The main difference between logical and bitwise operations is the output result
            // Bitwise operators do not output a boolean value!
            // They work at a bit level, returning a result wherein individual bits in the operand where modified
            // When comparing with AND, OR, or XOR, we need to make use of a bit mask to compare the bits of the operand

            cout << "\n\nBitwise operators demonstration!" << endl;

            unsigned short inputNumber {0};
            //cout << "Enter a number (0 - 255): " << endl;
            //std::cin >> inputNumber;

            inputNumber = 100;

            // Bitset makes displaying binary data easier - a helper to visualize binary
            std::bitset<8> inputBits {inputNumber};
            cout << inputNumber << " in binary is: " << inputBits << endl;

            std::bitset<8> bitwiseNOT = (~inputNumber);
            cout << "\nBitwise NOT ~" << endl;
            cout << "~" << inputBits << " = " << bitwiseNOT << endl;

            cout << "\nBitwise AND, & with bit mask: 00001111" << endl;
            std::bitset<8> bitwiseAND = (0x0F & inputNumber); // 0x0F is hex for 0001111
            cout << "00001111 & " << inputBits << " = " << bitwiseAND << endl;

            cout << "\nBitwise OR, | with bit mask: 00001111" << endl;
            std::bitset<8> bitwiseOR = (0x0F | inputNumber); // 0x0F is hex for 0001111
            cout << "00001111 | " << inputBits << " = " << bitwiseOR << endl;

            cout << "\nBitwise XOR, ^ with bit mask: 00001111" << endl;
            std::bitset<8> bitwiseXOR = (0x0F ^ inputNumber); // 0x0F is hex for 0001111
            cout << "00001111 ^ " << inputBits << " = " << bitwiseXOR << endl;

            // As seen by the output, bitwise operators work on a deeper level, giving as a result a new set of bits
            // that is the direct result of comparing each individual bit
            // 01100100 - Integer 100 in binary
            // 00001111 - Binary mask
            // 01101111 - Bitwise OR == As long as one bit is true (1), the resulting bitwise operator returns that relationship
            //
            // This is all based out of the same truth tables for each logical operator, applied to each bit instead of the whole value
        }

        {
            // Bitwise shifting operators
            // Left shift operator (<<)
            // Right shift operator (>>)
            // These operators move entire bit sequences to the right or left
            // They help to perform multiplication or division by multiples of 2 a specific number of times

            // Shifting to the left 1 position multiplies the value by 2
            // 011 is binary for 3, if we apply bitwise left shift operator, the result is 110, which is binary for 6

            // Shifting to the right 1 position divides the value by 2
            // 110 = 6 in decimal, becomes 011, which is 3 in decimal

            // For either operator the syntax is as follows:
            // L-value + << + number of times you wish to divide or multiply by 2
            // E.G. myNumber << 2; This will multiply myNumber twice by 2 == myNumber * 2 * 2;

            // IMPORTANT TO NOTE!
            // Bitwise shift operators DO NOT rotate values!
            // The most significant bit IS NOT rotated back to the least significant bit, so signs stay the same!

            const int baseNumber {100};
            int bitwiseShiftedNumber {INT_MIN};

            cout << "\n\nBitwise shift operators!" << endl;
            cout << "Base number is: " << baseNumber << endl;

            cout << "Single Bitwise left shift<< (multiplication by 2): " << (baseNumber << 1) << " == (100 * 2)" << endl;
            cout << "Single Bitwise right shift >> (division by 2): " << (baseNumber >> 1) << " == (100 / 2)" << endl;

            cout << "Double Bitwise right shift << (multiplication by 2): " << (baseNumber << 2) << " == (100 * 2 * 2)"  << endl;
            cout << "Double Bitwise right shift << (division by 2): " << (baseNumber >> 2) << " == (100 / 2 / 2)"  << endl;
        }

        {
            // Compound assignment operators (+=, -+, *=, /=, %=, <<=, >>=, &=, |=, ^=)
            // Assignment operators where the left operand is assigned the value resulting from the operation
            const int initialValue {22};
            int num1 {initialValue};
            const int num2 {5};

            cout << "\n\nAssignment operators!" << endl;
            cout << "Initial left operand value: " << num1 << endl;
            cout << "Right operand value: " << num2 << endl;

            num1 += num2;
            cout << "Addition assignment +=: " << num1 << endl;

            num1 -= num2;
            cout << "Subtraction assignment -=: " << num1 << endl;

            num1 *= num2;
            cout << "Multiplication assignment *=: " << num1 << endl;

            num1 /= num2;
            cout << "Division assignment /=: " << num1 << endl;

            num1 %= num2;
            cout << "Modulo assignment %=: " << num1 << endl;

            num1 <<= num2;
            cout << "Bitwise left assignment <<=: " << num1 << endl;

            num1 >>= num2;
            cout << "Bitwise right assignment >>=: " << num1 << endl;

            cout << "Initial value reset!" << endl;
            num1 = initialValue;

            std::bitset<8> bitwiseBeforeAND(num1);
            num1 &= num2;
            std::bitset<8> bitwiseAND (num1);
            cout << "Bits before Bitwise AND assignment: " << bitwiseBeforeAND << endl;
            cout << "Bits after Bitwise AND assignment &=: " << bitwiseAND << endl;

            num1 = initialValue;
            std::bitset<8> bitwiseBeforeOR(num1);
            num1 &= num2;
            std::bitset<8> bitwiseOR (num1);
            cout << "Bits before Bitwise OR assignment: " << bitwiseBeforeOR << endl;
            cout << "Bits after Bitwise OR assignment |=: " << bitwiseOR << endl;

            num1 = initialValue;
            std::bitset<8> bitwiseBeforeXOR(num1);
            num1 &= num2;
            std::bitset<8> bitwiseXOR (num1);
            cout << "Bits before Bitwise XOR assignment: " << bitwiseBeforeXOR << endl;
            cout << "Bits after Bitwise XOR assignment ^=: " << bitwiseXOR << endl;
        }

        {
            // sizeof() operator
            // Determines the size in bytes of a particular type or variable present in memory
            // Looks like a function but in reality it is an operator
            // Useful when you need to dynamically allocate memory for N objects

            const int number{100};
            int numberArray[number];

            cout << "\n\nSizeof() operator!" << endl;
            cout << "Size in bytes of an integer: " << sizeof(int) << endl;
            cout << "Size in bytes of a static array of integers with a size of " << number << ": " << sizeof(numberArray) << endl;
            cout << "Size in bytes of the first element of the array: " << sizeof(numberArray[0]) << endl;
        }

        {
            // Operator precedence and associativity
            // Operator precedence is strictly specified by the C++ standard
            // It makes references to the order in which operators will be invoked after another

            // Operator associativity is also specified in the C++ standard
            // It makes reference to the order in which operators of the same precedence will be evaluated (Left to right / right to left)

            // The C++ standard has an operator precedence of 18 ranks
            /*
             * Precedence Rank     Name                             Associativity       Operator
             * 1
             *                     Scope resolution                 Left to right       ::
             * 2
             *                     Member selection                 Left to right       ., ->
             *                     Subscripting                     Left to right       ()
             *                     Increment                        Left to right       ++
             *                     Decrement                        Left to right       --
             * 3
             *                     sizeof()                         Right to left       sizeof()
             *                     Prefix increment                 Right to left       ++
             *                     Prefix decrement                 Right to left       --
             *                     Complement                       Right to left       ^
             *                     And, Not                         Right to left       &, !
             *                     Unary minus and plus             Right to left       -, +
             *                     Address-0f                       Right to left       &
             *                     Dereference                      Right to left       *
             *                     new, new[]                       Right to left
             *                     delete, delete[]                 Right to left
             *                     Casting                          Right to left       ()
             * 4
             *                     Member selection for pointer     Left to right       .*, ->*
             * 5
             *                     Multiply                         Left to right       *
             *                     Divide                           Left to right       /
             *                     Modulo                           Left to right       %
             * 6
             *                     Add                              Left to right       +
             *                     Subtract                         Left to right       -
             * 7
             *                     Bitwise shift left               Left to right       <<
             *                     Bitwise shift right              Left to right       >>
             * 8
             *                     Three way comparison                                 <=>
             * 9
             *                     Inequality relational            Left to right       <, <=, >, >=
             * 10
             *                     Equality                         Left to right       ==, !=
             * 11
             *                     Bitwise AND                      Left to right       &
             * 12
             *                     Bitwise XOR                      Left to right       ^
             * 13
             *                     Bitwise OR                       Left to right       |
             * 14
             *                     Logical AND                      Left to right       &&
             * 15
             *                     Logical OR                       Left to right       ||
             * 16
             *                     Conditional                      Right to left       ?:
             * 17
             *                     Assignment                       Right to left       =, *=, /=, %=, +=, -=, >>=, <<=, &=, ^=, |=
             * 18
             *                     Comma                            Left to right       ,
             */

            // Let's use this example to see in action
            // The operation is the same in all cases, but we break it down into smaller batches based on the operators precedence

            cout << "\n\nShowcasing operator precedence" << endl;
            int myNumber = 10 * 30 + 20 - 5 * 5 << 2;
            cout << myNumber << endl;
            myNumber = 300 + 20 - 25 << 2;
            cout << myNumber << endl;
            myNumber = 295 << 2;
            cout << myNumber << endl;
            myNumber = 295 * 4;
            cout << myNumber << endl;
        }
    }

    return 0;
}