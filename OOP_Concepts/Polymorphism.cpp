//
// Created by juanf on 2024-08-25.
//

#include <iostream>
using std::cout, std::endl;

namespace BasicFish
{
    class BasicFish
    {
    public:
        BasicFish()
        {
            std::cout << "BasicFish was constructed" << std::endl;
        }

        ~BasicFish()
        {
            std::cout << "BasicFish was destructed" << std::endl;
        }

        void Swim() const
        {
            cout << "BasicFish Swims!" << endl;
        }
    };

    class BasicTuna : public BasicFish
    {
    public:
        BasicTuna()
        {
            std::cout << "BasicTuna was constructed" << std::endl;
        }

        ~BasicTuna()
        {
            std::cout << "BasicTuna was destructed" << std::endl;
        }

        void Swim() const
        {
            cout << "BasicTuna Swims!" << endl;
        }
    };

    void MakeFishSwim(const BasicFish& fish)
    {
        // Calling fish swim
        fish.Swim();
    }

    void DeleteFish(const BasicFish* fish)
    {
        delete fish;
    }
}

namespace VirtualFish
{
    class VirtualFish
    {
    public:
        VirtualFish()
        {
            std::cout << "VirtualFish was constructed" << std::endl;
        }

        virtual ~VirtualFish()
        {
            std::cout << "VirtualFish was destructed via virtual destructor" << std::endl;
        }

        virtual void Swim() const
        {
            cout << "VirtualFish Swims!" << endl;
        }
    };

    class VirtualTuna : public VirtualFish
    {
    public:
        VirtualTuna()
        {
            std::cout << "VirtualTuna was constructed" << std::endl;
        }

        ~VirtualTuna()
        {
            std::cout << "VirtualTuna was destructed via virtual destructor" << std::endl;
        }

        void Swim() const
        {
            cout << "VirtualTuna Swims!" << endl;
        }
    };

    class VirtualCarp : public VirtualFish
    {
    public:
        VirtualCarp()
        {
            std::cout << "VirtualCarp was constructed" << std::endl;
        }

        ~VirtualCarp()
        {
            std::cout << "VirtualCarp was destructed via virtual destructor" << std::endl;
        }

        void Swim() const
        {
            cout << "VirtualCarp Swims!" << endl;
        }
    };

    void MakeVirtualFishSwim(const VirtualFish& fish)
    {
        // Calling fish swim
        fish.Swim();
    }

    void DeleteVirtualFish(const VirtualFish* fish)
    {
        delete fish;
    }
}

namespace AbstractFish
{
    class AbstractFish
    {
    public:
        virtual ~AbstractFish() = 0;
        virtual void Swim() const = 0;
    };

    AbstractFish::~AbstractFish() = default;

    class AbstractTuna : public AbstractFish
    {
    public:
        void Swim() const
        {
            cout << "AbstractTuna Swims!" << endl;
        }
    };

    class AbstractCarp : public AbstractFish
    {
    public:
        void Swim() const
        {
            cout << "AbstractCarp Swims!" << endl;
        }
    };

    void MakeAbstractFishSwim(const AbstractFish& fish)
    {
        fish.Swim();
    }
}

namespace OverrideFish
{
    class OverrideFish
    {
    public:
        virtual ~OverrideFish() = 0;
        virtual OverrideFish* Clone() = 0;
        virtual void Swim() const = 0;

        void Eat() const
        {
            cout << "OverrideFish Eats!" << endl;
        }
    };

    OverrideFish::~OverrideFish() = default;

    class OverrideTuna : public OverrideFish
    {
    public:
        OverrideTuna()
        {
            cout << "OverrideTuna created!" << endl;
        }

        ~OverrideTuna() override
        {
            cout << "OverrideTuna destroyed!" << endl;
        }

        OverrideFish* Clone() override
        {
            return new OverrideTuna(*this);
        }

        void Swim() const override // The only major change here is the override specifier
        {
            cout << "OverrideTuna Swims!" << endl;
        }

        void Eat() const
        {
            cout << "OverrideTuna Eats!" << endl;
        }
    };

    class OverrideBlueFinTuna final : public OverrideTuna
    {
    public:
        OverrideBlueFinTuna()
        {
            cout << "OverrideBlueFinTuna created!" << endl;
        }

        ~OverrideBlueFinTuna() override
        {
            cout << "OverrideBlueFinTuna destroyed!" << endl;
        }

        OverrideFish* Clone() override
        {
            return new OverrideBlueFinTuna(*this);
        }

        void Swim() const override // The only major change here is the override specifier
        {
            cout << "OverrideBlueFinTuna Swims!" << endl;
        }

        void Eat() const
        {
            cout << "OverrideBlueFinTuna Eats!" << endl;
        }
    };

    class OverrideCarp final : public OverrideFish
    {
    public:
        OverrideCarp()
        {
            cout << "OverrideCarp created!" << endl;
        }

        ~OverrideCarp() override
        {
            cout << "OverrideCarp destroyed!" << endl;
        }

        OverrideFish* Clone() override
        {
            return new OverrideCarp(*this);
        }

        void Swim() const override // The only major change here is the override specifier
        {
            cout << "OverrideCarp Swims!" << endl;
        }

        void Eat() const
        {
            cout << "OverrideCarp Eats!" << endl;
        }
    };
}

int main()
{
    // What is Polymorphism?
    {
        /*
         * - This is an advanced feature from Object-Oriented Languages that allows objects of different types to be
         *   treated similarly.
         * - In C++ multiple types of polymorphic behaviours are supported. Each of them will happen at different stages
         *   of the execution and compilation of the application's code, based on the code support you provide for it.
         * - The 4 types of polymorphic behaviour C++ supports are:
         *  - Compile-time polymorphism (Static polymorphism): supported via function overloading and operator
         *    overloading in your custom types.
         *  - Run-time polymorphism (Dynamic polymorphism): supported via inheritance and method overloading using
         *    virtual functions.
         *  - Subtype polymorphism: Specific case of dynamic polymorphism. It happens when a function or method operates
         *    on objects of a subclass through a reference/pointer to the base class.
         *  - Parametric polymorphism (Generics): Supported through templates.
         *
         * - An easy analogy to this complex topic can be represented with the use of toys.
         *
         * - Compile-time polymorphism: Imagine a toy that has a pressure sensitive button. This button, based on the
         *   force applied, will prompt the toy to behave in a different way even though the action (button pressing)
         *   is the same. All that changes is the input force. This in OOP we know as function overloading.
         *   Now, for that same toy, imagine it were to be a robot that can be combined with other robots to create a
         *   bigger and more feature packed super robot (e.g. The Megazord). By adding one robot to the other and
         *   combining them, we end up with a bigger robot and so on. Now, of course, we can also disassemble the big
         *   robot and go back to a more simplistic version of it. This is an example of what can be achieved with
         *   operator overloading (e.g. SuperRobot = Robot + Robot; LameRobot = SuperRobot - SuperRobot)
         *
         * - Run-time polymorphism: Using the same example of the robots, now think of a Transformer toy. Each one of
         *   them is a robot that can transform into a vehicle or a machine, copying all of its functionality while
         *   still being a powerful soldier. This is the same way how this type of polymorphism works like. We will have
         *   a base class that provides default behaviours (e.g. Transformer) and the derived classes based on their
         *   programming will be able to override the base behaviour and use a more specialized one.
         *   Think of it like this, all our transformer toys have one single button, but we have a transformer that can
         *   turn into a car, one that can turn into a plane, and one that can turn into a tank. The inner workings
         *   of the toy are the same for all of them, yet when we press the button, the car transformer's lights all go
         *   off. The plane transformer spreads it wings, and the tank transformer shoots a projectile. We haven't
         *   changed the button or the inner working, yet each different type of transformer does its own custom action
         *   based on that button overloading.
         *
         * - Subtype polymorphism: This case will be a more abstract one but the main idea of subtype polymorphism
         *   expands on the implementation of dynamic polymorphism. How so? Well, dynamic poly. makes use of inheritance
         *   hierarchies to establish relationships between all the derived classes and their overloaded methods
         *   implementation. Subtypes take this inheritance relationships to the next level by abstracting the type of
         *   the derived class by only referencing the Base class as the type and then letting the compiler figure out
         *   which overloaded function and derived class to use. This way, you can use a generic base object as a
         *   container for any of its derived classes and still trigger the proper derived methods.
         *   - The perfect example of this are Lego figures and our imagination. Think of the default lego figurine. A
         *     small yellow avatar, with a generic face, generic clothing, and no defining features. A base figure.
         *   - When that figure is placed in the hands of a child, through their imagination, that simple Lego figure
         *     can become a police officer, a doctor, a superhero, or a myriad of other things. We didn't change
         *     anything about the figure, it's the same plane and basic figure from the beginning, but thanks to the
         *     child converting it and changing its concept, the lego figure becomes able of performing a different
         *     role.
         *   - In pseudocode terms:
         *     LegoFigure* figure; A basic lego figure.
         *     figure = new LegoDoctorFigure(); The child assigns it a new role.
         *     figure->HealPatient(); The basic lego figure now has a new role and is able to perform new things.
         *     figure = new LegoBatman(); A new role was given.
         *     figure->BeatTheJoker(); A whole new set of functions is given.
         *     And so on...
         *  - As you can see, subtypes allow for more abstract or one-size-fits-all design opportunities to better
         *    scale your application and avoid code clutter. This allows us to create templates or generic pieces of
         *    code that enable us to work with any type of object or derived without the need to create a per-type
         *    implementation. Funnily enough, the last type of polymorphism is also called Generics.
         *
         * - Parametric polymorphism: This type of polymorphism as explained in the last section of Subtype poly., will
         *   enable us to create generic containers, methods, classes, etc., that can work with whichever object we feed
         *   them. Similarly to a toy box! With a toy box, you don't care if the toy is a car, a plane, or a robot. All
         *   you care about is the fact that it is a toy. Thanks to that, you can store anything that fits the toy
         *   description in that box regardless of its type. As long as the base of the object is a toy, it will be
         *   accepted in the box.
         *   - This concept in C++ is known as Templates. This topic has its own module, so feel free to check it out to
         *     learn more about it.
         */
    }

    // Why do we need it?
    {
        cout << "Why do we need Polymorphism?" << endl;
        // Take a look at the following code and then the class implementation in the BasicFish namespace

        BasicFish::BasicTuna tuna;

        cout << "Using tuna.Swim() outputs: ";
        tuna.Swim(); // Here we call Tuna and its method directly

        cout  << "Sending tuna to MakeFishSwim(const BasicFish& fish) outputs: ";
        MakeFishSwim(tuna); // Sending tuna as a fish avoiding slicing and overriding parent method. But wait, huh?!

        cout << "Tuna overrides the Swim method, so why am I seeing the Fish implementation?!" << endl;
        cout << "I should be seeing: BasicTuna Swims!" << endl;

        /*
         * - There is technically nothing wrong with the code. However, the issue here is what the expected behaviour is
         *   v.s. what is actually occurring.
         *
         * - In the class declaration, Tuna is overriding the Swim() method and applying its own logic, as show in the
         *   console output.
         *
         * - When directly called, the Tuna method is called, no issues so far.
         *
         * - Tuna inherits from Fish, so even if I were to need a Fish as a method argument, Tuna is still an
         *   accepted reference. However, when passed to the reference, the application decides to directly reference
         *   the base class and invoke the Fish method, even though Tuna overrides the method.
         *
         * - This prevents any specialization code to be triggered! What we expect is to be able to properly trigger
         *   the right behaviour of any class that inherits from the base class, regardless of its subclass.
         *
         * - tl;dr: If I call a Tuna, which IS-A fish, I expect to see the Tuna swim and not a standard fish.
         * - So how do we fix this? We fix it by using VIRTUAL METHODS.
         */
    }
    cout << "\n\n" << endl;

    // Polymorphism using Virtual Methods
    {
        /*
         * - Virtual functions as discussed before, are needed in both Dynamic and subtype polymorphism in order to
         *   make it happen.
         *
         * - The first step will be to have an object of the base type, via a pointer or a reference. This object could
         *   have been initially instantiated as a subtype of the base class or a base object. The premise here is that
         *   we don't really care what type of object it is, all we care about is invoking the proper method regardless
         *   of its inheritance hierarchy type.
         *
         * - The syntax for declaring virtual methods is as follows:
         *  - In the base class: virtual ReturnType MethodName(ParameterList) {}
         *  - In the derived class: ReturnType MethodName(ParameterList) {}
         *  - As you can see, we only need to declare the base class's methods as virtual.
         *
         * - By making use of the virtual keyword, the compiler ensures that any overriding variant of the requested
         *   base class method is invoked.
         */

        cout << "Using virtual methods for polymorphism" << endl;

        VirtualFish::VirtualFish fish;
        VirtualFish::VirtualTuna tuna;
        VirtualFish::VirtualCarp carp;
        VirtualFish::VirtualFish* pointerFish = nullptr;

        cout << "Printing addresses of each fish type:" << endl;
        cout << "fish: " << &fish << endl;
        cout << "tuna: " << &tuna << endl;
        cout << "carp: " << &carp << endl;
        cout << endl;

        cout << "Invoking Swim method through a pointer of type VirtualFish. Pointer points at a default fish" << endl;
        pointerFish = &fish;
        cout << "Pointer's address: " << pointerFish << endl;
        pointerFish->Swim();
        cout << endl;

        cout << "Invoking Swim method through a pointer of type VirtualFish. Pointer points at a default fish" << endl;
        pointerFish = &tuna;
        cout << "Pointer's address: " << pointerFish << endl;
        pointerFish->Swim();
        cout << endl;

        cout << "Invoking Swim method through a pointer of type VirtualFish. Pointer points at a default fish" << endl;
        pointerFish = &carp;
        cout << "Pointer's address: " << pointerFish << endl;
        pointerFish->Swim();
        cout << endl;

        cout << "Invoking Swim method through a method. MakeVirtualFishSwim(const VirtualFish& fish), sending a fish"
        << endl;
        MakeVirtualFishSwim(fish);
        cout << endl;

        cout << "Invoking Swim method through a method. MakeVirtualFishSwim(const VirtualFish& fish), sending a tuna"
        << endl;
        MakeVirtualFishSwim(tuna);
        cout << endl;

        cout << "Invoking Swim method through a method. MakeVirtualFishSwim(const VirtualFish& fish), sending a carp"
        << endl;
        MakeVirtualFishSwim(carp);

        /*
         * - As you can see, the output of this section of the code is entirely different from the BasicFish
         *   implementation.
         *
         * - By making use of the virtual method, even if our methods/classes/etc. don't know the exact type of the
         *   derived object being handled, by at least providing a base class instance and a virtual method being
         *   overridden by the derived classes, the correct method will be invoked.
         *
         * - This is a really powerful tool that can allow us to expand and generalize our code to cover a wide range
         *   of use cases.
         *
         * - Unfortunately, with this incredible tool, new fail-safes and code security checks have to be put in place
         *   to ensure there are no memory leaks or bugs.
         */
    }
    cout << "\n\n" << endl;

    // Virtual Destructors
    {
        /*
         * - With C++ allowing us to allocate memory as needed, we have to take extra care on how we handle deletion
         *   and memory release.
         *
         * - Polymorphism, unsurprisingly, introduces new memory issues that have to be addressed in order to ensure
         *   our application works as expected.
         *
         * - Take a look at the code below but be aware of the memory issues this can cause in your system. Run at
         *   your own risk.
         */

        cout << "Why do we need Virtual Destructors!" << endl;
        cout << endl;

        cout << "Implementation with no virtual destructor implemented. Do you want to run this code? (y/n)" << endl;
        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            cout << "Allocating a tuna on the free memory store" << endl;
            BasicFish::BasicTuna* tuna = new BasicFish::BasicTuna;

            cout << "Deleting tuna through method: DeleteFish(const BasicFish* fish)" << endl;
            DeleteFish(tuna);

            cout << "Instantiating tuna in the stack" << endl;
            BasicFish::BasicTuna tuna2;
            cout << "Automatic destruction as it goes out of scope" << endl;

            cout << "We have a memory leak! The tuna on the free memory store was only cleared on its Fish slice "
                    "but the Tuna slice is now leaked, it was not cleared" << endl;
        }

        /*
         * - The destruction of the tuna allocated on the free store was partial. When the function invokes the delete
         *   operator, the tuna destructor is not invoked and that slice becomes lost in the system, a memory leak.
         *
         * - This is a big issue that we must solve if we want to ensure our application runs efficiently and safely.
         *
         * - This problem occurs because, just as with methods, there is no way to let the compiler know that the
         *   object is a derived type and not just a base type. This prompts the compiler to treat the object pointer
         *   as a base object, slicing it and tossing away the derived object slice without any sort of memory release.
         *
         * - Luckily for us, there is a way to solve this issue, and just as with methods, we need to declare a VIRTUAL
         *   DESTRUCTOR!
         *
         * - A VIRTUAL DESTRUCTOR, just as with methods, will ensure that the destructor of a derived class is invoked
         *   when deleting a pointer of type Base*.
         *
         * - Just as with methods, in order to declare a virtual destructor we need to add the virtual keyword to the
         *   destructor in the base class and then override the method in the derived classes.
         */

        cout << "Virtual Destructor was implemented! No more leaks!" << endl;

        cout << "Allocating a tuna on the free memory store" << endl;
        VirtualFish::VirtualTuna* tuna = new VirtualFish::VirtualTuna;

        cout << "Deleting tuna through method: DeleteVirtualFish(const VirtualFish* fish)" << endl;
        DeleteVirtualFish(tuna);

        {
            cout << "Instantiating tuna in the stack" << endl;
            VirtualFish::VirtualTuna tuna2;

            cout << "Automatic destruction as it goes out of scope" << endl;
        }

        cout << "No more leaks are present and all constructors and destructors match up in number!" << endl;

        /*
         * - As you can tell by the output, all constructors and destructors are being invoked. Regardless of the type
         *   being passed in the function Delete, now both the derived and base destructors are invoked, ensuring memory
         *   is properly released.
         *
         * - Adding virtual to these methods seems to solve a lot of problems regarding memory and polymorphic classes
         *   but, how does it all work? How does the compiler know which method belongs to each derived class if all we
         *   are providing is a BaseType argument?
         *
         * - Well, that takes us to our next topic - THE VIRTUAL FUNCTION TABLE aka V-TABLE.
         */
    }
    cout << "\n\n" << endl;

    // Virtual Function Table
    {
        /*
         * - Just as I mentioned, the compiler only knows that your function accepts a BaseType reference as an argument
         *   but there is no other additional information being passed along that clearly differentiates the object from
         *   a derived type against the base type.
         *
         * - So how does the application know which method to call? This is an important concept to understand because
         *   this decision is one that happens at runtime, using logic that implements polymorphism, which was supplied
         *   by the compiler when compiling the code.
         *
         * - Consider the following:
         *  - We have a base class that implements N virtual methods.
         *  - A derived class, overrides one of the methods, exposing the other virtual methods from the Base class.
         * - The compiler sees an inheritance hierarchy and understands that the Base class defines certain virtual
         *   methods that have been overridden in Derived.
         * - The compiler then creates a table known as the VIRTUAL FUNCTION TABLE (VFT) for every class that implements
         *   a virtual function/method.
         *
         * - A VFT can be represented as a static array of function pointers, where each pointer points to the virtual
         *   function (or override, if any exists) of interest. In case no override exists for a virtual method in a
         *   derived class, the VFT function pointer associated with that virtual method, will point to the Base class's
         *   method implementation.
         *
         * - This way, whenever an object is created from either the Base class or a Derived class, the object gets a
         *   pointer to their respective class VFT, which has already been populated with the correct method
         *   implementation, to be used whenever a Base object reference statement is used as the invoking entity.
         *
         * - Whenever a method is invoked this way, the compiler performs a lookup in the VFT of the types class and
         *   ensures the right method implementation is invoked.
         *
         * - Take a look at the example below. The Derived class does not implement one of the virtual methods. So the
         *   Derived VFT will be populated with two local function pointers and one (Foo2) pointer that points back to
         *   the Base class's method implementation.
         *
         * - Based on the output, we can see that even though we are using a Derived object as the invoking entity,
         *   thanks to the VFT, the parent method is called for the non-overridden method.
         *
         * - Also, thanks to the VFT, even though we are using a Base& object as the instigator, the VFT pointer being
         *   passed along with the object still points to the Derived VFT, which is why the compiler knows which method
         *   to invoke even when not using the actual object's type.
         *
         * - Something to note. The VFT pointer is a hidden member that the compiler generates for us. When compilation
         *   starts, if any class has a member declared as virtual, the compiler will automatically generate a VFT for
         *   the class and will also add a hidden pointer member to the class that points to the VFT.
         */

        class Base
        {
        public:
            virtual ~Base() = default;
            virtual void Foo1(){}
            virtual void Foo2() { cout << "Foo2 Base was called" << endl; }
            virtual void FooN(){}
        };

        class Derived : public Base
        {
        public:
            void Foo1(){ cout << "Foo1 Derived" << endl; } // Override base method
            // NOTICE THERE IS NO IMPLEMENTATION FOR Foo2()!
            void FooN(){ cout << "FooN Derived" << endl; }
        };

        class Utility
        {
        public:
            void DoSomething(Base& baseObject) const
            {
                cout << "Doing something in utility" << endl;
                baseObject.Foo1();
                baseObject.Foo2();
                baseObject.FooN();
            }
        };

        cout << "Demonstration of VFT!" << endl;
        cout << "First we will invoke a virtual method through a Derived object" << endl;
        cout << "The output should show the Base class method being invoked" << endl;
        Derived derived;
        derived.Foo2();

        cout << "Now, we will make use of methods that have been virtually overridden by calling a method through a "
                "Base type pointer " << endl;
        cout << "The output should show the Derived class methods override and the parent method that was "
                "not yet overridden" << endl;
        Base* basePointer;
        basePointer = &derived;
        Utility utility;
        utility.DoSomething(*basePointer);
    }
    cout << "\n\n" << endl;

    // Abstract Base Classes and Pure Virtual Functions
    {
        /*
         * - A base class that cannot be instantiated is called an ABSTRACT BASE CLASS.
         *
         * - This type of class fulfills a single purpose: To be used in an inheritance hierarchy by a class that
         *   derives from it.
         *
         * - In C++, we can create this type of class by using PURE VIRTUAL methods.
         *
         * - A virtual method is said to be PURE VIRTUAL when declared like this:
         *  - virtual ReturnType MethodName() = 0;
         *  - This declaration essentially tells the compiler that the Method needs to be implemented by the class that
         *    derives from an ABSTRACT BASE CLASS.
         *
         * - This way, the ABSTRACT BASE CLASS ensures that a derived class must provide an implementation for the PURE
         *   VIRTUAL METHODS. This functionality, where a base class can enforce support for methods with a specified
         *   name and signature in classes that derive from it, is called: AN INTERFACE.
         *
         * - Abstract base classes are thus a very good mechanism for declaring functions that you expect derived
         *   classes to implement and fulfill.
         */

        cout << "Abstract class implementation!" << endl;

        //AbstractFish::AbstractFish absFish; // This fails as the class being abstract, cannot be instantiated
        AbstractFish::AbstractTuna abstractTuna;
        AbstractFish::AbstractCarp abstractCarp;

        MakeAbstractFishSwim(abstractTuna);
        MakeAbstractFishSwim(abstractCarp);
    }
    cout << "\n\n" << endl;

    // The Diamond Problem and how to solve it
    {
        /*
         * - In the previous module - Inheritance.cpp - we implemented a class called Echidna. This class inherits from
         *   2 different classes, Mammal and Bird. However, if we get more technical, both of these Classes can also
         *   inherit from a more general class: Animal, that can implement a variety of methods common to all Animals.
         *
         * - So, if we have all these classes that all inherit from the same Base, and as we know, per derived class, an
         *   instance of the base class is created. How many times is the Base class being instantiated then per echidna
         *   object?
         *
         * - Let's explore this case with an even more tricky animal, a Platypus.
         */

        {
            class Animal
            {
            public:
                Animal() { cout << "Animal constructor" << endl; }

                int age;
            };

            class Mammal :public Animal{}; // Feeds milk to young ones
            class Bird : public Animal{}; // Lays eggs
            class Reptile : public Animal{}; // Has venom it can inject

            class Platypus : public Mammal, public Bird, public Reptile
            {
            public:
                Platypus() { cout << "Platypus constructor" << endl; }
            };

            cout << "Diamond problem and how virtual helps to solve it" << endl;
            cout << "Analyse this code: " << endl;
            Platypus perry;
            //perry.age = 10; // What is going on here!? Look below.
            cout << endl;
        }

        /*
         * - Why does this line cause the compiler to fail compilation? Well, that is because this object has 3
         *   instances of the base class Animal!
         *
         * - The compiler does not know which of the 3 instances you are addressing and as such, prevents compilation to
         *   avoid errors! However, this can be solved by directly addressing each one of the parent classes age.
         *   - perry.Mammal::age = 10;
         *   - perry.Bird::age = 10;
         *   - perry.Reptile::age = 10;
         *   - This is too convoluted and simply put, a coding nightmare!
         *
         * - This problem is known as THE DIAMOND PROBLEM. It gets its name from the diagram shape that results in
         *   revising the class relationship between all the classes involved.
         *
         * - The problem will always occur when in an inheritance hierarchy containing two or more base classes that
         *   inherit from a common base, the compiler fails to properly resolve the base type reference ambiguity.
         *
         * - In the long run, having these many base instances will bloat our memory. As it stands, 3 instances of a
         *   base class per platypus object is totally unnecessary. However, we still want to be able to give to the
         *   platypus the abilities of 3 different types of animals, so how do we fix this issue?
         *
         * - By making use of VIRTUAL INHERITANCE!
         *
         * - If you expect a derived class to be used as a Base Class, it is a good idea to define its relationship to
         *   the base class by using the keyword virtual:
         *   - class Derived : public virtual Base
         *
         * - Run the program and take a look at the output of the scope below.
         */

        {
            class Animal
            {
            public:
                Animal() { cout << "Animal constructor" << endl; }

                int age;
            };

            class Mammal :public virtual Animal{};
            class Bird : public virtual Animal{};
            class Reptile : public virtual Animal{};

            class Platypus final : public Mammal, public Bird, public Reptile
            {
            public:
                Platypus() { cout << "Platypus constructor" << endl; }
            };

            cout << "Now analyse this code: " << endl;
            Platypus perry;
            perry.age = 10; // No compilation errors!
        }

        /*
         * - As you can see, we now only have a single instance of the animal class, representative of the single
         *   platypus object we instantiated. This is because of the new inheritance hierarchy with the use of virtual.
         *
         * - What the keyword does is ensure that whenever base classes that share the same Super-Base Class are grouped
         *   together under a single derived class, the common Super-Base Class (Animal) only exists as a single
         *   instance.
         *
         * - This helps to solve a lot of ambiguity issues and allows the code to properly run. If you take a look in
         *   the code, directly addressing a member variable of the Super-Base Class is now possible and there are no
         *   more ambiguity issues, as only a single instance of the Super-Base Class exists now.
         */
    }
    cout << "\n\n" << endl;

    // THE OVERRIDE!
    {
        /*
         * - Whenever we are programming, mistakes are bound to happen, specially when working with complex inheritance
         *   hierarchies. A common problem that shows up, is failure to properly override member methods from the base
         *   class. As we have seen through this lesson, proper method overriding and inheritance is a must in order to
         *   get polymorphism to work.
         *
         * - So, how can we ensure that we are properly overloading base methods? The compiler does not throw any
         *   exceptions or errors because there are no mistakes. The compiler sees the method as either a method
         *   overload or a new method altogether. This then does not prompt the programmer to look for errors until bugs
         *   appear later on.
         *
         * - Luckily for us, C++ 11 introduced a handy specifier that, although not required, helps enforce the idea
         *   that we are indeed planning to override a base method and will prompt the compiler to verify that we are,
         *   indeed, properly overriding a base method.
         *
         * - Whenever the override specifier is used the main things the compiler cares about are:
         *  - Is the base class's method declared as virtual?
         *  - Does the signature of the base class virtual function exactly matches the signature of the derived class
         *    function declared to override?
         *
         * - If none of the checks above are true, the compiler will fail and will throw an error, helping you to
         *   prevent bugs down the line. Of course, the regular old fashion overriding will still work but by marking
         *   base class methods as abstract and allowing the derived class to implement its own logic will be a safer
         *   practice. OF COURSE, THIS WILL DEPEND ON YOUR SYSTEM DESIGN REQUIREMENTS! So if needed, use the base class
         *   as well as a totally valid object.
         */

        cout << "Override specifier implementation!" << endl;
        OverrideFish::OverrideFish* overrideFish;
        OverrideFish::OverrideTuna overrideTuna;

        overrideFish = &overrideTuna;
        overrideFish->Swim();
        overrideTuna.Swim();

        overrideTuna.Eat(); // Uses classic override. No virtual keyword or override specifier
        overrideTuna.OverrideFish::Eat();
    }
    cout << "\n\n" << endl;

    // Preventing function overriding
    {
        /*
         * - We can prevent derived classes from overriding base methods by using the keyword FINAL.
         *  - Just as with classes, marking a method final means no other changes can be done to it.
         */
    }

    // A take on copy constructors, are virtual ones possible?
    {
        /*
         * - It is technically impossible in C++ to have virtual copy constructors. If such a feature existed, it would
         *   then be possible to create a collection of BaseType*, with each element being a specialisation of that
         *   type. Once that collection is done, we could then assign it to another collection where the copy
         *   constructor will ensure a deep copy of the derived class, ensuring that all objects remain as their
         *   specialisation.
         *   - This however is a dream... (For now).
         *
         * - A virtual copy constructor is impossible to program as most of the polymorphic behaviour we see and program
         *   happens at runtime. Constructors on the other hand, are not polymorphic and can only construct a fixed
         *   type, hence why C++ prevents the use of virtual copy constructors.
         *
         * - However, code always finds a way. You can implement such a behaviour by coding your own cloning method
         *   directly in the base class as a pure virtual method. This way, you have a simulated virtual copy
         *   constructor with only one downside. It has to be manually invoked.
         */

        const int ARRAY_SIZE = 4;

        OverrideFish::OverrideFish* myFishes[ARRAY_SIZE];
        myFishes[0] = new OverrideFish::OverrideTuna();
        myFishes[1] = new OverrideFish::OverrideCarp();
        myFishes[2] = new OverrideFish::OverrideBlueFinTuna();
        myFishes[3] = new OverrideFish::OverrideCarp();

        OverrideFish::OverrideFish* myNewFishes[ARRAY_SIZE];

        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            myNewFishes[i] = myFishes[i]->Clone();
        }

        for (const auto& myNewFish : myNewFishes)
        {
            myNewFish->Swim();
        }

        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            delete myFishes[i];
            delete myNewFishes[i];
        }
    }

    // FINAL REMARKS
    {
        /*
         * - When implementing abstract classes, remember to add the keyword VIRTUAL to its member methods, so derived
         *   classes are aware that they require their own implementation.
         *
         * - Any method that you mark as PURE VIRTUAL will cause the class to become an abstract class, enforcing
         *   derived classes to implement their own method logic.
         *
         * - Enforce safe and readable code by making use of the override keyword when overriding base class methods.
         *
         * - Use virtual inheritance when required to avoid diamond problems.
         *
         * - Always supply your base class with a virtual destructor!
         *
         * - You can't instantiate abstract classes, so pay attention to how you implement your types.
         *
         * - Abstract classes are meant to be the barebones blueprint of methods for derived classes.
         *   You can still define member variables and method implementation, but be aware that no object of this
         *   class be instantiated, so be smart about your system design!
         */
    }

    return 0;
}