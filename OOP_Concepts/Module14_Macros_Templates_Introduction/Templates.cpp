//
// Created by juanf on 2024-09-06.
//

#include <iostream>
#include <tuple>

// Module 14

using std::cout, std::endl, std::string, std::tuple;

template <typename objType>
const objType& GetMax(const objType& value1, const objType& value2)
{
    return value1 > value2 ? value1 : value2;
}

template <typename Type>
void DisplayComparison(const Type& value1, const Type& value2)
{
    cout << "GetMax(" << value1 << ", " << value2 << ") = " << GetMax(value1, value2) << endl;
}

namespace BasicTemplateClass
{
    template<typename T>
        class HoldVarTypeT
    {
    private:
        T value; // The type of variable value is T, and T is resolved at the time the template is instantiated.

    public:
        void SetValue(const T& newValue) { value = newValue; }
        const T& GetValue() const { return value; }
    };

     class Human
     {
     public:
        string name;
        int age;

        void IntroduceSelf() const
        {
            cout << "I am " + name << " and am ";
            cout << age << " years old" << endl;
        }
     };

}

namespace PairTemplateClass
{
    template<typename T = int, typename T2 = double> // T2 = T is also accepted
    class HoldsPair
    {
    private:
        T value1;
        T2 value2;

    public:
        HoldsPair(const T& newValue1, const T2& newValue2) : value1(newValue1), value2(newValue2) {}

        const T& GetValue1() const { return value1; }
        const T2& GetValue2() const { return value2; }
    };

    template<> class HoldsPair<int, int>
    {
    private:
        int value1;
        int value2;
        string strFun{};

    public:
        HoldsPair(const int& newValue1, const int& newValue2) : value1(newValue1), value2(newValue2) {}

        const int& GetValue1() const
        {
            cout << "Return value 1: " << value1 << endl;
            return value1;
        }
    };

}

namespace StaticTemplates
{
    template<typename T>
    class TestStatic
    {
    public:
        static T staticValue;
    };

    //static member initialization
    template<typename T> T TestStatic<T>::staticValue;
}

template<typename Res, typename ValType>
void Sum(Res& result, ValType& value)
{
    result = result + value;
}

// Variadic template, no set limit of arguments!
template<typename Res, typename First, typename... Rest>
void Sum(Res& result, First value, Rest... valueN)
{
    result = result + value;
    return Sum(result, valueN...);
}

template<typename TupleType>
void DisplayTupleInfo(TupleType& tup)
{
    const int numMembers = std::tuple_size<TupleType>::value;
    cout << "Number of elements in tuple: " << numMembers << endl;
    cout << "Last element of tuple: " << std::get<numMembers - 1>(tup) << endl;
}

namespace StaticAssertTemplate
{
    template<typename T>
    class OnlyInt
    {
    public:
        OnlyInt()
        {
            static_assert(std::is_integral<T>::value, "Only integral type passed");
            //static_assert(std::is_integral_v<T>, "Only integral type passed"); // Shorter form, same check
        }
    };
}

int main()
{
    // An introduction to templates
    {
        /*
         * - Templates are one of the most powerful features of C++.
         * - They enable us to define a behaviour that we can apply to objects of varying types while being type safe.
         *
         * - Templates are declared in the following way:
         *  - First add the template keyword
         *  - Follow it by a type parameter list
         *
         *  template<parameter list>
         *  method or class declaration
         *
         * - The keyword template marks the start of a template declaration, and the template parameter list contains
         *   the keyword typename, which defines the template parameter objType, making it a placeholder for the type of
         *   the object that the template is being instantiated for.
         *
         *   template<typename T1, typename T2 = T1>
         *   bool TemplateFunction(const T1& param1, const T2& param2);
         *
         *   template<typename T1, typename T2 = T1>
         *   class MyTemplate
         *   {
         *   private:
         *      T1 member1;
         *      T2 member2;
         *   public:
         *      T1 GetMember1() const { return member1; }
         *   }
         *
         * - What you see here: template<typename T1, typename T2 = T1> is the declaration of a template that takes two
         *   template parameters, T1 and T2, where T2 is given the default type of T1.
         */
    }

    // Different types of template declaration
    {
        /*
         * - A template declaration can be:
         *  - A declaration or definition of a method.
         *  - A declaration or definition of a class.
         *  - A definition of a member method or a member class of a class template (T).
         *  - A definition of a static data member of a class template.
         *  - A definition of a static data member of a class nested within a class template.
         *  - A definition of a member template of a class or class template.
         */
    }

    // Template functions/methods
    {
        /*
         * - By using template syntax, we can declare methods that adapt themselves to a variety of argument types,
         *   no longer having to declare multiple overloaded methods for the same operation.
         *
         *   template<typename objType>
         *   const objType& GetMax(const objType& value1, const objType& value2)
         *   {
         *      if(value1 > value2) return value1;
         *
         *      return value2;
         *   }
         */

        cout << "Template method implementation!" << endl;

        int num1 = 10;
        int num2 = 20;
        double double1 = 30.3;
        double double2 = 45.132;

        int maxValue = GetMax<int>(num1, num2);
        double maxValue2 = GetMax<double>(double1, double2);

        /*
         * - As you can see with the example above, we can use the template method we declared above to get the max
         *   number between integers and doubles. We did not have to overload the same function so that it would work
         *   with the two types.
         * - Notice the <int> and <double> being used to call the method? They effectively define the template's
         *   parameter objType as int and double on their respective invocation.
         *
         * - However, template methods don't necessarily need an accompanying type specifier, so invoking this statement
         *   int max = GetMax(num1, num2) is perfectly valid!
         * - Compilers nowadays are smart enough to understand that the template method is being invoked for the integer
         *   type.
         * - However with classes, you need to explicitly specify the type!
         */

        int num3 = -101, num4 = 2014;
        string name1{"Jack"}, name2{"John"};

        DisplayComparison(num3, num4);
        DisplayComparison(double1, double2);
        DisplayComparison(num3, num4);
        DisplayComparison(name1, name2);

        /*
         * - This example takes things further by declaring a second template method and passing along varying types.
         * - As you can see, the <typename Type> specifier is not needed when calling the methods because the compiler
         *   is able to infer it automatically when working with primitive types.
         * - You can add the type specifier if you want to communicate more explicitly what you are sending to your
         *   method, but it's not a requirement.
         *   - DisplayComparison<string>(name1, name2); is a valid statement.
         *
         * - As mentioned before, templates are type safe so attempting to make calls like this one:
         *  - DisplayComparison(int, string)
         *  - Will cause the program to fail compilation, preventing your application from encountering unexpected
         *    behaviours that could easily be introduced with macros.
         */

        cout << "\n\n" << endl;
    }

    // Template classes
    {
        /*
         * - Template classes are templatized versions of C++ classes; they are blueprints of blueprints.
         * - When using a template class, you are given the option to specify the "type" you are specialising the class
         *   for. This enables you to create classes with templatized parameters where in some instances it will be an
         *   integer, in others a double, and so on.
         *
         * - A simple template class can be defined as follows:
         *   template<typename T>
         *   class HoldVarTypeT
         *   {
         *   private:
         *    T value; // The type of variable value is T, and T is resolved at the time the template is instantiated.
         *   public:
         *    void SetValue(const T& newValue) { value = newValue; }
         *    const T& GetValue() const { return value; }
         *   };
         */

        cout << "Template class implementation!" << endl;

        BasicTemplateClass::HoldVarTypeT<int> holdInt{};
        holdInt.SetValue(10);
        cout << "The value stored is: " <<holdInt.GetValue() << endl;

        BasicTemplateClass::HoldVarTypeT<string> holdString{};
        holdString.SetValue("John");
        cout << "The value stored is: " << holdString.GetValue() << endl;

        /*
         * - As you can see, with the template class implementation, we can store different types in the same class
         *   and use all the methods and members regardless of the type specifier that we give to the template.
         * - This helps to define a pattern for classes and helps implement that exact same pattern on different data
         *   types that our class might need to operate with for a variety of reasons.
         *
         * - Template classes can also be instantiated with types other than primitive types or the Standard Template
         *   Library. We can instantiate a template using custom types that we declare. Just like the example below.
         */

        BasicTemplateClass::HoldVarTypeT<BasicTemplateClass::Human> holdHuman{};
        BasicTemplateClass::Human human{"John", 24};
        holdHuman.SetValue(human);
        holdHuman.GetValue().IntroduceSelf();

        cout << "\n" << endl;
    }

    // Declaring templates with multiple parameters
    {
        /*
         * - You can expand the template parameter list to declare multiple parameters, separated by commas.
         * - This allows you to declare generic classes that can hold a pair of object that can be of different types.
         */

        PairTemplateClass::HoldsPair<int, double> pairClass(6, 1.99);
        PairTemplateClass::HoldsPair<int, int> pairClass2(6, 500);
    }

    // Declaring templates with default parameters
    {
        /*
         * - Just as with methods, we can declare a type as the default template parameter type by using: T = type
         * - This helps to compact template syntax declaration when using the default type. As you can see with the
         *   example below, we no longer provide a type specifier because the template supports a default type.
         * - Also note that because we are providing the template primitive types, the compiler can easily set the type
         *   of the class even when using different types to the ones set as default!
         *
         * - Templates are a great way to increase code reusability.
         */

        PairTemplateClass::HoldsPair<> defaultPairClass(6, 500.54); // Using default types!
        PairTemplateClass::HoldsPair<short, const char*> defaultPairClass2(50, "C++ templates are OP!");

        cout << "The first object contains:" << endl;
        cout << "Value 1: " << defaultPairClass.GetValue1() << endl;
        cout << "Value 2: " << defaultPairClass.GetValue2() << endl;

        cout << "The second object contains:" << endl;
        cout << "Value 1: " << defaultPairClass2.GetValue1() << endl;
        cout << "Value 2: " << defaultPairClass2.GetValue2() << endl;

        cout << "\n\n" << endl;
    }

    // Template instantiation and specialisation
    {
        /*
         * - As far as the compiler is concerned, a template class you define but don't consume is code that is simply
         *   ignored. Unless it is used in one way or another, the template doesn't truly exist for the compiler.
         * - You instantiate a template class when you supply template arguments <type>.
         *  - This statement instructs the compiler to create a class for you by using the template and to instantiate
         *    it for the types specified as template arguments.
         *  - Therefore, in templates, instantiation is the process of creating a specific type using one or more
         *    template arguments
         *
         * - On the other hand, there may be situations where you explicitly define a different behaviour of a template
         *   when instantiated with a specific type. In these cases, you specialise a template for that type.
         * - The syntax for this specialisation is as follows:
         *   template<> class HoldsPair<int,int>
         *
         * - Of course, code that specialises a template must follow the template definition.
         */

        cout << "Template specialisation implementation!" << endl;

        PairTemplateClass::HoldsPair<int,int> defaultPairClass(6, 500);
        auto result = defaultPairClass.GetValue1();

        /*
         * - In the example above, this template specialisation behaves completely different from the basic template
         *   implementation. The method does an extra action other than returning the value. the class also contains a
         *   new string member that is not found in the original one.
         * - Even if were to leave the methods of the base template empty, the program will still compile, and that is
         *   because the compiler is only concerned about instantiating the <int,int> specialisation of the template.
         *   It does not care about the base template, it's invisible code for it because there is nothing calling the
         *   base template.
         * - As you can see templates are powerful tools that based on the needs of our program can easily mutate to
         *   better fit our needs
         */

        cout << "\n\n" << endl;
    }

    // Template classes and static members
    {
        /*
         * - Static members of a template class, similarly to a regular class, are shared across all objects of the same
         *   class. However, in templates this changes a bit.
         * - The static member is still shared across all objects of the template class with the same template
         *   instantiation.
         * - What does this mean?
         *  - It means that a static member X of a template<int>, will be static with all instances of the class that
         *    were instantiated as <int>. If a template<double> is instantiated, it will not have access to the static
         *    member of the <int> class. It will have access however, to the static member of all <double> classes.
         *
         * - Take a look at the example below. On it, we can see that two instances of the same type of template are
         *   being created but the type specifiers are different (int and double). Both are making changes to the static
         *   member staticValue yet, when you analyze the output of the program, the values are different. This goes to
         *   prove that because the type specifier is different, each object is treated as its own separate entity even
         *   if coming from the same base.
         */

        cout << "Static members in templates implementation!" << endl;

        using namespace StaticTemplates;
        TestStatic<int> intInstance;
        cout << "Setting staticValue for intInstance to 2024" << endl;
        intInstance.staticValue = 2024;

        TestStatic<double> doubleInstance;
        cout << "Setting staticValue for doubleInstance to 3.1416" << endl;
        doubleInstance.staticValue = 3.1416;

        cout << "intInstance.staticValue = " << intInstance.staticValue << endl;
        cout << "doubleInstance.staticValue = " << doubleInstance.staticValue << endl;

        cout << "\n\n" << endl;
    }

    // Variable templates
    {
        /*
         * - Since C++14, the use of variadic templates, also called variable templates has been supported.
         * - They are helpful in writing methods/classes that can accept multiple arguments without a set limit.
         *
         * - If we analyze the example and variable template at the top, we can see that they cannot only process a
         *   wide variety of types, but they can also process a varying number of arguments.
         * - During compilation time, the compiler actually creates code for the right kind of sum to suit the call,
         *   and it does so recursively until all arguments have been processed!
         *
         * - The ellipsis that is being used at the variable template declaration tells the compiler that the template
         *   class or method may accept an arbitrary number of template arguments of any type.
         *
         * - Variadic templates help to save a lot of time when programming tedious mathematical operations and also
         *   make the maintenance of the code base easier.
         *
         * - You can use the operator sizeof...(), NOTICE THE ELLIPSIS!, to determine the number of template arguments
         *   passed in a call to a variadic template.
         *   - int array[sizeof...(Rest)] -> This will allocate an array that has space for all the template arguments.
         *
         * - The support of variadic templates has also ushered in standard support for tuples.
         *  - Tuples can be instantiated with a varying number of member elements and types.
         *  - These may be individually accessed using the STL function std::get().
         */

        cout << "Variable templates implementation!" << endl;

        double result = 0;
        Sum(result, 3.14, 4.56, 1.1111);
        cout << "result = " << result << endl;

        string strResult;
        Sum(strResult, "Hello", "World");
        cout << "strResult = " << strResult << endl;

        cout << "\n\n" << endl;

        cout << "Tuple access with variadic templates implementation" << endl;
        tuple<int, char, string> tup1(std::make_tuple(101, 'J', "Hello Tuple"));
        DisplayTupleInfo(tup1);

        auto tup2(std::make_tuple(3.14, false));
        DisplayTupleInfo(tup2);

        auto concatTup(std::tuple_cat(tup2, tup1));
        DisplayTupleInfo(concatTup);

        double pi;
        string sentence;
        std::tie(pi, std::ignore, std::ignore, std::ignore, sentence) = concatTup;
        cout << "Unpacked! Pi: " << pi << " and \"" << sentence << "\"" << endl;

        /*
         * - Tuples are used to hold a collection of elements of different types, where required.
         * - The example demonstrates the reach of templates. Tuples are being instantiated by directly providing type
         *   specifiers and by letting the compiler type deduct. We programmed a template function that provides a tuple
         *   , and it automatically figures the type and performs the appropriate logic to it. We also use std::tie to
         *   map values of the tuple to variables of our choice that get type deducted inside the function.
         *
         * - As you can see, templates are extremely powerful and allow for incredibly complex systems to be put in
         *   place.
         */

        cout << "\n\n" << endl;
    }

    // Using static_assert to perform compile time checks
    {
        /*
         * - Introduced in C++11, static_asserts block compilation if a supplied condition is not fulfilled.
         * - It is a compile-time assert that can display custom messages on your IDE or console.
         * - static_assert(expression being evaluated, "Error message that shows up if failed to evaluate")
         *
         * - This feature is really helpful with template classes!
         * - For example, you might want to ensure your template class can only be instantiated for integer types. You
         *   can use the assert like this:
         *   - static_assert(std::is_integral<T>::value, "Only integers!");
         *   - std::is_integral check whether the supplied template parameter is an integer type.
         */

        StaticAssertTemplate::OnlyInt<int> test1;
        //StaticAssertTemplate::OnlyInt<double> test2; // Error! Fails to compile
    }

    // Final thoughts
    {
        /*
         * - Knowing how templates work will help a great deal when dealing with STL libraries for data structures and
         *   algorithms, as they all implement templates for their with C++ types and your custom types.
         *
         * - Use templates for the implementation of generic concepts
         * - Chose templates over macros!
         * - Don't forget to use proper const correctness to avoid bugs or unwanted access to the objects.
         */
    }

    return 0;
}