#include <iostream>

int main_Extras()
{
    // Tokens
    {
        /*
         * - A token is the smallest individual element that of a program that is understood by a compiler.
         *
         * - A token in C++ can be:
         *  - Keywords: contain special meaning to the compiler.
         *  - Identifiers: Hold a unique value/identity.
         *  - Constants: variables that never change their value throughout the program.
         *  - Strings: That contain a homogenous sequence of data.
         *  - Special symbols: They have spacial meaning and cannot be used for other purposes.
         *  - Operators: To perform operations on the operand.
         */
    }

    // Differences between a pointer and a reference
    {
        /*
         * - References:
         *  - The value of a reference cannot be reassigned.
         *  - It can not hold a null value as it needs an existing value to become an alias of.
         *  - It cannot work with arrays.
         *  - It uses the dot operator to access members of a struct/class.
         *  - The memory location reference can be accessed easily and used directly.
         *
         * - Pointers:
         *  - The value of a pointer can be reassigned.
         *  - It can point to a null value either through NULL or nullptr.
         *  - It can work with arrays.
         *  - To access members of structs/classes it uses the member selection unary operator.
         *  - The memory location of a pointer cannot be accessed as easily, we first need to dereference the pointer.
         */
    }

    // Operator operations allowed in pointers
    {
        /*
         * - Increment decrement a pointer.
         * - Addition or subtraction of integer to a pointer.
         * - Comparison of pointers of the same type.
         */
    }

    // new vs malloc()
    {
        /*
         * - malloc()
         *  - Function that returns and accepts values.
         *  - Does not call the constructors.
         *  - Slower than new as it is a function and creates overhead.
         *
         * - new
         *  - operator that performs an action.
         *  - Does call the constructors.
         *  - Faster, as it is an operator.
         *  - returns the exact data type.
         */
    }

    return 0;
}
