//
// Created by juanf on 2024-03-20.
//

#include <iostream>
#include <chrono>
#include <algorithm>
#include <math.h>

using std::cout, std::endl, std::cin, std::string;
using namespace std::chrono;

// Classes used as an example for many of the concepts present in this document.
// Class Implementation
class BasicHuman
{
public:
    // Inline declaration of a default constructor. If deleted, the overloaded constructor is now enforced!
    BasicHuman() : age(1), agesOfChildren(nullptr)
    {
        //age = 1;
    }

    // Overloaded constructor that takes a string as a parameter.
    // Constructors can also take default values for parameters, and follow the same rules: defaults always at the end.
    // Use of initialization list (: memberVariable(value)).
    BasicHuman(const string& humanName, const int newAge = 25, const int numberOfChildren = 3)
        : name(humanName), age(newAge)
    {
        // Dynamically allocated memory
        agesOfChildren = new int[numberOfChildren];
    }

    // Use of explicit to avoid implicit conversion.
    // Look at line 652 for a deeper explanation of implicit conversion.
    BasicHuman(const int newAge) : age(newAge), agesOfChildren(nullptr)
    {
    }

    BasicHuman(const int newAge, const int numberOfChildren) : age(newAge)
    {
        agesOfChildren = new int[numberOfChildren];
    }

    // Example of "default" constructor that uses default values
    // Human(const string& humanName = "Human", const int newAge = 25)
    // {
    //     name = humanName;
    //     age = newAge;
    // }

    // Destructor
    ~BasicHuman()
    {
        // Release dynamically allocated memory
        delete[] agesOfChildren;
        cout << "Cleared memory!" << endl;
    }

    // Custom methods
    void SetName(const string& newName)
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

    void SpewWords()
    {
        Talk("Bla, Bla"); // Same as Talk(this, "Bla, Bla")
    }

private:
    string name;
    int age;
    int* agesOfChildren;
    friend void DisplayAge(const BasicHuman& human);

    void Talk(const string& statement)
    {
        cout << statement << endl;
    }
};

class MyBuffer
{
public:
    explicit MyBuffer(const unsigned int length)
    {
        bufLength = length;
        cout << "Constructor allocates: " << length << " integers" << endl;
        myNums = new int[length]; // Dynamic memory!
    }

    ~MyBuffer()
    {
        cout << "Destructor called. Clearing memory buffers..." << endl;
        delete[] myNums; // Deallocate memory, return it to the free memory pool
    }

    MyBuffer(const MyBuffer& rhs) // Copy constructor
    {
        cout << "Copy constructor creating deep copy" << endl;
        bufLength = rhs.bufLength; // Copy member variables
        myNums = new int[bufLength]; // Allocate new dynamic memory, with a different address from the original object.
        std::copy(rhs.myNums, rhs.myNums + bufLength, myNums); // Copy values of the original buffer to the new one
    }

    MyBuffer(MyBuffer&& rhs) noexcept // Move constructor
    {
        cout << "Move constructor was invoked!" << endl;

        if (rhs.myNums != nullptr)
        {
            myNums = rhs.myNums;
            bufLength = rhs.bufLength;
            rhs.myNums = nullptr;
            rhs.bufLength = 0;
        }
    }

    void SetValue(const unsigned int index, const unsigned int value)
    {
        if (index < bufLength) // Check for bounds
        {
            *(myNums + index) = value;
        }
    }

    void DisplayBuffer()
    {
        for (unsigned counter = 0; counter < bufLength; ++counter)
        {
            cout << *(myNums + counter) << "";
        }

        cout << endl;
    }

    void PrintAddress()
    {
        cout << "Buffer stored at address: " << &myNums << endl;
    }

    unsigned int GetLength() const { return bufLength; }

private:
    int* myNums;
    unsigned int bufLength;
};

void UseHuman(BasicHuman human)
{
    human.IntroduceSelf();
}

void UseMyBuffer(MyBuffer copyBuffer)
{
    cout << "Buffer copy will be destroyed once out of the function." << endl;
    copyBuffer.PrintAddress();
}

void UseMyBufferCopy(MyBuffer copyBuffer)
{
    cout << "Displaying copy of the buffer:" << endl;
    copyBuffer.DisplayBuffer();
}

MyBuffer CopyBuffer(MyBuffer& original)
{
    MyBuffer returnCopy(original); // Copy is created
    return returnCopy; // Return by value invokes copy constructor, again
}

void DisplayAge(const BasicHuman& human)
{
    cout << human.age << endl;
}

void SimpleClassImplementation();

namespace
{
    union SimpleUnion
    {
        int num;
        char alphabet;
    };

    struct ComplexStruct
    {
        enum class DataType { Int, Char }Type;

        union Value
        {
            int num;
            char alphabet;

            Value(){}
            ~Value(){}
        }value;
    };

    void DisplayComplexType(const ComplexStruct& object)
    {
        switch (object.Type)
        {
            case ComplexStruct::DataType::Int:
                cout << "Union contains number " << object.value.num << endl;
                break;
            case ComplexStruct::DataType::Char:
                cout << "Union contains character " << object.value.alphabet << endl;
                break;
        }
    }
}

int main_classes()
{
    // Basics of Object-Oriented Programming
    {
        /*
        * - So far the content from the previous modules covers procedural programming
        * - However, on modern day C++, Object oriented programming is the go to for the language
        *
        * - The base concepts of object oriented programming are classes and objects
        *
        * - CLASSES:
        *  - Classes are constructs in which we can group specific attributes (Data) and functions (methods)
        *  - Classes are defined in C++ with the keyword class, followed by the name of the class and a statement block
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
        *  - PUBLIC class members can be accessed, set, and used by anyone in possession of an object of a class
        *  - PRIVATE class members can only be accessed by the class and its "FRIEND CLASSES". However, objects can only access
        *    their private data and won't be allowed to modify other object members, even if they are the same type
        *  - Protected class members will be inherited to child classes and accessible from these new child classes (more on this later)
        *
        * - WHY WOULD WE USE THIS? FOR DATA ABSTRACTION!
        *  - With C++, we are in control to decide which information remains unreachable to the outside world, while also enabling us
        *    to control and provide custom access methods to private members. This way, we have far more control on how data being
        *    given and requested from the class is processed, preventing other classes and functions from accessing data they should
        *    not be able to modify
        *  - This way we abstract member information and keep it known only to the class and its friends, solely providing what
        *     is needed from the class through methods that expose only what we want to expose
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
            void Talk(const string& textToTalk);

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
        Human* firstWoman = new Human{};

        // Non-pointer member variable access
        firstMan.name = "Robert";
        firstMan.age = 34;
        firstMan.dateOfBirth = std::chrono::year_month_day(1990y, std::chrono::January, 20d);

        // Pointer member variable access
        firstWoman->name = "Ana";
        firstWoman->age = 32;
        firstWoman->dateOfBirth = std::chrono::year_month_day(1992y, std::chrono::March, 15d);

        // Non-pointer member method access
        firstMan.IntroduceSelf();

        // Pointer member method access (Indirection operator)
        (*firstWoman).IntroduceSelf();

        // Pointer to a Human object and use of pointer operator
        Human* doppleganger = &firstMan;
        doppleganger->IntroduceSelf();

        delete firstWoman; // Proper memory clean-up
    }

    // IMPORTANT CORE CONCEPTS OF OOP!
    {
        /*
        *   - ENCAPSULATION: Ability to logically group data and methods from a class privately, providing access to them via
        *                    public methods
        *   - ABSTRACTION: Simplify complexity, using methods and tools to represent more intricate systems in a simple way.
        *                  Keep private members unknown to the world but have simple ways to get the data you need from a class.
        *   - Inheritance: Allows a class to inherit properties and behaviours (members and methods) from a base class.
        *                  This promotes code reusability and a hierarchical relationship between related classes.
        *                  It is also the stepping stone towards polymorphism.
        *   - Polymorphism:
        */
    }

    // Methods and functionality of classes
    {
        // - Classes in C++ have methods and functionality that only exist for this type of construct

        // CONSTRUCTORS
        {
            /*
             *- Special method that gets invoked during the instantiation of a class to construct an object
             *  - Constructors, being methods, can be overloaded.
             *  - Constructors are declared by taking the name of the class and constructing a method with it. It has no return value!
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
             *  - Constructors that have default values for all arguments are interpreted as default constructors because an
             *    object can still be instantiated with no arguments to initialize member variables
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

            // C++ Handling of copies
            {
                // SHALLOW COPIES
                {
                    /*
                     * - Shallow copies are the default behaviour of many programming languages
                     * - Unless dealing with simple data, shallow copies can be threats to the stability of an application!
                     * - Shallow copies copy all the member field values (variables & methods) of an object
                     * - Any references (memory address) to other objects, pointers, or blocks of memory will be copied as is,
                     *   meaning that the copied object will be pointing to the same memory location as the original object
                     * - With this in mind, any changes to the member variables that happen either in the original object or
                     *   the copied object, will be reflected on all instances!
                     * - What this means, is that if we were to change the value of an integer pointer in a shallow object, the
                     *   value/data of that variable will also change in the original object. This is because they share the same memory
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
                     *   memory that the original object is pointing to. Once the original object clears its memory, the app
                     *   will crash because of the duplicate delete calls to an already cleared block.
                     * - This goes on to show why shallow copies are so dangerous and why the default copy method in C++ is not
                     *   safe when dealing with complex/custom types
                     */
                }

                /*
                 * - On shallow copies, the copy method used is known as a binary copy.
                 * - This binary copy makes plain copies of the existing data in members, disregarding any other information
                 * - This is why pointer values, which are just memory addresses, are the same. The compiler does not care
                 *   nor is aware of the block of memory, all it knows is the pointer has a valid address and that address is
                 *   the value it will copy on the new copy-object
                 * - For this reason, we have to ensure that whenever we are going to make copies of any objects or variables
                 *   containing pointers or dynamically allocated memory, to perform a DEEP COPY, eliminating this way, any of
                 *   the program breaking errors introduced by shallow copies.
                 */

                // DEEP COPIES
                {
                    /*
                     * - Deep copies are a more complete and safe solution to avoid the problems caused by shallow copies.
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
                     *   we want it through a COPY CONSTRUCTOR
                     */
                }
            }

            // COPY CONSTRUCTOR Implementation
            {
                /*
                 * - The copy constructor is an overloaded constructor that we supply.
                 * - It is invoked by the compiler every time an object of the same class is copied.
                 * - Correctly programmed copy constructors solve many of the issues caused by shallow copies.
                 * - This is the syntax used to declare a copy constructor:
                 *      MyClass(const MyClass& copySource);
                 * - As you can see, a copy constructor is characterized by a parameter that accepts an object of the
                 *   same class type by reference.
                 * - The parameter is an alias of the source object and is the handle you have in writing your custom
                 *   copy code.
                 * - Make use of the copy constructors to ensure a deep copy of all pointers / dynamic memory instances
                 *   of the original object unto the copy.
                 * - See the class example at the top of this document for an example implementation
                 */

                cout << "\n\nCopy constructor implementation!" << endl;
                cout << "How many integers would you like to store?";
                unsigned int numbersToStore = 0;
                cin >> numbersToStore;

                MyBuffer firstBuffer{numbersToStore};

                for (unsigned int counter = 0; counter < numbersToStore; ++counter)
                {
                    cout << "Enter value: ";
                    int valueEntered = 0;
                    cin >> valueEntered;
                    firstBuffer.SetValue(counter, valueEntered);
                }

                cout << "Numbers in the first buffer:";
                firstBuffer.DisplayBuffer();
                UseMyBufferCopy(firstBuffer);

                /*
                 * - Something important to keep in mind is that the Copy constructor will only be invoked whenever an
                 *   explicit copy is being made. [void Foo(MyObject original) → direct copy of an object]
                 * - In cases where the assignment operator is used [auto copyObject = MyObject], the copy constructor
                 *   will not be invoked as no overloaded assignment operator has been provided. Implement a custom
                 *   assignment operator to ensure that a deep copy is performed.
                 * - Ensure const correctness when working with copy constructors. This will make sure the original
                 *   object cannot be modified inside the copy function.
                 * - In addition to this, the parameter in the copy constructor is passed by reference as a necessity.
                 *   If you remove the reference, the copy constructor will get caught inside an eternal copy loop
                 *   until the system ran out of memory.
                 *
                 * - If you want to prevent a class from being copied, you can declare the copy constructor and the
                 *   copy assignment operator (See Operators.cpp) as private. This will cause the compiler to throw
                 *   errors on any copy attempts made to any instance of that class either through a value method
                 *   pass or assignment.
                 */

                /*
                 * IMPORTANT DOS AND DON'TS:
                 * - Always program a copy constructor and assignment operator whenever your class contains raw
                 *   pointers.
                 * - Always add the reference operator (&) to the argument of the copy constructor.
                 * - Use the keyword explicit while declaring constructors that should not permit implicit conversions
                 * - Don't use raw pointers as member variables unless absolutely unavoidable, use smart pointers!
                 */
            }
        }

        // Move Constructors
        {
            /*
             * - In some cases, objects will be subjected to automatic copy steps because of the way C++ works.
             * - These additional copy steps can hurt the performance of the system, especially when the objects contain
             *   large amounts of data.
             * - See the example below.
             * - The problem with the example lies within the second temporary copy being instantiated inside the
             *   method to copy and just being usable in that context. Allocating memory for no good reason.
             */

            cout << "\n\n\nAutomatic copy constructor test case!" << endl;
            MyBuffer firstBuffer(5);
            MyBuffer copyBuffer(CopyBuffer(firstBuffer));
            // Copy constructor triggered twice.
            // Once in the argument and the second one when returning the buffer by value
            // With the implementation of a Move constructor, the issue above is solved and no more unnecessary copies
            // are created

            /*
             * - To avoid this bottleneck and unnecessary copies, C++ introduced Move Constructors.
             * - Move constructors are special constructors that enable the efficient transfer of resources from one
             *   object to another, especially in cases where copying would be an expensive operation.
             * - Move semantics are an important concept that should be studied and understood in order to implement all
             *   best move practices.
             * - Also keep in mind the Rule of Five! The rule of five suggests that if your class requires a custom
             *   destructor, copy constructor, or copy assignment operator, you should also define the move constructor
             *   and move assignment operator.
             */
        }

        // Different uses of constructors and the Destructor
        {
            // A class that does not permit copying.
            {
                /*
                * - We can ensure that a class cannot be copied via a copy constructor by declaring a private copy constructor.
                * - You would do the same with the assignment operator.
                * - There is no need for implementation. As long as they are marked as private, there will be no copies.
                */

                class President
                {
                private:
                    President(const President&);
                    President& operator=(const President&);

                public:
                    float salary;
                };
            }

            // A singleton class
            {
                /*
                 * - Singletons prevent the instantiation of the same object more than once.
                 * - This effectively allows you to have a single entity per program.
                 * - To create a singleton pattern in C++, we make use of the word static, private constructors, and private
                 *   operators.
                 *
                 * - Using the static keyword on a class's data member, ensures that the member is shared across all instances.
                 * - When used in a method, that method is available to all instances of the class.
                 * - When used on a local variable declared within the scope of a function, it ensures that the variable
                 *   retains its value between function calls.
                 */

                cout << "\n\n\nSingleton implementation!" << endl;

                class Dictator
                {
                private:
                    Dictator()
                    {
                    }; // Private constructor
                    Dictator(const Dictator&); // Private copy constructor
                    const Dictator& operator=(const Dictator&); // Private copy assignment operator

                    string name;

                public:
                    static Dictator& GetInstance()
                    {
                        // Static objects are constructed only once!
                        static Dictator instance;
                        return instance;
                    }

                    string GetName() const { return name; }

                    void SetName(const string& inputName) { name = inputName; }
                };

                Dictator& dictator = Dictator::GetInstance();
                dictator.SetName("Admiral General Aladeen");

                // If the following lines are uncommented, compilation will fail
                //Dictator second; // Can't access constructor.
                //Dictator* third = new Dictator(); // Can't access constructor
                //Dictator fourth = dictator; // Can't access copy constructor
                //dictator = Dictator::GetInstance(); // Can't access operator= as it has been marked private

                cout << "The name of the dictator is: ";
                cout << Dictator::GetInstance().GetName() << endl; // Notice this line!
                // In the line above, we can see the use of the static keyword.
                // We are not directly calling the object we instantiated, but rather, we are calling the static instance.
                // By being static, no matter where we are in this scope, we can directly call that one dictator and access
                // its information!
            }

            // A class that prohibits instantiation on the stack
            {
                /*
                 * - The stack is a LIFO memory bank (Last-in, First-out) that is used to store local variables of a function.
                 * - Space on the stack is limited.
                 * - When working with classes/structures that require a big amount of data, it's better to ensure they
                 *   allocate their memory on the free store and not on the stack.
                 * - The key to making this happen is to declare the destructor as private.
                 */

                class MonsterDataBase
                {
                private:
                    ~MonsterDataBase(); // Private destructor
                };

                // - Creating a class like that ensures that you cannot declare an object as a variable.
                // - Instead, it will force you to declare it as a pointer that allocates memory using the new operator.
                // - This happens because at compilation time, the object will be added to the stack, and by doing so, the
                //   destructor of the class needs to be invoked the end of the main function.
                //   However, by making it private, the compiler cannot just invoke it, and so, compilation fails.

                //MonsterDataBase monsterDataBase; // This will cause a compiler error.
                //MonsterDataBase* monsterDataBase = new MonsterDataBase(); // This causes no compilation errors!

                /*
                 * - BE CAREFUL THOUGH!
                 * - We can now use the free store to create this object, but the problem now is that we are going to suffer
                 *   a serious memory leak.
                 * - This is because the constructor is private and won't be called at the end of the scope.
                 * - The same applies to the delete/delete[] operator. No call is possible as the destructor is private.
                 * - To solve this issue, we MUST ensure there is a method that can be called by all instances of the class
                 *   that will clear the memory and destroy the object that is calling it.
                 * - For this method, implement it using the public static syntax.
                 */

                class SafeMonsterDataBase
                {
                private:
                    ~SafeMonsterDataBase()
                    {
                    } // Private destructor

                public:
                    static void DestroyMonsterDataBase(SafeMonsterDataBase* instance)
                    {
                        delete instance;
                    }

                    void DoSomething()
                    {
                    }
                };

                SafeMonsterDataBase* instance = new SafeMonsterDataBase(); // Allocated on the free store
                instance->DoSomething();

                //delete instance; // This will cause a compilation error. Added for demonstration purposes.

                // Proper way to release memory
                SafeMonsterDataBase::DestroyMonsterDataBase(instance);

                /*
                 * - This works because DestroyMons...() is a member method of the class, and as such, it can access the
                 *   other internal members/methods of the class.
                 * - By calling the method, internally, we call the delete operator, which will then trigger the
                 *   implementation of the destructor, if any.
                 *   This will safely clear all the allocated memory from the object and then release it.
                 */
            }

            // Using constructors to convert types
            {
                /*
                 * - Overloading constructors is often used to convert one type to another.
                 * - Let's take, for example, the BasicHuman class at the top of the document.
                 * - The basic constructors given allow for implicit conversions. See line 672.
                 */

                cout << "\n\n\nImplicit conversion implementation!" << endl;
                BasicHuman kid(10); // Convert an integer to a human with age 10
                UseHuman(kid);
                UseHuman(20); // Huh!? How are we turning an integer into a human? Because of implicit conversion!

                /*
                 * - Implicit conversion happens because the compiler knows that the BaseHuman class has an overloaded
                 *   constructor that accepts an integer as a parameter. Because of that, it implicitly converts the integer
                 *   to a BaseHuman object, using the constructor, and then calls the UseHuman method on it.
                 * - This happens because of the capabilities of the Converting constructor.
                 */

                // Converting constructor
                {
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
                    * - What does explicit declaration in a constructor do?
                    *   - It prevents implicit conversions
                    *   - When used, a constructor won't be used for automatic type conversions, improving code safety
                    *
                    * - Let's test it out!
                    * - We will create a class that takes meters in the constructor and transforms them to feet
                    * - If we do not use explicit, we can accidentally create an object of type Distance from an integer value
                    */

                    cout << "\n\n Converting constructor demonstration!" << endl;

                    class Distance
                    {
                    public:
                        Distance(const double metersToFeet)
                        {
                            cout << "Distance Constructor has been called!" << endl;
                            cout << metersToFeet << " meters to feet equals = " << metersToFeet * 3.28084f << " feet!"
                                <<
                                endl;
                        }

                        explicit Distance(const string& text)
                        {
                            cout << "This is your text: " << text << endl;
                        }
                    };

                    Distance distance = 10.0f;
                    // When this is invoked, the constructor gets called and then the calculation is run
                    //Distance anotherDistance = "This is new to me!"; // This won't compile! We need to call the proper constructor!
                    Distance textDistance{
                        "This is new to me! Here there was no implicit conversion and I am using a constructor"
                    };
                }
            }
        }

        // The "this" pointer
        {
            /*
             * - "this" is a reserved keyword that is applicable within the scope of a class and contains the address of the
             *   object.
             * - The value of this == &object
             * - When calling a method that calls another internal method, the compiler adds an automatic reference to the
             *   object itself. You can use the "this" pointer inside methods to clearly state a message on the assignation
             *   of member variables. However, the "this" pointer in reality does not have many use case scenarios by itself.
             * - Do take note that the "this" pointer is not sent to a class methods that are declared as "static" because
             *   static functions are not connected to instances of the class. Instead, they are shared by all instances.
             * - To use an instance variable in a static function, you explicitly declare a parameter and send the "this"
             *   pointer as an argument.
             */

            class ExampleClass
            {
            public:
                explicit ExampleClass(const int input)
                {
                    this->value = input; // Example of the "this" pointer
                }

            private:
                int value;
            };
        }

        // sizeof() operator with classes
        {
            /*
             * - The operator will report back the number of bytes needed in memory per class declaration.
             * - Member methods and their local variables do not play a role in defining sizeof() for a class
             */

            MyBuffer buff1(5);
            MyBuffer buff2(20);
            BasicHuman dude("Tom", 20);
            BasicHuman gal("Jen", 21);

            cout << "\n\n\nsizeof() implementation" << endl;
            cout << "sizeof(MyBuffer) = " << sizeof(MyBuffer) << endl;
            cout << "sizeof(buff1) = " << sizeof(buff1) << endl;
            cout << "sizeof(buff2) = " << sizeof(buff2) << endl;
            cout << "sizeof(BasicHuman) = " << sizeof(BasicHuman) << endl;
            cout << "sizeof(dude) = " << sizeof(dude) << endl;
            cout << "sizeof(gal) = " << sizeof(gal) << endl;
        }
    }

    // Differences between structs and classes
    {
        /*
         * - In modern C++. structs are mostly treated as classes.
         * - The main differences are default access specifiers. Unless specified, members in a struct are public by
         *   default (private for a class). Structs also feature public inheritance from a base struct, unless otherwise
         *   specified. Classes on the other hand feature private inheritance.
         * - So when do we use each?
         *      - Use structs for simple data structures that group together public data members and minimal functionality.
         *      - Use classes when you need encapsulation and more advanced functionality through methods.
         */

        struct Human
        {
        private:
            int age;
            string gender;
            string name;

        public:
            Human(const string& inputName, const int inputAge, const string& inputGender)
                : age(inputAge), gender(inputGender), name(inputName) {}

            int GetAge() const { return age; }
        };

        Human man("Adam", 20, "Man");
        // As you can see, a struct follows the same pattern as a class.
    }

    // What are FRIENDS and how can we declare one? (Does not apply to IRL, go outside and meet people!)
    {
        /*
         * - Classes do not allow external access to its private methods and member variables.
         * - However, this rule is waived for classes and methods that are disclosed as friend classes or methods.
         * - Use the keyword "friend" for such cases.
         */

        class Human
        {
        private:
            int age;
            string name;
            friend class Utility; // Example implementation of external class as a friend.

        public:
            Human(const string& inputName, const int inputAge)
                : age(inputAge), name(inputName) {}

            int GetAge() const { return age; }
        };

        class Utility
        {
        public:
            static void DisplayAge(const Human& person)
            {
                cout << "I am the Utility class! Printing out the age: ";
                cout << person.age << endl;
            }
        };

        cout << "\n\n\nAccessing private members through friend function" << endl;
        BasicHuman dude("Adam", 20); // Class implements friend function declared at the top.
        dude.IntroduceSelf();
        DisplayAge(dude); // This is an external global function declared as a friend.

        cout << "\nAccessing private members through friend class" << endl;
        Human gal("Eve", 20);
        Utility::DisplayAge(gal);
    }

    // What are Unions?
    {
        /*
         * - Unions are special data storage mechanisms in which only one of the non-static data members is active at a
         *   time.
         * - Unions can then accommodate multiple data members, just like a class, with the exception that only one of
         *   them can be used.
         *
         * - Unions are declared with the keyword "union", followed by their name and data members, within braces.
         */

        union UnionName
        {
            //Type variable;
            //Type variable;
            int member1;
            float member2;
        };

        UnionName unionObject;
        unionObject.member2 = 1.0f; // Here we have chosen member2 as the active member.

        /*
         * - Just like structs, a union's members are public by default. However, unions cannot be used in inheritance
         *   hierarchies.
         * - Additionally, the size of a union is always fixed to the size of its biggest member, regardless of it being
         *   active or not.
         *
         * - Use cases:
         *  - Often used with structs to model a complex data type.
         *  - Can also be used for type conversions thanks to its ability to interpret fixed memory space as another type.
         *  - Memory reinterpretation.
         *  - These last two cases are controversial as better optimized methods are available.
         */

        cout << "\n\n\nUniom implementation!" << endl;

        SimpleUnion u1, u2;
        u1.num = 2100;
        u2.alphabet = 'C';

        cout << "sizeof(u1) containing an integer: " << sizeof(u1) << endl;
        cout << "sizeof(u2) containing a character: " << sizeof(u2) << endl;

        ComplexStruct myData1, myData2;
        myData1.Type = ComplexStruct::DataType::Int;
        myData1.value.num = 2017;

        myData2.Type = ComplexStruct::DataType::Char;
        myData2.value.alphabet = 'X';

        DisplayComplexType(myData1);
        DisplayComplexType(myData2);

        /*
         * - Unions give you the flexibility to store one among many permissible types.
         * - The downside of it though, is that it won't stop you from accessing the contents of one type as another.
         *   You store and int, yet you are able to access a string's methods.
         * - Unions thus do not enforce type safety. In order to solve this, C++ 17 introduced std::variant. A type safe
         *   alternative to union.
         */
    }

    // Aggregate Initialization on Classes and Structs
    {
        /*
         * - The following syntax is known as Aggregate Initialization
         *      - Type objectName = {argument1, ..., argumentN};
         * - It can also follow the next pattern:
         *      - Type objectName{argument1, ..., argumentN};
         * - Aggregate initialization can be applied to an aggregate, with multiple data types falling under this category:
         *  - Aggregates are simple data structures that do not involve complex behaviors like constructors,
         *    destructors, or private/protected member variables.
         *  - However, this definition of an aggregate changes based on the C++ standard you refer to, and in newer ones
         *    like C++ 14 and 17, the definition of an aggregate has become more flexible.
         * - As of today, there are 4 major requirements for a data structure to be considered an aggregate:
         *  - No user-declared constructors.
         *  - No Private or Protected Non-Static Data Members. It must all be public.
         *  - No virtual functions.
         *  - No use of private, protected, and virtual inheritance. Only public inheritance is allowed.
         * - If any data structure follows these requirements, it counts as an aggregate and can be initialized as one.
         */

        cout << "\n\n\nAggregate initialization implementation" << endl;
        struct Aggregate1
        {
            int num;
            double pi;
        };

        Aggregate1 agg1{2024, 3.1416}; // Can be initialized as an aggregate.
        // Remember to initialize in the same order as you organize your data structure (num, float, etc.)

        struct Aggregate2
        {
            int num;
            char hello[6];
            int mYears[5];
        };

        Aggregate2 agg2 = {42, {'h','e','l','l','o'}, {1998, 2003, 2011, 2014, 2017}};
        // In this example we are using another syntax for aggregate initialization
        // We are also showcasing another example of aggregates such as arrays

        class Aggregate3
        {
        public:
            int num;
            double pi;
        };

        struct Aggregate4
        {
            char hello[6];
            int cYears[3];
            string world;
        };

        int myNums[] = {9,5,-1};
        Aggregate3 aggClass{2023, 3.1416}; // Class follows all the requirements, so it is an aggregate!
        cout << "PI is approx: " << aggClass.pi << endl;

        Aggregate4 agg3{{'h','e','l','l','o'}, {2017, 2020, 2023}, "world"};
        Aggregate4 agg3_b{'h','e','l','l','o', '\0', 2017,2020,2023, "world"};

        cout << agg3.hello << " " << agg3.world << endl;
        cout << "C++ standard update schedule in: " << agg3_b.cYears[2] << endl;

        // EXTRA
        {
            /*
             * - Aggregate Initialization initializes only the first non-static member of a union
             * - If we were to use it, the syntax would like the example below.
             * - Unfortunately, this would cause unexpected behaviour because the member being initialized in u2 is num
             *   and not alphabet, although you meant to initialize alphabet.
             * - This happens because the first member of the union is num.
             * - The code will still compile and when accessing the members of u2 we would get 'C' for alphabet and 63
             *   for the num representation, which is its ASCII value.
             */

            SimpleUnion u1{2100}, u2{'C'};

            cout << "U1: " << u1.num << endl;
            cout << "U2 alphabet is: " << u2.alphabet << endl;
            cout << "U2 Num value is: " << u2.num << endl;
        }
    }

    // Constexpr with Classes and objects
    {
        /*
         * - When adding constexpr to a method that operates on const/constexpr arguments, you instruct the compiler to
         *   evaluate those functions at compile time and insert their result instead of inserting instructions that
         *   call the function when the code is run.
         * - This same principle can be applied to classes and objects that are evaluated as constants.
         * - Do note that if the function or class is used with entities that are not const, the compiler will ignore
         *   the constexpr and treat it as a regular executing method.
         * - Remember these main differences between const and constexpr:
         *  - const does not require the value to be known at compile time. It can still be initialized at run time.
         *  - constexpr does require the value to be known, and if it is not, the program will not compile.
         *  - constexpr can be used with functions, and if all parameters are const or literals, the function result
         *    will be calculated at compile time. If the arguments are not const/literals, then the method will be
         *    called at runtime, as a normal function.
         */

        class Human
        {
        private:
            int age;

        public:
            constexpr Human(int humansAge) : age(humansAge) {}
            constexpr int GetAge() const { return age; }
        };

        constexpr Human someDude(26); // Instantiated at compiletime
        const int hisAge = someDude.GetAge();
        // In this case, because the variable and method are declared as const, the statement will be computed at compile
        // time. If the variable was not but the expression is, depending on compiler optimization settings, it can
        // either be comp time evaluated or ru time evaluated.

        Human anotherDude(40); // Not a constant expression. Instantiated at runtime.
    }

    SimpleClassImplementation();
    return 0;
}

void SimpleClassImplementation()
{
    cout << "\n\n\nSimple class implementation!" << endl;

    // This human uses the default constructor - If we delete the default constructor, this block does not work any more!
    BasicHuman firstHuman{};
    firstHuman.SetName("Tom");
    firstHuman.SetAge(22);
    firstHuman.IntroduceSelf();

    // This human uses the overloaded constructor to initialise member attributes at object creation
    BasicHuman secondHuman{"Ella", 25};
    secondHuman.IntroduceSelf();

    // This human initialises the name, but not the age, so the constructor reverts to the default age value
    BasicHuman thirdHuman{"Ana"};
    thirdHuman.IntroduceSelf();
}

class ExampleClass
{
public:
    explicit ExampleClass(const string& name);

    ~ExampleClass();
};

// Constructor definition, making use of resolution operator
ExampleClass::ExampleClass(const string& name)
{
}

// Destructor definition
ExampleClass::~ExampleClass()
{
}
