//
// Created by juanf on 2024-03-13.
//

#include <iostream>

using std::cout, std::endl, std::cin;

int main()
{
    // Pointers
    {
        // - Pointers are variables that store an address in memory
        // - Pointers as any other variable occupy space in memory
        // - The value contained in a pointer is interpreted as a memory address

        // - * myPointer{} -> this is a variable stored at memory address 0x101
        // - myPointer = 0x558; The pointer variable points to the address 0x558
        // - 0x558 is a memory address that contains an integer with value 100
        // - My pointer makes reference ONLY to the address, NOT the data!

        // MEMORY LOCATIONS ARE REPRESENTED USING HEXADECIMAL NOTATION

        // POINTER DECLARATION
        /*
         * - Pointers are normally declared to point to an specific vlaue type
         * - The address contained in the pointer points to a location in memory that holds that type
         * - E.G. An int pointer will point to a location that contains an int
         *
         * - You can also declare void pointers. This type of pointer points to an unspecified type and directly addresses
         *   a block of memory
         *
         * - Pointer sysntax is as follows:
         *   [PointerType]* [PointerVariableName]
         *   int* pointerToInt;
         *
         * - Pointers, unless initialized, contain a random value/ We do not want this behaviour as this can cause the program
         *   to crash because we could be accessing invalid memory locations
         * - To avoid this problem, we initialize pointers with a null value
         * - NUll is a value that can be checked against and one that cannot be a memory address
         *
         * - Correct pointer declaration
         * int* pointerToInt = NULL;
         */

        // Determining the address of a varible using the reference operator
        {
            /*
            * In order to get the address in memory of a variable we need to make use of the reference operator &
            * This memory address is the location in which all of its data will be stored
            */

            int age{30};
            const double pi{3.1416};

            cout << "Determining addresses through & operator (Reference)" << endl;
            cout << "Integer age is locaed at 0x" << &age << endl;
            cout << "Const double pi is locaed at 0x" << &pi << endl;
        }

    }
}