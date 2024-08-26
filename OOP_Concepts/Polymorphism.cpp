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
         * - In the class declaration, Tuna is overriding the Swim() method and applying its own logic, as show in the
         *   console output.
         * - When directly called, the Tuna method is called, no issues so far.
         * - Tuna inherits from Fish, so even if I were to need a Fish as a method argument, Tuna is still an
         *   accepted reference. However, when passed to the reference, the application decides to directly reference
         *   the base class and invoke the Fish method, even though Tuna overrides the method.
         * - This prevents any specialization code to be triggered! What we expect is to be able to properly trigger
         *   the right behaviour of any class that inherits from the base class, regardless of its subclass.
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
         * - The first step will be to have an object of the base type, via a pointer or a reference. This object could
         *   have been initially instantiated as a subtype of the base class or a base object. The premise here is that
         *   we don't really care what type of object it is, all we care about is invoking the proper method regardless
         *   of its inheritance hierarchy type.
         * - The syntax for declaring virtual methods is as follows:
         *  - In the base class: virtual ReturnType MethodName(ParameterList) {}
         *  - In the derived class: ReturnType MethodName(ParameterList) {}
         *  - As you can see, we only need to declare the base class's methods as virtual.
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
         * - By making use of the virtual method, even if our methods/classes/etc. don't know the exact type of the
         *   derived object being handled, by at least providing a base class instance and a virtual method being
         *   overridden by the derived classes, the correct method will be invoked.
         * - This is a really powerful tool that can allow us to expand and generalize our code to cover a wide range
         *   of use cases.
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
         * - Polymorphism, unsurprisingly, introduces new memory issues that have to be addressed in order to ensure
         *   our application works as expected.
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
         * - This is a big issue that we must solve if we want to ensure our application runs efficiently and safely.
         * - This problem occurs because, just as with methods, there is no way to let the compiler know that the
         *   object is a derived type and not just a base type. This prompts the compiler to treat the object pointer
         *   as a base object, slicing it and tossing away the derived object slice without any sort of memory release.
         * - Luckily for us, there is a way to solve this issue, and just as with methods, we need to declare a VIRTUAL
         *   DESTRUCTOR!
         * - A VIRTUAL DESTRUCTOR, just as with methods, will ensure that the destructor of a derived class is invoked
         *   when deleting a pointer of type Base*.
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
         * - Adding virtual to these methods seems to solve a lot of problems regarding memory and polymorphic classes
         *   but, how does it all work? How does the compiler know which method belongs to each derived class if all we
         *   are providing is a BaseType argument?
         * - Well, that takes us to our next topic - THE VIRTUAL FUNCTION TABLE aka V-TABLE.
         */
    }
}