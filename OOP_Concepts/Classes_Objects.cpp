//
// Created by juanf on 2024-03-20.
//

#include <iostream>
#include <chrono>

using std::cout, std::endl, std::cin, std::string;

int main()
{
    /*
     * - So far the content from the previous modules covers procedural programming
     * - However, on moden day c++, Object oriented programming is the go to for the language
     *
     * - The base concepts of object oriented programming are classes and objects
     *
     * - CLASSES:
     *  - Classes are constructs in which we can group especific attributes (Data) and functions (methods)
     *  - Classes are definied in C++ with the keyword class, followed by the name of the class and a statement block
     *    - Inside the statement block, we will find the MEMBER attributes and methods (Member = internal/specific to that class)
     *  - Classes by themselves do not affect the execution of a program, as they have to be invoked and used as you would a function
     *  - Think of classes as custom data types that enable us to ENCAPSULATE attributes and methods that work making use of those attributes
     *
     * IMPORTANT CONCEPTS!
     * - ENCAPSULATION: Ability to logically group data and methods that work with said data
     *
     * - OBJECTS
     *  - Objects are instances of a class, encapsulating data and behaviour
     *  - By using objects, we can access member attributes and methods from the class an object was created from
     *  - Creating an object of any class is similar to creating an instance of any other data type
     *  - We can also dynamically create an object by using the new operator. Deallocate the object once no longer in use
     *
     */

    class Human
    {
        // Member attributes
        string name;
        std::chrono::year_month_day dateOfBirth;
        string placeOfBirth;
        string gender;

        // Member methods
        void Talk(const string& textToTalk);
        void IntroduceSelf();
    };

    //
    Human firstMan;

}