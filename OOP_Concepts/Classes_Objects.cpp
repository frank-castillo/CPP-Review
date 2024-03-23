//
// Created by juanf on 2024-03-20.
//

#include <iostream>
#include <chrono>

using std::cout, std::endl, std::cin, std::string;
using namespace std::chrono;

class MyBuffer
{
public:
    explicit MyBuffer(const unsigned int length)
    {
        cout << "Constructor allocates: " << length << " integers" << endl;
        myNums = new int[length]; // Dynamic memory!
    }

    ~MyBuffer()
    {
        cout << "Destructor called. Clearing memory buffers..." << endl;
        delete[] myNums; // Deallocate memory, return it to the free memory pool
    }

    void PrintAddress()
    {
        cout << "Buffer stored at address: " << &myNums << endl;
    }

private:
    int *myNums;
};

void UseMyBuffer(MyBuffer copyBuffer)
{
    cout << "Buffer copy will be destroyed once out of the function." << endl;
    copyBuffer.PrintAddress();
}

int main()
{
    // Basics of Object Oriented Programming
    {
        /*
        * - So far the content from the previous modules covers procedural programming
        * - However, on moden day C++, Object oriented programming is the go to for the language
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
        * - NAMING CONVENTIONS
        *   - Class names and member methods are declared in PascalCase
        *   - Member attributes and variable declaration in camelCase
        *
        * - OBJECTS
        *  - Objects are instances of a class, encapsulating data and behaviour
        *  - By using objects, we can access member attributes and methods from the class an object was created from
        *  - Creating an object of any class is similar to creating an instance of any other data type
        *  - We can also dynamically create an object by using the new operator. Deallocate the object once no longer in use
        *
        * - ACCESSING MEMBERS VIA DOT OPERATOR(.)
        *  - Attributes exist only when an object has been instantiated at runtime
        *  - Dot operator allows us to access member variables and methods that belong to the class type of the object
        *  - When working with object pointers of a class type, you can access their members 2 ways:
        *      - Using the pointer operator(->)
        *      - Using the indirection operator (dereference operator) '*' to reference the object following the dot operator
        *
        * - ACCESSING MEMBERS VIA POINTER OPERATOR(->)
        *  - Use whenever an object is dynamically allocated or there is a pointer pointing to an object
        *
        * - PROTECTING CLASSES! PUBLIC, PRIVATE, (and later on PROTECTED) KEYWORDS
        *  - C++ allows us, the programmer, to control how we want to expose and manipulate the data attributes of a class
        *  - By making use of the keywords public, private, or protected, we control how the class' attributes will be accessed
        *    by external objects/methods and the functionality we will allow to be exposed to the application in general
        *
        *  - PUBLIC class members can be accessed, set, and used by anyone in possesion of an object of a class
        *  - PRIVATE class members can only be accessed by the class and its "FRIEND CLASSES". However, objects can only access
        *    their private data and wont be allowed to modify another's object members, even if they are the same type
        *  - Protected class members will be inherited to child classes and accessible from this new child classes (more on this later)
        *
        * - WHY WOULD WE USE THIS? FOR DATA ABSTRACTION!
        *  - With C++, we are in control to decide which information remains unreachable to the outside world, while also enabling us
        *    to control and provide custom access methods to private members. This way, we have far more control on how data being
        *    given and requested from the class is processed, preventing otehr classes and functions from accessing data they should
        *    not be able to modify
        *  - This way we abstract member information and keep it known only to the class and its friends, soley providing what
        *     is needed from the class through methods that expose only what we want to expose
        *
        */

        // Simple Implementation of a class (All members are public, very DANGEROUS unless this is the desired design!)
        class Human
        {
        public:
            // Member attributes
            string name;
            std::chrono::year_month_day dateOfBirth;
            int age;

            // Member methods
            void Talk(const string &textToTalk);

            void IntroduceSelf() const // Use of const here to prevent changes to any member inside this function
            {
                // Classes are usually written and divided in a class file (Header and CPP). For now, we will keep it simple!
                cout << "My name is: " << name << ". I am " << age << " years old, and was born on: " << dateOfBirth <<
                        endl;
            }
        };

        // Regular object instance of type Human
        Human firstMan;

        // Dynamically allocated type Human
        Human *firstWoman = new Human{};

        // Non pointer member variable access
        firstMan.name = "Robert";
        firstMan.age = 34;
        firstMan.dateOfBirth = std::chrono::year_month_day(1990y, std::chrono::January, 20d);

        // Pointer member variable access
        firstWoman->name = "Ana";
        firstWoman->age = 32;
        firstWoman->dateOfBirth = std::chrono::year_month_day(1992y, std::chrono::March, 15d);

        // Non pointer member method access
        firstMan.IntroduceSelf();

        // Pointer member method access (Indirection operator)
        (*firstWoman).IntroduceSelf();

        // Pointer to a Human object and use of pointer operator
        Human *doppleganger = &firstMan;
        doppleganger->IntroduceSelf();

        delete firstWoman; // Proper memory clean-up
    }

    // Methods and functionality of classes
    {
        // - Classes in C++ have methods and functionality that only exist for this type of construct

        // CONSTRUCTORS
        {
            /*
             *- Special method that gets invoked during the instantiation of a class to constrcut an object
             *  - Constructors, being methods, can be overloaded
             *  - Consructors are declared by taking the name of the class and constructing a method with it. It has no return value!
             *  - Constructors can be declared inline within the class or outside the class declaration
             *      - When declared outside the class, you have to use the scope resolution operator (::) to directly target the
             *        member of the class
             *  - Constructors are the perfect place to initialize class member variables
             *  - A constructor that does not accept any arguments is called a DEFAULT CONSTRUCTOR
             *    - Default constructors are optional, and if you do not write one, the compiler will try its best to deduce
             *      a default one and construct member attributes. However, it will not initialize them to any default value
             *  - Depending on the design of your class, you can opt for not having a default constructor and just using an
             *    overloaded one. If that happens, the compiler will not generate a default constructor and will instead, enforce
             *    the use of the overloaded constructor.
             *  - Constructors can have default values for its arguments, and follow the same syntax
             *  - Constructors can make use of initialization lists to initialize member variables. (See info below)
             *
             * - SPECIAL NOTE ON CONSTRUCTORS
             *  - Constructors that have default values for all arguments, are interpreted as default constructors because an
             *    an object can still be instantiated with no arguments to initialize member variables
             *  - Constructors can be set as constexpr and be called at compilation time
             *  - Constructors that contain parameters are also called converting constructors. It implicitly converts the
             *    parameter list into the type being constructed. To avoid implicit conversion, specially on constructors
             *    that only take a single parameter, we use the keyword explicit at the beginning of a constructor declaration
             *    - Jump to the end for more details
             *
             * - INITIALIZATION LISTS
             *  - Initialization lists provide a way to initialize class members within the constructor
             *  - They are more efficient and performant because they construct objects directly inside the member variables.
             *    So instead of first calling a constructor and then an assignment operation, the data is initialized directly
             *    on the member variable
             *  - They are essential for initializing:
             *      - Base classes that do not make use of default constructors and use specific arguments
             *      - Const members
             *      - Reference members
             *  - Prevent default construction by calling the appropriate constructor for each member variable, avoiding memory
             *    overhead from having to create a new object and then assign it
             *  - USE INITIALIZATION LISTS OVER CONSTRUCTOR ASSIGNMENT!
             */
        }

        // Destructors
        {
            /*
             * - Invoked when an object gets destroyed
             * - Declared by adding a tilde before the name of the class ~ClassName() {}
             * - Just like constructors, they can be implemented inline or outside the class declaration
             * - Always invoked when an object goes out of scope or is deleted via delete operator
             * - Perfect place to reset variables and release dynamically allocated memory and other resources
             * - Destructors CAN NOT be overloaded
             * - A class can only have one destructor
             * - If you do not implement one, the compiler will create an empty one. HOWEVER, this empty destructor WILL
             *  NOT clear any dynamically allocated memory, causing memory leaks
             */
        }

        // Copy Constructors
        {
            // - Before we delve deeper into this topic, first we need to understand how the C++ compiler handles
            //   copying variables and objects

            // SHALLOW COPIES
            {
                /*
                 * - Shallow copies are the default behaviour of many programming languages
                 * - Unless dealing with simple data, shallow copies can be threats to the stability of an application!
                 * - Shallow copies copy all of the member field values (varibles & methods) of an object
                 * - Any references (memory address) to other objects, pointers, or blocks of memory will be copied as is,
                 *   meaning that the copied object will be pointing to the same memory location as the original object
                 * - With this in mind, any changes to the member variables that happen either in the original object or
                 *   the copied object, will be reflected on all instances!
                 * - What this means, is that if we were to change the value of an integer pointer in a shallow object, the
                 *   value/data of that variable will also change in the original object, because they share the same memory
                 *   address references
                 */

                cout << "\n\nShallow copy demonstration!" << endl;
                MyBuffer firstBuffer{5};
                UseMyBuffer(firstBuffer);

                /*
                 * - Depending on your compiler and toolset, some behaviours might not happen
                 * - On g++ and MSVC, the application will crash at this point because of a duplicate delete call to a block of
                 *   memory that has already been cleared. This happened because the method UseMyBuffer creates a shallow copy
                 *   of the object being passed as an argument. Once the copy goes out of scope, it clears the same block of
                 *   memory that the original object is pointing to, and once the original object clears its memory, the app
                 *   will crash because of the duplicate delete calls to an already cleared block.
                 * - This goes on to show why shallow copies are so dangerous and why the default copy method in C++ is not
                 *   safe when dealing with complex/custom types
                 */
            }

            /*
             * - On shallow copies, the copy method used is known as a binary copy.
             * - This binary copy makes plain copies of the exisiting data in members, disregarding any other information
             * - This is why pointers values, which are just memory addresses, are the same, the compiler does not care
             *   nor is aware of the block of memory, all it knows is the pointer has a valid address and that is the value
             *   it will copy on the new copy-object
             * - For this reason, we have to ensure that whenever we are going to make copies of any objects or variables
             *   containing pointers or dynamically allocated memory, to perform a DEEP COPY, eliminating this way any of
             *   the program breaking errors introduced by shallow copies
             */

            // DEEP COPIES
            {
                /*
                 * - Deep copies are a more complete and safe solution to avoid the problems caused by shallow copies
                 * - Deep copies will copy as is all the primitive member variables, ensuring both the original object and
                 *   the copy have the same data. However, for all dynamically allocated memory data and objects that are
                 *   being pointed to by the original instance, new blocks and addresses of memory will be created.
                 * - Once these new blocks of memory have been allocated, we will duplicate one by one the values contained
                 *   in the original instance into the copy's newly allocated memory, effectively creating a DEEPER COPY
                 * - This way, any new object that is a copy of another, will have the same values as the original but will
                 *   have different memory addresses for all pointers and dynamically allocated memory, effectively creating
                 *   an independent instance that will never modify the original objects values and only manages its own memory
                 * - However, the compiler has no way to understand and automatically do this advanced deep copy by itself,
                 *   so, it is our job, as the programmer, to provide the functionality and methods to copy the data the way
                 *   we want it trough a COPY CONSTRUCTOR
                 */
            }

            // COPY CONSTRUCTOR
            {

            }

        }

        // Class Implementation
        class Human
        {
        public:
            // Inline declaration of a default constructor. If deleted, the overloaded constructor is now enforced!
            Human() : age(1), agesOfChildren(nullptr)
            {
                //age = 1;
            }

            // Overloaded constructor that takes a string as a parameter
            // Constructors can also take default values for parameters, and follow the same rules: defaults always at the end
            // Use of initialization list (: memberVariable(value))
            Human(const string &humanName, const int newAge = 25, const int numberOfChildren = 3)
                : name(humanName), age(newAge)
            {
                // Dynamically allocated memory
                agesOfChildren = new int[numberOfChildren];
            }

            // Use of explicit to avoid implicit conversion
            explicit Human(const int newAge, const int numberOfChildren = 3) : age(newAge)
            {
                // Look at the end for a more detailed explanation of the explicit keyword
                agesOfChildren = new int[numberOfChildren];
            }

            // Example of "default" constructor that uses default values
            // Human(const string& humanName = "Human", const int newAge = 25)
            // {
            //     name = humanName;
            //     age = newAge;
            // }

            // Destructor
            ~Human()
            {
                // Release dynamically allocated memory
                delete[] agesOfChildren;
                cout << "Cleared memory!" << endl;
            }

            // Custom methods
            void SetName(const string &newName)
            {
                name = newName;
            }

            void SetAge(const int newAge)
            {
                age = newAge;
            }

            void IntroduceSelf() const
            {
                cout << "I am: " << name << " and am " << age << " years old." << endl;
            }

        private:
            string name;
            int age;
            int *agesOfChildren;
        };

        // This human uses the default constructor - If we delete the default constructor, this block does not work anymore!
        Human firstHuman{};
        firstHuman.SetName("Tom");
        firstHuman.SetAge(22);
        firstHuman.IntroduceSelf();

        // This human uses the overloaded constructor to initialize member attributes at object creation
        Human secondHuman{"Ella", 25};
        secondHuman.IntroduceSelf();

        // This human initializes the name, but not the age, so the constructor reverts back to the default age value
        Human thirdHuman{"Ana"};
        thirdHuman.IntroduceSelf();
    }

    /*
    * - IMPORTANT CORE CONCEPTS OF OOP!
    *   - ENCAPSULATION: Ability to logically group data and methods from a class privately, providing access to them via
    *                    public methods
    *   - ABSTRACTION: Simplify complexity, using methods and tools to represent more intricate systems in a simple way.
    *                  Keep private members unknown to the world but have simple ways to get the data you need from a class.
    *   - Inheritance
    *   - Polymorphism
    */

    // Converting constructor
    /*
    * - A converting constructor allows you to create an object of a class by converting (or changing) the type of its
    *   parameter to the type of the class itself.
    * - Essentially, it lets you create an object from a different type.
    *
    * - A constructor is considered to be a converting constructor when:
    *   - It takes a single parameter
    *   - Not declared with the explicit keyword
    *
    * - Why do we use them?
    *   - We use this type of constructor to create objects with more flexibility
    *   - If we have a class, and its converting constructor takes a measure to convert it into another one, then we can
    *     create an object of that class directly from the measurement type (Use an int to create an object, hence the conversion)
    *
    * - What does explicit solve?
    *   - It prevents implicit conversions
    *   - When used, a constructor wont be used for automatic type conversions, improving code safety
    *
    * - Let's test it out!
    * - We will create a class that takes meters in the constructor and transforms them to feet
    * - If we do not use explicit, we can accidentally create an object of type Distance from an integer value
    */

    cout << "\n\n Converting constructor demosntration!" << endl;

    class Distance
    {
    public:
        Distance(const double metersToFeet)
        {
            cout << "Distance Constructor has been called!" << endl;
            cout << metersToFeet << " meters to feet equals = " << metersToFeet * 3.28084f << " feet!" << endl;
        }

        explicit Distance(const string &text)
        {
            cout << "This is your text: " << text << endl;
        }
    };

    Distance distance = 10.0f; // When this is invoked, the constructor gets called and then the calculation is ran
    //Distance anotherDistance = "This is new to me!"; // This won't compile! We need to call the proper constructor!
    Distance textDistance{"This is new to me! Here there was no implicit conversion and I am using a constructor"};

    return 0;
}

class ExampleClass
{
public:
    explicit ExampleClass(const string &name);

    ~ExampleClass();
};

// Constructor definition, making use of resolution operator
ExampleClass::ExampleClass(const string &name)
{
}

// Destructor definition
ExampleClass::~ExampleClass()
{
}
