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

        // Determining the address of a varible using the reference operator and assign it to a pointer
        {
            /*
            * In order to get the address in memory of a variable we need to make use of the reference operator &
            * This memory address is the location in which all of its data will be stored
            */

            const int age{30};
            const double pi{3.1416};

            cout << "Determining addresses through & operator (Reference)" << endl;
            cout << "Integer age is locaed at: " << &age << endl;
            cout << "Const double pi is locaed at: " << &pi << endl;

            // Using pointers to store an address
            // - To store an address, we declare a pointer of the same type and initialize the pointer to a variable's
            //   address using the reference operator

            const int* integerPointer{&age}; // Use of list initialization
            const double* doublePointer{&pi};

            cout << "\n\nStoring memory addresses in pointers!" << endl;
            cout << "Integer pointer for age points at: " << integerPointer << endl;
            cout << "Double pointer for pi points at: " << doublePointer << endl;

            // Once you run the program, you can see how both variables and pointers point to the same address
            // Pointers point to the aaddress assigned to the varibles at the top of this code segment

            // Pointers as any other variables CAN BE REASSIGNED!
            // Make sure the types are the same! Otherwise, you cannot assign it (E.g. int* cannot be assigned const int*)
            int dogAge{9};
            int humanAge{60};
            int* freePointer{&dogAge};

            cout << "\n\nReassigning pointers!" << endl;
            cout << "Integer pointer points to variable dogAge at: " << freePointer << endl;

            freePointer = &humanAge;
            cout << "POinter has been reassigned!" << endl;
            cout << "Integer pointer NOW points at humanAge with address: " << freePointer << endl;
        }

        // Accessing pointed data using Dereference (*) operator
        {
            // - Dereference operator allows us to access the address in memory and interact with the data stored at that location
            // - You need a valid pointer in order to dereference successfully. If not, the program might crash for accessing
            //   invalid memory locations

            int age{30};
            int dogAge{8};

            cout << "\n\nDereference operator (*) implementation!" << endl;

            cout << "Int age has the value: " << age << ". and the address: " << &age << endl;
            cout << "Int dogAge has the value: " << dogAge << ". and the address: " << &dogAge << endl;

            int* integerPointer{&age};

            cout << "Integer pointer points to age. Address is: " << integerPointer << endl;
            cout << "Accessing the data in the pointer using * operator (*integerPointer)" << endl;
            cout << "Value of data stored at pointerAddress is: " << *integerPointer << endl;

            integerPointer = &dogAge;

            cout << "Integer pointer points to dogAge. Address is: " << integerPointer << endl;
            cout << "Accessing the data in the pointer using * operator (*integerPointer)" << endl;
            cout << "Value of data stored at pointerAddress is: " << *integerPointer << endl;

            // - The application uses the address stored in the pointer as a starting point and based on the size of the type
            //   fetches that amount of memory to retrieve the data stored in that block
            // - Hence why it is imperative that you have a VALID memory address

            // MODIFYING THE VALUES OF A DEREFERENCED POINTER

            integerPointer = &age;

            cout << "\nDereferencing and modifying the value of a pointer's data!" << endl;
            cout << "Integer pointer points back to age. Address is: " << integerPointer << endl;
            cout << "Accessing the data in the pointer using * operator and modifying the stored value" << endl;
            *integerPointer = 5;
            cout << "Value of data stored at pointerAddress is: " << *integerPointer << endl;

            integerPointer = &dogAge;

            cout << "Integer pointer now points to dogAge. Address is: " << integerPointer << endl;
            cout << "Accessing the data in the pointer and modifying it" << endl;
            *integerPointer = 10;
            cout << "Value of data stored at pointerAddress is: " << *integerPointer << endl;

            cout << "Input a value for your desired age: " << endl;
            cin >> *integerPointer;
            cout << "Value of data stored at pointerAddress is: " << *integerPointer << endl;
            cout << "Value of data stored at the original Address is: " << dogAge << endl;

            // Any changes that happen to a dereferenced pointer will be reflected in the original variable/memory
            // This is because a pointer points to the same location, so any changes affect the data in memory itself
        }

        // How much memory does a pointer occupy?
        {
            // - Pointers contain a memory address, so regardless of the type of variable it is pointing to (int*, double*)
            //   the contents of a pointer will be an address (represented in hex numbers), nothing else
            // - With that in mind, the length of an address (number of bytes required to store it) is a constant size for a
            //   given system. The platform buildset and compiler being used will define this constant value
            // - Use sizeof() operator to check your systems size constant for an address

            cout << "\n\nPointer size comparisons!" << endl;
            cout << "Size of fundamental types" << endl;
            cout << "Size of char = " << sizeof(char) << endl;
            cout << "Size of int = " << sizeof(int) << endl;
            cout << "Size of double = " << sizeof(double) << endl;

            cout << "Size of pointers to fundamental types" << endl;
            cout << "Size of char* = " << sizeof(char*) << endl;
            cout << "Size of int* = " << sizeof(int*) << endl;
            cout << "Size of double* = " << sizeof(double*) << endl;

            // - As seein in the implemetation above, regardless of the type of variable, a pointer will occupy the same space
            //   in memory even though its fundamental type might only require a single byte of data
            // - For a 64-bit system, the address length tends to be 8 bytes
            // - For a 32-bit system, the address length tends to be 4 bytes
        }
    }

    // Dynamic Memory Allocation
    {
        /*
         * - In order to write an application that is able to optimally consume memory resources based on the needs of
         *   the user, we need to dynamically allocate memory. This will allow us to allocate more memory when we need
         *   more resources, and to release memory when we have an excess of it
         * - C++ supplies two operators for better managing memory consumption:
         *      - new operator
         *      - delete operator
         * - Pointers play a critical role in efficient dynamic memory allocation
         */

        // Dynamic Memory Allocation using new and delete operators
        /*
         * - We use new to allocate memory blocks
         * - Most frequent usedf form of new returns a pointer to the allocated memory if successful. If not, an exception occurs
         * - When using new, you must specify the data type for which memory is being allocated
         *      Type* pointer = new Type;
         * - The syntax above requests memory for one element
         *
         * - We can also specify the number of elements we want to allocate that memory for
         *      Type* pointer = new Type[NumberOfElements]
         *
         * - [new] indicates a request for memory. However, there is no guarantee this call will always succeed.
         *   Memory being allocated depends on the state of the system and how much memory is available
         * - Any allocation that uses [new] needs to be eventually released using an equal and opposite deallocation [delete]
         * - [delete] is used for a single element
         * - [delete[]] is used for clearing a block of memory
         *
         * - IF you do not release memory once it is no longer needed, that memory remains reserved and allocated for your application
         * - This reduces the amount of system memory available for application consumption, slowing down the execution
         * - This is called a LEAK AND SHOULD BE AVOIDED AT ALL COST!
         */

        int* pointToInt = new int{10};
        int* pointToNums = new int[10];

        delete pointToInt; // release memory allocation for one element
        delete[] pointToNums; // release memory block -> DONT FORGET THE "[]". If you do you only release the head of the memory block!

        cout << "\n\nDynamic Memory allocation!" << endl;
        int* ageData = new int;
        cout << "Enter an age value: " << endl;
        cin >> *ageData; // Remember to dereference so we can modify the addresse's data
        cout << "Age: " << *ageData << " is stored at: " << ageData << endl;
        delete ageData; // ALWAYS ENSURE YOU RELEASE ALLOCATED MEMORY!!!!

        // - The address above containing the age value was given by the application when the new keyword was called
        // - [new] returns a pointer (an address in memory), so that is why we use pointers as the variables to store
        //   dynamic allocated memory
        // - [delete] can only be invoked on an address that has been returned by the new operator!
        //      DONT DELETE regular pointers! Let the application handle the release of regular primitive pointers

        cout << "\n\nDynamic Memory block allocation!" << endl;
        int memorySize{INT_MIN};
        cout << "Enter the number of elements you wish to allocate: " << endl;
        cin >> memorySize;
        int* myBlock = new int[memorySize];
        cout << "Memory block allocated at: " << myBlock << endl;
        delete[] myBlock; // De-allocate the entire block. USE []! Avoid dangling pointers and leaks!

        // The code above allocates a block of memory that will change based on your input

        /*
         * - new and delete operators allocate and de-allocate memory from the free store
         * - The free store is a memory abstraction in the form of a pool of memory where an application can reserve (allocate)
         *   and release (de-allocate) memory to
         */
    }

    // Special operations with pointers
    {
        // Effects of the Increment (++) and Decrement (--) operators on pointers
        {

        }

    }
}