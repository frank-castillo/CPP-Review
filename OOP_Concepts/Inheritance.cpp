//
// Created by juanf on 2024-08-23.
//

#include <iostream>
#include <chrono>

using std::cout, std::endl, std::cin, std::string;

class Fish
{
protected:
    bool isFreshWaterFish; // If used with protected, can only be accessed by derived classes and friends

public:
    Fish(const bool isFreshWater): isFreshWaterFish(isFreshWater) // Overloaded constructor
    {
        cout << "Fish constructor" << endl;
    }

    ~Fish()
    {
        cout << "Fish destructor" << endl;
    }

    void Swim() const
    {
        if(isFreshWaterFish)
        {
            cout << "Swims in lake" << endl;
        }
        else
        {
            cout << "Swims in sea" << endl;
        }
    }
};

class Tuna : public Fish
{
public:
    Tuna(): Fish(false) // Constructor initializes base class
    {
        cout << "Tuna constructor" << endl;
    }

    ~Tuna()
    {
        cout << "Tuna destructor" << endl;
    }

    // Protected accessor, implemented before base class initialization via derived constructor initialization
    //Tuna() { isFreshWaterFish = true; } // bool still accessible by derived classes while using protected

    void Swim() const
    {
        cout << "Tuna swims real fast" << endl;
    }
};

class Carp : public Fish
{
public:
    Carp(): Fish(true) // Constructor initializes base class
    {
        cout << "Carp constructor" << endl;
    }

    ~Carp()
    {
        cout << "Carp destructor" << endl;
    }

    // Protected accessor, implemented before base class initialization via derived constructor initialization
    //Carp() { isFreshWaterFish = true; } // bool still accessible by derived classes while using protected

    void Swim() const
    {
        cout << "Carp swims real slow" << endl;
    }

    void SwimWithFish() const
    {
        cout << "Carp swims real fish" << endl;
        Fish::Swim(); // Invoking base class method
    }
};

namespace CarClasses
{
    class Motor
    {
    public:
        void SwitchIgnition() const
        {
            cout << "Ignition On" << endl;
        }

        void PumpFuel() const
        {
            cout << "Fuel in cylinders" << endl;
        }

        void FireCylinders() const
        {
            cout << "I am Speed! Vroom!" << endl;
        }
    };

    class PrivateCar : private Motor
    {
    public:
        void Move() const
        {
            cout << "Move the car!" << endl;
            SwitchIgnition(); // As you can see, the base members are still available in the class
            PumpFuel();
            FireCylinders();

            //However, if outside the scope of the class, nothing can access the base methods!
        }
    };

    class Car : protected Motor
    {
    public:
        void Move() const
        {
            cout << "Move the car!" << endl;
            SwitchIgnition(); // As you can see, the base members are still available in the class
            PumpFuel();
            FireCylinders();
        }
    };

    class RaceCar : protected Car
    {
    public:
        void Move() const
        {
            cout << "Move the Race Car!" << endl;
            SwitchIgnition();
            PumpFuel();
            FireCylinders();
            FireCylinders();
            FireCylinders();

            /*
             * - As you can see, the RaceCar class still has access to the public members of Motor because of the
             *   protected access specifier.
             * - Car inherits it from Motor, and RaceCar then inherits the base methods through Car.
             * - If we were to change the access specifier to private, we will still get access to them but any classes
             *   that were to inherit from RaceCar will lose access to the base's methods. See example below.
             */
        }
    };

    class PrivateRaceCar : private Car
    {
    public:
        void Move() const
        {
            cout << "Move the Race Car!" << endl;
            SwitchIgnition();
            PumpFuel();
            FireCylinders();
            FireCylinders();
            FireCylinders();
        }
    };

    class TestCar : protected PrivateCar
    {
    public:
        void Move() const
        {
            //SwitchIgnition(); // Error compiling: Member is inaccessible. Reason: PrivateRaceCar inherits privately
            // Because of the private inheritance, TestCar can no longer access the base class's methods.
        }
    };
}

int main()
{
    // INHERITANCE
    {
        /*
         * - Inheritance allows classes to that are similar to derive from a base class that contains common attributes
         *   and implements common functionality.
         * - Derived classes can then OVERRIDE the base functionality to implement their own behaviour, making each
         *   class unique.
         * - Because derived classes directly inherit their functionality from the base class, they are also considered
         *   the same type as the base class. Similarly to how you are considered a member of your family even though
         *   you are your own individual.
         * - This type of relationship between a base clas and a derived class is known as an "is-a". However, this is
         *   only applicable to public inheritance cases, which are the most common ones.
         * - To exemplify the point above: Car is the base class. A Mazda CX-5, is its own class, but it inherits from the
         *   base functionality of a car. Thus, we can say, a Mazda CX-5 is-a car. A Corolla is-a car.
         * - With that in mind, both cars inherit common characteristics from the base class "Car" yet each of them will
         *   have a different engine, size, specs, etc. which helps distinguish them from just a Car.
         *
         * - Inheritance can come many in many forms, with the common ones being:
         *  - Single inheritance: only one class used as the base class.
         *  - Multiple inheritance: multiple classes used as the base for a derived class.
         *  - Multilevel inheritance: a class is derived from a class that is also derived from another class.
         *  - Hybrid inheritance: inheritance that is the result of multiple types of inheritance being used.
         *  - Hierarchical inheritance: multiple derived classes that inherit from the same base. (Like cars.)
         *
         * - Example of inheritance syntax
         *  - class Base{ // Insert members and methods};
         *  - class Derived : access-specifier (public/private/protected) Base { // Insert members, methods, and override methods};
         *
         * - Based on the access specifier of the inheritance, the type of relationship between classes will change.
         *  - When using "public", the relationship is: "is a". A Mazda IS A car.
         *  - When using "private" or "protected" is: "has a". A Mazda HAS AN engine.
         *
         * - Take a look at the example of the fish class. On the derived classes Tuna and Carp we are calling the method
         *   swim, however, this method is never implemented directly in the class. Similarly, the constructor of both
         *   classes access the boolean value, yet none of the derived classes implements it. This happens because
         *   both the method and boolean value are defined as public in the base class, thus marking them accessible
         *   and modifiable through instances of the derived classes that PUBLICLY INHERIT from the base class.
         * - This implementation however, leaves the class and application to the introduction of serious bugs as the
         *   bool flag can be modified anywhere else in the program by anything.
         *
         * - If we want to prevent external modification of the boolean we need a mechanism that still allows derived
         *   classed to modify chosen attributes of the base class while denying access to these attributes to the
         *   program/application.
         * - Here is where the PROTECTED keyword comes in handy.
         * - By declaring member attributes with this access specifier, we are making them accessible to any derived
         *   class and friend classes while simultaneously making it inaccessible to everyone else outside that class.
         * - This is a perfect example of the principles of OOP. We are abstracting our members through the protected
         *   and public accessors. Using inheritance to create derived classes that can safely access base class members
         *   that cannot be tampered with by anyone outside the hierarchical system.
         *
         *   - Imagine we have an object of type Tuna. Tuna inherits from Fish and all the members are public.
         *   - This is a situation which can lead to bugs or unexpected behaviour if left as is... (public accessor case)
         *   - tuna.isFreshWaterFish = true; // Tunas are not freshwater fishes, yet we can freely modify this value anywhere
         *   - Once we implemented the protected access specifier, the line above would stop compiling as main no longer
         *     would have access to the member variable.
         */

        // Base class initialization: Passing parameters to the base class
        {
            /*
             * - What happens when we have an overloaded constructor that requires arguments at the time of instantiation?
             * - How can such a base class be instantiated when the derived class is being constructed?
             * - The answer: List initialization and base class constructor invocation via derived class constructor.
             * - This design is really helpful in ensuring that every derived class is forced to initialize a set of
             *   members that are required for proper behaviour. (See fish clas implementation)
             * - By applying this design the base class ensures that derived classes do not contain uninitialized values,
             *   null references, rubbish values, etc. This also ensures that an object of a derived class cannot be
             *   instantiated unless it properly initializes the base class.
             * - To further enhance program security and abstraction, you can mark the bool of the base as private. This
             *   is the case with this scenario because the derived class never modifies the bool flag directly, only the
             *   base class does. Because of that, there is no need for the derived class to get access to it, so the
             *   member can be private.
             */

            class Base
            {
            protected:
                int mNumber;

            public:
                Base(int someNumber) : mNumber(someNumber) {} // Overloaded constructor
            };

            class Derived : public Base
            {
            public:
                Derived() : Base{10} {} // // Constructor initializes base class
            };

            cout << "Base class initialisation via derived constructor" << endl;

            Carp carp{};
            Tuna tuna{};

            /*
             * - If you take a look at the output. You will see that first the fish constructor is invoked and later on
             *   the derived class constructor is invoked.
             */
        }
        cout << "\n\n" << endl;

        // Derived class overriding the base class methods
        {
            /*
             * - If any derived classes implement the same methods with the same return values and signatures as in the
             *   base class from which it inherits, it effectively overrides the base method.
             * - This results in calls made to that method invoking the local implementation of the derived class rather
             *   than the parent class.
             */

            class Base
            {
            protected:
                int mNumber;

            public:
                Base(int someNumber) : mNumber(someNumber) {} // Overloaded constructor

                void DoSomething() { cout << "DoSomething in Base" << endl; }
            };

            class Derived : public Base
            {
            public:
                Derived() : Base{10} {} // // Constructor initializes base class

                void DoSomething() { cout << "DoSomething in Derived" << endl; }
            };

            cout << "Overloading base class methods" << endl;

            Fish aFish{true};
            Fish anotherFish{false};
            Carp carp{};
            Tuna tuna{};

            cout << "Calling base class swim" << endl;
            aFish.Swim();
            anotherFish.Swim();

            cout << "Calling derived classes swim" << endl;
            carp.Swim();
            tuna.Swim();

            cout << "\n\n" << endl;

            // Invoking overridden methods of a base class
            {
                /*
                 * - In the previous examples we saw how by defining a method in the derived class that follows the same
                 *   definition syntax as the base class, effectively overrides it.
                 * - However, because our derived classes are inheriting from a base class with public methods, we can
                 *   directly invoke the base's class methods with the help of the SCOPE RESOLUTION OPERATOR (::).
                 * - The syntax for that is as follows:
                 *   derivedClass.ParentClassType::Method()
                 * - See example below
                 */

                cout << "Invoking overridden methods of a base class" << endl;

                cout << "Calling base class method through tuna directly == tuna.Fish::Swim()" << endl;
                tuna.Fish::Swim(); // Invokes Fish::Swim() via a Tuna instance instead of Tuna::Swim()

                cout << "Calling Carp method and then base clas method through Carp instance == ";
                cout << "carp.Swim() followed by carp.Fish::Swim()" << endl;
                carp.Swim();
                carp.Fish::Swim();
            }
            cout << "\n\n" << endl;

            // Invoking methods of a base class in a derived class
            {
                /*
                 * - Typically the base class method will contain a generic implementation that is applicable to all
                 *   derived classes.
                 * - If your derived classes need to make use of the base class's generic implementation of a method,
                 *   you can use the scope resolution operator to directly invoke it in any derived class method.
                 * - This will be done in the class definition, so see the Tune/Carp class at the top of the file for a
                 *   more in depth implementation than the example below.
                 */

                class BaseMethod
                {
                public:
                    void DoSomething() const
                    {
                        // Base default behaviour
                    }
                };

                class DerivedMethod : public BaseMethod
                {
                public:
                    void DoSomething() const
                    {
                        cout << "DoSomething in DerivedMethod" << endl;
                        BaseMethod::DoSomething(); // Using scope resolution operator to invoke the base class method
                    }
                };

                cout << "Invoking methods of a base class in a derived class" << endl;

                cout << "Calling tuna method" << endl;
                tuna.Swim();

                cout << "Calling carp method" << endl;
                carp.Swim();

                cout << "Calling base class method through Carp method == carp.SwimWithFish()" << endl;
                carp.SwimWithFish();

                cout << "Calling base class method through tuna directly == tuna.Fish::Swim()" << endl;
                tuna.Fish::Swim();
            }
            cout << "\n\n" << endl;

            // A derived class hiding a base class's methods
            {
                /*
                 * - Overriding can take an extreme form when one derived classes overridden method can potentially hide
                 *   all the versions of an overloaded method belonging to the base class./
                 * - In extreme cases this can cause compilation errors whenever any of the overloaded methods are used.
                 * - This form is then called hidden.
                 * - Take a look at the implementation below:
                 */

                class HiddenFish
                {
                public:
                    void Swim() const { cout << "Fish Swims!" << endl; }
                    void Swim(bool isFreshWaterFish) const
                    {
                        (isFreshWaterFish) ? cout << "Swims in lake" << endl : cout << "Swims in sea" << endl;
                    }
                };

                class HidingTuna : public HiddenFish
                {
                public:
                    void Swim() const { cout << "Tuna swims real fast" << endl; }
                };

                class HidingCarp : public HiddenFish
                {
                public:

                    // Second solution to the problem
                    using HiddenFish::Swim;

                    void Swim() const { cout << "Tuna swims real slow" << endl; }
                };

                class HidingBass : public HiddenFish
                {
                public:
                    void Swim() const
                    {
                        cout << "Bass swims at moderate pace" << endl;
                        HiddenFish::Swim(); // Hybrid implementation via override and base method invoking
                    }

                    // Third solution overriding all base methods and using the (::) operator
                    void Swim(bool isFreshWaterFish) const
                    {
                        // Third solution with scope resolution operator
                        HiddenFish::Swim(isFreshWaterFish);
                    }
                };

                cout << "Derived class hiding a base class's methods" << endl;

                HidingTuna hTuna{};

                //hTuna.Swim(false); // If uncommented it will fail to compile! Tuna::Swim() hides Fish::Swim(bool)
                hTuna.Swim(); // HidingTuna base implementation and only using the local one

                /*
                 * - Because Tuna inherits from Fish, both methods from the base should be available to the derived
                 *   class. The problem lies in the overriding function. Tuna overrides one of the overloaded methods
                 *   from the base class, causing the compiler to no longer see the base class methods, thus hiding them.
                 * - It won't matter which overload method you override, by doing so, the compiler will still lose sight
                 *   of all other base methods. Fortunately, there are ways to get around this issue such as:
                 *      - Using the scope resolution operator.
                 *      - Use the keyword USING in the class Tuna to reveal Swim() in the class.
                 *      - Override all overloaded variants of Swim() in the class Tuna and invoke the base class
                 *        methods through the scope resolution operator.
                 */

                // First solution
                hTuna.HiddenFish::Swim(false);

                HidingCarp hCarp{};
                hCarp.Swim(true); // Here, we get access to the base method thanks to the using keyword
            }
            cout << "\n\n" << endl;
        }
        cout << "\n\n" << endl;

        // Order of construction and Destruction
        {
            // Order of construction
            /*
             * - The instantiation sequence of objects, classes and attribute members is standardised.
             * - Base class objects are instantiated before derived classes. This way, member attributes are ready to be
             *   used by the time the derived class is instantiated.
             * - Member attributes are initialized and instantiated before constructor invoking. This applies to both
             *   base and derived classes. This guarantees that all member attributes are ready before any logic triggers
             *   the class.
             */

            // Order of destruction
            /*
             * - The sequence of destruction is the opposite of the sequence of construction.
             * - The destructor of the derived class happens first before that of the base class.
             */

            cout << "\n\n\nOrder of construction and destruction" << endl;

            Tuna aTuna{};
            Carp aCarp{};
        }
        cout << "\n\n" << endl;

        // Private Inheritance
        {
            /*
             * - Private inheritance makes use of the private accessor in the inheritance specifier of a derived class.
             * - In this type of inheritance, all public member methods and attributes are private. Rendering them
             *   inaccessible to anyone with an instance of the derived class.
             * - Even if members of the base class are marked as public, they can only be consumed by the derived class
             *   but not any other entity in possession of an object of the derived class.
             * - This relationship between the base class and derived class then changes to a "HAS-A" instead of "IS-A"
             * - The perfect example would be a car: Car HAS AN Engine/Motor
             * - In the example below as you can see, when we call the public method Move from car, the base methods
             *   are still being called through the class. However, if you try to invoke them directly through the car
             *   instance or the :: operator, the compilation will fail as the inheritance is private, so no one other
             *   than the class can access those methods.
             */

            cout << "Private inheritance implementation!" << endl;

            CarClasses::PrivateCar mazda;
            mazda.Move();

            // These next lines will cause the program to not compile
            //mazda.FireCylinders(); // Error message: Member is inaccessible. Reason: Private accessor.
            //mazda.Motor::PumpFuel(); // Error message: Member is inaccessible. Reason: Private accessor.

            /*
             * - The same concept would apply to any other classes that inherit from Car. Car already inherits privately
             *   from Motor, meaning that all entities other than Car have private access (NO ACCESS) to public and
             *   protected members of Motor (Base class) when using an instance of car.
             *
             * - The compiler then gives priority to the most restrictive access specifier in its calculation of whether
             *   one class should have access to a base class's public or protected members.
             */
        }
        cout << "\n\n" << endl;

        // Protected Inheritance
        {
            /*
             * - Protected inheritance is similar to private inheritance in that:
             *  - It also signifies a "HAS-A" relationship.
             *  - It also lets the derived class access all public and protected members of the Base class.
             *  - Those outside the inheritance hierarchy with an instance of Derived cannot access public members of
             *    base.
             * - The main difference however, is that protected inheritance will allow subclasses of the Derived class
             *   to access the Base's public and protected members. This is not possible in private inheritance!
             * - The access to methods then resides in the relationship between the super class (Base Class) and
             *   all of its subclasses, from which other subclasses will then be based of.
             * - Think of it as connections:
             *  - If you have the connections to a company, you get preference treatment.
             *  - If you are the son of the person who has the connections, you inherit those connections and thus can
             *    access the preference treatment.
             *  - If you know the company but have no connections then you get no access to the preference treatment.
             *    You can still access services from the company but not the preference ones.
             *  - Same with classes. Based on the level of access specifier you give to the class, it will determine what
             *    it has access to and what it can offer to other classes.
             */

            cout << "Protected inheritance implementation!" << endl;

            CarClasses::RaceCar ferrari;
            ferrari.Move();
        }
        cout << "\n\n" << endl;

        // IMPORTANT NOTES ON INHERITANCE
        {
            /*
             * - Use private or protected inheritance only when you have to. These specifiers can be restrictive and can
             *   affect the way on how you design systems.
             * - In some cases, depending on your system design, it would be better to make use of composition or
             *   aggregation concepts to better scalate your classes and properly control lifecycles and entity
             *   ownership.
             * - See the section on composition and aggregation at the end of this document.
             */
        }

        // The problem of slicing
        {
            // What happens when a programmer does the following?
            //Derived objDerived{};
            //Base objBase = objDerived; // Assignment copy

            // Second case scenario:
            // void UseBase(Base inputClass){}
            // Derived objDerived{};
            // UseBase(objDerived); // Copy of objDerived will be sliced and sent to the function.

            /*
             * - In all the cases above, an object of type Derived is being copied into another object of type Base,
             *   either explicitly via assignment or by being passed as an argument. So, how does this affect the
             *   execution of the program and the inner workings of the involved classes?
             * - The compiler ends up copying only the Base class part of the derived object and not the complete object.
             *  - The information contained by the data members belonging to Derived class portion is lost in the
             *    copy process.
             *  - This process is not anticipated, and this unwanted reduction of that part of the data that makes
             *    derived a specialisation of Base is called SLICING.
             * - To avoid slicing problems, don't pass parameters by value. Pass them as pointers to the base class or
             *   as a reference (making use of const) to the base class.
             *
             * - Solution examples:
             * void UseBase(const Base& base); Using const references
             * void UseBase(const Base* base); Using const pointers
             *
             * - Whichever method you choose, the proper method will be called and no object slicing will occur!
             */

            class Base
            {
                friend class ProcessClass;
            public:
                void Display() const { cout << "Base class implementation" << endl; }
            };

            class Derived : public Base
            {
            public:
                void Display() const { cout << "Derived class implementation" << endl; }
            };

            class ProcessClass
            {
            public:
                void ProcessBaseClass(const Base& base) const { base.Display(); }
            };

            cout << "Fixing slicing issues!" << endl;
            Derived derived;
            ProcessClass pc;

            cout << "Invoking: pc.ProcessBaseClass(derived)" << endl;
            cout << "Derived class is passed as an argument but using const & prevents slicing" << endl;
            pc.ProcessBaseClass(derived);
        }
        cout << "\n\n" << endl;

        // Composition and Aggregation
        {
            /*
             * - Composition and aggregation are both techniques used to model relationships between classes,
             *   specifically "whole-part" relationships. Differing only in terms of ownership, lifecycle management,
             *   and the nature of the relationship between classes.
             */

            // Composition
            {
                /*
                 * - Strong ownership (part-whole relationship)
                 *  - In composition, the containing object (whole) strongly owns the contained object (part).
                 *  - The lifetime of the part is strictly bound to the lifetime of the whole. When the containing
                 *    object is destroyed, all its parts are destroyed.
                 *  - The part cannot exist without the whole.
                 * - Best used when the part is integral to the overall behaviour and proper functioning of a class.
                 * - Best example, a human and its heart! A heart is necessary for a human to be alive and the heart
                 *   cannot exist by itself, even if it's an artificial one. Both the human and the heart need each
                 *   other to operate!
                 */

                class Heart final
                {
                public:
                    Heart(){}
                    ~Heart(){}
                };

                class Human final
                {
                public:
                    Human() { mHeart = std::make_unique<Heart>(); }
                    ~Human() { mHeart.reset(); }

                private:
                    std::unique_ptr<Heart> mHeart;
                };
            }

            // Aggregation
            {
                /*
                 * - Weak ownership (whole-parts relationship)
                 *  - In aggregation, the containing object (whole) does not strongly own the contained object (part).
                 *  - The parts can exist independently of the whole.
                 *  - When the containing object (whole) is destroyed, the parts may continue to exist.
                 * - In aggregation, there can be cases in which a part is shared among multiple whole objects.
                 */

                class Student final
                {
                };

                class Course final
                {
                private:
                    std::vector<const Student*> students;

                public:
                    Course()
                    {
                        students.reserve(15); // Reserving an initial contiguous memory block.
                    }

                    ~Course()
                    {
                        students.clear();
                    }

                    void AddStudent(const Student* student) { students.push_back(student); }
                };

                class AttendanceList final
                {
                private:
                    std::vector<const Student*> students;

                public:
                    AttendanceList()
                    {
                        students.reserve(15); // Reserving an initial contiguous memory block.
                    }

                    ~AttendanceList()
                    {
                        students.clear();
                    }

                    void AddStudent(const Student* student) { students.push_back(student); }
                };

                // auto* aStudent = new Student();
                // Add student to Course;
                // Add student to AttendanceList;

                // Once either the course or attendance list is destroyed, or even both. The student object will still
                // exist and be accessible by other entities. They were part of two wholes. but their lifetime and
                // overall functionality is not hindered by them not existing any more.
                // delete aStudent;
            }
        }
    }

    return 0;
}