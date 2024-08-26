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
        void Swim() const
        {
            cout << "BasicFish Swims!" << endl;
        }
    };

    class BasicTuna : public BasicFish
    {
    public:
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

        constexpr BasicFish::BasicTuna tuna;

        cout << "Using tuna.Swim() outputs: ";
        tuna.Swim(); // Here we call Tuna and its method directly

        cout  << "Sending tuna to MakeFishSwim(const BasicFish& fish) outputs: ";
        MakeFishSwim(tuna); // Sending tuna as a fish avoiding slicing!

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
}