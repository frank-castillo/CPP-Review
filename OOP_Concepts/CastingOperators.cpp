//
// Created by juanf on 2024-09-02.
//

// Module 13

#include <iostream>
#include <string>
#include <vector>

using std::cout, std::endl, std::string;

namespace DynamicCastFish
{
    class DynamicCastFish
    {
    public:
        virtual ~DynamicCastFish() = default;

        virtual void Swim()
        {
            cout << "Fish Swims in water" << endl;
        }
    };

    class DynamicCastTuna : public DynamicCastFish
    {
    public:
        void Swim() override
        {
            cout << "Tuna Swims in the sea" << endl;
        }

        void BecomeDinner()
        {
            cout << "Tuna Becomes dinner" << endl;
        }
    };

    class DynamicCastCarp : public DynamicCastFish
    {
    public:
        void Swim() override
        {
            cout << "Carp swims in the lake" << endl;
        }

        void Talk()
        {
            cout << "Carp talks!?" << endl;
        }
    };

    void DetectFishType(DynamicCastFish* fish)
    {
        DynamicCastTuna* tuna = dynamic_cast<DynamicCastTuna*>(fish);
        if (tuna)
        {
            cout << "Tuna Detected! Feeding time" << endl;
            tuna->BecomeDinner();
        }

        DynamicCastCarp* carp = dynamic_cast<DynamicCastCarp*>(fish);
        if (carp)
        {
            cout << "A weird carp appeared..." << endl;
            carp->Talk();
        }

        cout << "Verifying type using virtual ...Fish::Swim()" << endl;
        fish->Swim();
    }
}

int main()
{
    // What is casting?
    {
        /*
         * - Casting is a mechanism that allows a programmer to temporarily or permanently change how the compiler
         *   interprets an object. This does not mean that the object itself is changed, only its interpretation!
         *
         * - In C++ this is achievable thanks to the CASTING OPERATORS!
         *
         * - In order to achieve interoperability between modern code and legacy code, external modules, libraries, etc.
         *   our compiler needs to be instructed to interpret data in ways that make our application compile and function
         *   correctly.
         *
         * - As years have gone by, and as the C and C++ standards have been updated, added functionality support has been
         *   added to support both older and newer code bases. In modern C++, we have the ability to use both C-style and
         *   C++ casting operators. Although C-style casting is older and not the preferred method, it is still important
         *   to understand both casting styles.
         */
    }


    // C-style vs C++-style
    {

        /*
         * - Type safety is one of the top-features that C++ programming provides. However, it still needs to support legacy
         *   code and be backward compliant with the older C standard.
         * - With this in mind, compilers will permit casting at the expense of being able to introduce serious bugs.
         *
         * - C++ won't allow this:
         *   - char* staticString = "Hello"; int* intArray = staticString; Error! Can't convert char* to int*
         *
         * - However, because of casting support, nothing stops me from doing the following:
         *   - int* intArray = (int*)staticString; C-style cast
         *
         * - This particular C-style cast FORCES the compiler to interpret the destination as a type that the programmer
         *   wanted to assign to.
         * - Casting suppresses compile errors even though the types are totally incompatible! You are basically muzzling
         *   the compiler and forcing it to obey.
         * - C-style casting does not perform any conversions, compromising type safety, and undermining the quality of the
         *   code and ourselves!
         *
         * - So how does C++ do it better?
         */
    }

    // C++ Casting operators
    {
        /*
         * - Despite the obvious disadvantages of casting and the problems it can introduce, it is a concept that we cannot
         *   discard.
         * - In many situations, casts are the only way to solve important compatibility issues and ensure that our code
         *   performs the task at hand.
         *
         * - With C++ being an OOP language, inheritance hierarchies and the ability to cast objects is another concern for
         *   which, obviously, C++ provides an operator for.
         *
         * - C++ provides 4 casting operators:
         *  - static_cast.
         *  - dynamic_cast.
         *  - reinterpret_cast.
         *  - const_cast.
         *
         * - The usage syntax of casting operators is simple and consistent among them:
         *  - destination_type result = cast_operator<destination_type>(object_to_cast);
         *  - int result = static_cast<int>(randomVariableType);
         */
    }

    // Using static_cast<>
    {
        /*
         * - This operator can be used to:
         *  - Convert pointers between related types.
         *  - Perform explicit type conversions for standard data types that would otherwise happen automatically or
         *    implicitly.
         *
         * - For pointers, it implements a basic compile-time check to ensure that a pointer is being cast to a related
         *   type.
         *   - This is a big improvement against the classic C-style cast, which allows a pointer to one object to be
         *     cast to a completely unrelated type without any complaint.
         * - This basically means that a pointer can be upcasted (Derived to Base) or downcasted (Base to derived).
         */

        class Base{};
        class Derived: public Base{};
        class Unrelated{};

        Base objBase;
        Base* b = &objBase;
        Derived* d = static_cast<Derived*>(b); // Base type to Derived type == downcast
        //Unrelated* u = static_cast<Unrelated*>(b); // Cannot cast from Base * to Unrelated * via static_cast

        /*
         * - Upcasting can be done without the need of an explicit cast. Some compilers, if implementing Clang-tidy,
         *   will actually throw this suggestion: "Clang-Tidy: Do not use static_cast to downcast from a base to a
         *   derived class"
         * - This is not a compiler error and there is nothing wrong with doing it. Writing it as such will make your
         *   intention to cast clearer and help with readability and type safety.
         *
         * - On the other hand! Downcasting does require the use of an explicit casting operator and won't work unless
         *   it is provided.
         */

        Derived d2;
        Base* b2 = &d2; // No need to use cast operator to upcast
        //Derived* d3 = b2; // Compiler fails, as it is not possible to perform this operation

        /*
         * - DO NOTE that static_cast only verifies that the pointer types are related. It will not perform runtime
         *   checks. So a bug like this one can still be added:
         *   - Base* b = new Base(); Derived* d = static_cast<Derived*>(b);
         * - In the example, derived points to a Base type but not to a type derived. The compiler will check if the
         *   types are related, and if they are, will allow the casting. However, it will not check if the type is the
         *   correct one. This will introduce unexpected behaviour when attempting to use the object.
         *
         * - static_cast can also help in making implicit casts explicit and bring them to the attention of a reader or
         *   programmer.
         * - We also make use of static_cast when using explicit conversion operators and constructors to ensure we are
         *   properly invoking them. Read Modules 9 and 12 for more information.
         */

        double pi = 3.141592653589;
        int num = static_cast<int>(pi); // Implicit cast is now explicit
    }

    // Using dynamic_cast<> and runtime type identification (RTI)
    {
        /*
         * - Just as the name suggests, this type of casting happens at runtime.
         * - The result of a dynamic_cast can be checked to see whether the attempt to cast an object succeeded.
         *
         * - The syntax is as follows
         *  - destination_type* Dest = dynamic_cast<destination_type*>(source)
         *  - if(Dest) { Perform an action with cast pointer}.
         */

        class Base
        {
        public:
            virtual ~Base() = default;
            virtual void foo() { cout << "foo" << endl; }
        };
        class Derived: public Base
        {
        public:
            void foo() override{ cout << "Derived foo" << endl; }
        };

        cout << "Dynamic cast implementation" << endl;

        Base objBase;
        Derived objDer;
        Base* b = new Derived();

        Derived* d = dynamic_cast<Derived*>(b);

        if (d)
        {
            //d->foo();
        }

        delete b;

        /*
         * - As shown in the example above, given a pointer to a base class object, we can use dynamic_cast to verify
         *   the type of the destination object being pointed to before proceeding to use it. This functionality comes
         *   in really handy when working with more complex types and methods that can accept Base class pointers.
         * - By using dynamic_cast, we can detect the type of object it is and perform operations that belong to the
         *   derived type.
         * - This is called: Runtime Type Identification (RTI).
         *
         * - This operator returns either a valid address or a nullptr when performing the cast hence why we perform
         *   the validity check. NEVER FORGET TO PERFORM A VALIDITY CHECK!
         *
         * - TL;DR: dynamic_cast helps to determine the type are runtime and makes it possible to use a cast pointer
         *   when it is safe to do so. The cast can return a valid address or a nullptr, so always perform a check.
         *
         *   For a more complex implementation, see the example below.
         */

        using namespace DynamicCastFish;
        DynamicCastCarp carp;
        DynamicCastTuna tuna;

        DetectFishType(&tuna);
        cout << endl;
        DetectFishType(&carp);

        cout << "\n\n" << endl;

        /*
         * - Given an instance of the base class Fish*, we can dynamically detect whether the pointer points to a carp
         *   or a tuna. Inside the function, we use dynamic_cast to test the nature of the input base class pointer of
         *   type Fish* for the other derived types. If any of those casts succeeds, then the cast was successful, and
         *   we can then safely use the pointer to call the associated methods and members of the derived class.
         * - Finally, by making use of the VTABLE, we call the override method of the derived class through the base
         *   class to further proof that our cast was correct and our object is indeed, of the derived type.
         */
    }

    // Using reinterpret_cast
    {
        /*
         * -
         */
    }
}
