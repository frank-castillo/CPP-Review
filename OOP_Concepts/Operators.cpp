//
// Created by juanf on 2024-08-27.
//

#include <iostream>
#include <string>
#include <sstream> // New include that implement ostringstream that is used by cout
#include <memory>
#include <random>

using std::cout, std::endl, std::string;

namespace DateClass
{
    class Date
    {
    private:
        int year, month, day;
        string dateInString;

    public:
        Date(const int month, const int day, const int year) : year(year), month(month), day(day) {}

        Date& operator++()
        {
            ++day;
            return *this;
        }

        Date& operator--()
        {
            --day;
            return *this;
        }

        Date operator++(int) // postfix increment
        {
            Date temp(month, day,year);
            ++day;
            return temp;
        }

        Date operator--(int) // postfix decrement
        {
            Date temp(month, day,year);
            --day;
            return temp;
        }

        explicit operator const char*()
        {
            std::ostringstream formattedDate; // Assists during construction
            formattedDate << year << "/" << month << "/" << day; //ostringstream helps in converting primitives to str
            dateInString = formattedDate.str();
            // Stored in member variable because the variable would be destroyed before the compiler returns the value
            // to the place that invokes the operator.
            return dateInString.c_str();
        }

        // Binary operators
        Date operator+(int daysToAdd) // Binary addition
        {
            Date temp(month, day + daysToAdd, year);
            return temp;
        }

        Date operator-(int daysToSub) // Binary subtraction
        {
            Date temp(month, day - daysToSub, year);
            return temp;
        }

        void operator+=(int daysToAdd)
        {
            day += daysToAdd;
        }

        void operator-=(int daysToSub)
        {
            day -= daysToSub;
        }

        bool operator==(const Date& compareTo) const
        {
            return ((year == compareTo.year) && (month == compareTo.month) && (day == compareTo.day));
        }

        bool operator!=(const Date& compareTo) const
        {
            return !this->operator==(compareTo); // Inverse of the result of the equality operator
        }

        // Conditional checking
        bool operator<(const Date& compareTo) const
        {
            if (year < compareTo.year)
            {
                return true;
            }
            else if (year == compareTo.year && month < compareTo.month )
            {
                return true;
            }
            else if (year == compareTo.year && month == compareTo.month && day < compareTo.day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool operator<=(const Date& compareTo) const
        {
            if(this->operator==(compareTo))
            {
                return true;
            }

            return this->operator<(compareTo);
        }

        bool operator>(const Date& compareTo) const
        {
            return !this->operator<=(compareTo);
        }

        bool operator>=(const Date& compareTo) const
        {
            if(this->operator==(compareTo))
            {
                return true;
            }

            return this->operator>(compareTo);
        }

        auto operator<=>(const Date& compareTo) const
        {
            if(year < compareTo.year)
            {
                return std::strong_ordering::less;
            }
            else if(year > compareTo.year)
            {
                return std::strong_ordering::greater;
            }
            else
            {
                // Years are identical. Compare months
                if (month < compareTo.month)
                {
                    return std::strong_ordering::less;
                }
                else if (month > compareTo.month)
                {
                    return std::strong_ordering::greater;
                }
                else
                {
                    // Months are identical. Compare days
                    if (day < compareTo.day)
                    {
                        return std::strong_ordering::less;
                    }
                    else if (day > compareTo.day)
                    {
                        return std::strong_ordering::greater;
                    }
                    else
                    {
                        return std::strong_ordering::equal;
                    }
                }
            }
        }

        void DisplayDate() const
        {
            std::cout << year << "/" << month << "/" << day << std::endl;
        }
    };
}

namespace BufferClass
{
    class MyBuffer
    {
    private:
        int* mNumbers = nullptr;
        unsigned int mSize;

    public:
        explicit MyBuffer(const unsigned int length) : mSize(length)
        {
            mNumbers = new int[mSize]; // Allocate memory

            cout << "Constructing new instance with: " << mSize << " elements." << std::endl;
        }

        virtual ~MyBuffer()
        {
            cout << "Destructor called!" << endl;
            delete[] mNumbers; // Free allocated memory
        }

        MyBuffer(const MyBuffer& rhs)
        {
            cout << "Copy constructor called!" << endl;
            if (this != &rhs)
            {
                if(mNumbers != nullptr)
                {
                    delete[] mNumbers;
                }

                mSize = rhs.mSize;
                mNumbers = new int[mSize];
                std::copy(rhs.mNumbers, rhs.mNumbers + mSize, this->mNumbers);
            }
        }

        MyBuffer(MyBuffer&& rhs) noexcept
        {
            cout << "Move constructor called!" << endl;
            if (this != &rhs)
            {
                mSize = rhs.mSize;
                mNumbers = rhs.mNumbers; // We take ownership of the memory pointer! No copy, we just take it

                // Clear source resources after moving them to avoid any issues
                rhs.mSize = 0;
                rhs.mNumbers = nullptr;
            }
        }

        MyBuffer& operator=(const MyBuffer& rhs)
        {
            if (this != &rhs)
            {
                cout << "Copy assignment operator" << endl;

                if(mNumbers)
                {
                    delete[] mNumbers;
                }

                mSize = rhs.mSize;
                mNumbers = new int[mSize];
                std::copy(rhs.mNumbers, rhs.mNumbers + mSize, this->mNumbers);
            }

            return *this;
        }

        MyBuffer& operator=(MyBuffer&& rhs) noexcept
        {
            cout << "Move assignment operator" << endl;
            if (this != &rhs && rhs.mNumbers != nullptr) // Ensure it's not ourselves and something can be moved!
            {
                delete[] mNumbers;
                mSize = rhs.mSize;
                mNumbers = rhs.mNumbers;

                // Clear source resources after moving them to avoid any issues
                rhs.mSize = 0;
                rhs.mNumbers = nullptr;
            }

            return *this;
        }

        MyBuffer operator+(const MyBuffer& rhsToAppend)
        {
            cout << "Operator+: concatenation of buffers" << endl;
            MyBuffer temp(this->mSize + rhsToAppend.mSize); // New combined length

            for (int i = 0; i < this->mSize; ++i)
            {
                temp[i] = this->mNumbers[i];
            }

            for (int i = 0; i < rhsToAppend.mSize; ++i)
            {
                temp[i + this->mSize] = rhsToAppend.mNumbers[i];
            }

            return temp;
        }

        int& operator[](const unsigned int index)
        {
            return mNumbers[index];
        }

        const int& operator[](const unsigned int index) const
        {
            return mNumbers[index];
        }

        void SetValue(const unsigned int index, const int value)
        {
            if(index < mSize)
            {
                *(mNumbers + index) = value; // + will move pointer forward by n index
            }
        }

        void DisplayBuffer() const
        {
            for(unsigned int i = 0; i < mSize; ++i)
            {
                cout << *(mNumbers + i) << " ";
            }

            cout << endl;
        }
    };
}

namespace Literals
{
    struct Temperature
    {
        double Kelvin;
        explicit Temperature(long double Kelvin) : Kelvin(Kelvin) {}
    };

    Temperature operator""_C(long double celsius)
    {
        return Temperature(celsius + 273);
    }

    Temperature operator""_F(long double fahrenheit)
    {
        return Temperature((fahrenheit + 459.67) * 5 / 9);
    }
}

int main()
{
    // Operator Overloading: An introduction
    /*
     * - In addition to member variables and methods, classes can also encapsulate operators that make it easy to
     *   operate on instances of the class.
     * - Just as with methods, operators can be overloaded in a multitude of ways, allowing you to perform operations
     *   such as assignment or object addition in objects of the same class.
     *
     * - The syntax to declare an operator overloading is as follows:
     *  - return_type operator operator_symbol(parameter list){}
     *  - The operator_symbol can be any of the several operator types that we can define as programmers.
     *
     * - Looking at it that way, an operator overloading looks exactly the same as a method overload. The question
     *   then is, why would we go out of our way to implement an operator overload when we can achieve the same through
     *   methods?
     * - The answer lies in implementation intuitiveness and application performance.
     *
     * - Imagine this case scenario: You have a class that manages dates. Whenever you want to increase the date by a
     *   day, you can implement two options:
     *   - ++date;
     *   - date.IncrementByOne();
     *  - Which one looks like the fastest and most intuitive implementation? The answer is the increment operator
     *    (++). Superfast to code, easy to understand, and, in bigger applications, it does not generate function
     *    overhead as the operator overload functions as a static polymorphism and gets processed as an innate compiler
     *    operation.
     *
     * - Taking time to properly overload and implement relevant operators in your class, comes with great ease of
     *   consumption for your class, as many complex operations are reduced to a single symbol.
     *
     * - The ultimate goal of operator overloading is making classes easier and more intuitive to use. However, not all
     *   operators should be overloaded! Make sure you only overload those that fit the requirements and needs of your
     *   class.
     */

    // Types of operators
    {
        /*
        * - In C++, we have two types of operators:
        *  - Unary operators.
        *  - Binary operators.
        */

        // Unary Operators
        {
            /*
             * - Unary operators only function on a single operand.
             * - They can be declared as either:
             *  - Global namespace operators.
             *  - Static member functions of a class.
             *  - Non-static class members.
             *
             * - Global namespace and static member operator overloads are declared as follows:
             *  - return_type operator operator_type(parameter_type) {}
             *  - Notice that the operator argument list only accepts a single parameter, hence the name, UNARY.
             *
             * - Non-static class members operator overloads are declares as follows:
             *  - return_type operator operator_type() {}
             *  - Notice how in this case there is no argument list. This is because the single parameter that it works
             *    on is the instance of the class itself via the "this" reference pointer.
             *
             * - The following list represents all the unary operators that can be overloaded/redefined:
             *  - ++ Increment operator
             *  - -- Decrement operator
             *  - * Pointer dereference operator
             *  - -> Member selection operator
             *  - ! Logical NOT operator
             *  - & Address-of operator
             *  - ~ One's complement operator
             *  - + Unary plus operator
             *  - - Unary negation operator
             *  - Conversion Operators -> special cases
             */

            // ++ and -- operators
            {
                /*
                 * - Dependent on the type of increment you want to perform, the syntax changes.
                 *
                 * - In order to perform a prefix increment or decrement, follow this syntax:
                 *  - ClassType& operator++() { //Perform other logic; return *this; }
                 *
                 * - To perform a postfix increment/decrement, follow this syntax:
                 *  - ClassType operator++(int)
                 *    {
                 *      // Perform a copy of the current state of the object, before any calculations are done
                 *      Type Copy(*this);
                 *
                 *      // Increment code operating on "this"
                 *
                 *      // Return state before increment(because, postfix)
                 *      return copy;
                 *    }
                 *
                 * - Postfix creates a temp copy that ends up being discarded. If all you want to do is increase a value
                 *   by another amount, you are better off just using the prefix operator.
                 */

                cout << "Implementing ++ and -- operator overloading! " << endl;

                DateClass::Date date(8, 27, 2024);

                cout << "Date is: ";
                date.DisplayDate();

                ++date;
                cout << "After using ++date. Date is: ";
                date.DisplayDate();

                --date;
                cout << "After using --date. Date is: ";
                date.DisplayDate();

                date++;
                cout << "After using date++. Date is: ";
                date.DisplayDate();

                date--;
                cout << "After using date--. Date is: ";
                date.DisplayDate();

                cout << "\n\n" << endl;
            }

            // Conversion operators
            {
                /*
                 * - Conversion operators are a great tool to easily convert the contents of your class into other
                 *   types that can be used by the compiler to interact with other operators.
                 *
                 * - Do note that these conversions may cause implicit conversions. That is, the compiler uses the
                 *   available conversion operator, thereby permitting unintended assignments that can be compiled
                 *   without errors.
                 *   - To avoid implicit conversions, use explicit at the beginning of a conversion operator.
                 *   - By using explicit, we are now forced to assert the intention to convert using CASTS.
                 *
                 * - A good practice to follow is to program as many operators as you think your class would be used
                 *   with. This will extend the usability of your class and improve the readability of your code.
                 *
                 * - Let's take a look at this with the following code example:
                 */

                cout << "Conversion operator implementation!" << endl;

                class AClass{};
                AClass a;

                //cout << a << endl;
                // This line fails to compile as there is no innate conversion from your class to send to cout.
                // cout accepts primitive types or types of ostream, yet your class does not support that.

                // Now take a look at the Date class, with an overloaded const char* operator marked as explicit
                DateClass::Date testDate(8, 27, 2024);

                cout << "The date is: " << static_cast<const char*>(testDate) << endl;
                string newString = static_cast<const char*>(testDate);
                string newString2(static_cast<const char*>(DateClass::Date(8,27,2024)));

                cout << "String 01 is : " << newString << endl;
                cout << "String 02 is : " << newString2 << endl;

                cout << "\n\n" << endl;

                /*
                 * - By implementing a const char*() operator, we are able to convert the information contained in the
                 *   class to a string. This string in turn is a compatible with the cout << stream, allowing us to
                 *   directly print data from the class without the need of a function.
                 *
                 * - In this particular case, in order to prevent implicit conversions unless required, we marked the
                 *   operator as explicit. This forces us to explicitly state the conversion via the static_cast,
                 *   promoting code safety and programmer intention.
                 *
                 * - The operator will also allow us to assign the char* to a string directly, either through an
                 *   assignment operation, or as the parameter of the string constructor.
                 */

            }

            // Dereference operator and member selection operator
            {
                /*
                 * - These 2 operators are more wildly used in the programming of smart pointer classes.
                 *  - Smart pointers are an advanced solution that solves many of the issues regarding memory
                 *    management, ownership problems, and copy issues using operators.
                 *
                 * - For this case scenario, in order to properly show how the implementation of these 2 pointers works
                 *   on manipulating smart pointers we'll jump ahead a bit. Smart pointers has its own file.
                 *
                 * - Overloading these two operators is more common in smart pointer classes. The code below is just
                 *   a demonstration on how the operators function.
                 */

                cout << "Dereference and member selection pointers implementation!" << endl;

                std::unique_ptr<int> smartPointer(new int);
                *smartPointer = 10; // Use of dereference operator in order to manipulate the value of the data to which
                                    // the smart pointer points to.

                cout << "Integer value contained in pointer: " << *smartPointer << endl; // Dereference to access data
                cout << "Integer smart pointer address: " << smartPointer << endl;

                std::unique_ptr<DateClass::Date> smartDate(new DateClass::Date(8,27,2024));
                cout << "The date is: " << static_cast<const char*>(*smartDate) << endl; // Dereference == value

                cout << "The data can also be accessed with ->: ";
                smartDate->DisplayDate(); // Use of member selection to access the method of an object via a pointer

                cout << "\n\n" << endl;
            }
        }

        // Binary Operators
        {
            /*
             * - Binary operators can operate on two operands at the same time.
             * - They can be declared as either:
             *  - Global functions.
             *  - Static member method.
             *  - Class member
             *
             * - Global namespace and static member operator overloads are declared as follows:
             *  - return_type operator_type(parameter1, parameter2)
             *
             * - Non-static class members operator overloads are declares as follows:
             *  - return_type operator_type(parameter)
             *  - Notice how the clas member only accepts one parameter? This is because the member class overload's
             *    second parameter is usually derived from the attributes of the class itself.
             *
             * - The following list represents all the unary operators that can be overloaded/redefined:
             *  - ,   Comma
             *  - !=  Inequality
             *  - %   Modulus
             *  - %=  Modulus Assignment
             *  - &   Bitwise And
             *  - &&  Logical And
             *  - &=  Bitwise And Assignment
             *  - *   Multiplication
             *  - *=  Multiplication Assignment
             *  - +   Addition
             *  - +=  Addition Assignment
             *  - -   Subtraction
             *  - -=  Subtraction Assignment
             *  - ->* Pointer to Member Selection
             *  - /   Division
             *  - /=  Division Assignment
             *  - <   Less Than
             *  - <<  Left Shift
             *  - <<= Left Shift Assignment
             *  - <=  Less Than or Equal
             *  - =   Assignment, Copy Assignment, and Move Assignment
             *  - ==  Equality
             *  - >   Greater Than
             *  - >=  Greater Than or Equal
             *  - >>  Right Shift
             *  - >>= Right Shift Assignment
             *  - ^   Exclusive OR
             *  - ^=  Exclusive OR Assignment
             *  - |   Bitwise Inclusive OR
             *  - |=  Bitwise Inclusive OR Assignment
             *  - ||  Logical OR
             *  - []  Subscript
             */

            // Binary addition and subtraction operators (+ , -)
            {
                /*
                 * - When defined, these operators allow us to add or subtract the value of a supported data type from
                 *   an object of the class that implements these operators.
                 *
                 * - These operators are also helpful when working in classes that manage dynamically allocated memory.
                 *   - A perfect example would be the concatenation of buffers. By overloading this operator, it is
                 *    possible to combine two buffers into a single one and return the new buffer to a new variable.
                 */

                cout << "Binary + and - implementation!" << endl;

                DateClass::Date date(8, 27, 2024);
                cout << "The date is: " << static_cast<const char*>(date) << endl;

                cout << "Day of final exam: " << static_cast<const char*>(date - 10) << endl;

                cout << "Last day of the month: " << static_cast<const char*>(date + 4) << endl;

                cout << "\n\n" << endl;
            }

            // Addition and subtraction assignment (+= , -=)
            {
                /*
                 * - These operators allow us to modify the value of an object a by an amount b.
                 * - In the case of these operators, it is possible to overload them to accept a different type of
                 *   parameter as b.
                 * - These operators declarations can also be overloaded, allowing you to pass other types or your
                 *   own custom types == void operator+=(const Date& daysToAdd).
                 */

                cout << "Binary += and -= implementation!" << endl;

                DateClass::Date date(8, 27, 2024);
                cout << "The date is: " << static_cast<const char*>(date) << endl;

                date += 4;
                cout << "Last day of the month == date += 4: " << static_cast<const char*>(date) << endl;

                date -= 4;
                date -= 10;
                cout << "Day of final exam == date -= 10: " << static_cast<const char*>(date) << endl;

                cout << "\n\n" << endl;
            }

            /*
             * - Other operators such as:
             *  - Multiplication assignment
             *  - Division assignment
             *  - Modulus assignment
             *  - Left and Right Shift assignment
             *  - XOR assignment
             *  - Bitwise inclusive OR assignment
             *  - Bitwise AND assignment
             * - All share the same syntax as += and -= operators. They also have the capability to be overloaded.
             */

            // Equality and inequality operators (== , !=)
            {
                /*
                 * - When comparing instances of a class, if no overloaded equality or inequality operators have been
                 *   overloaded, the compiler defaults to performing a binary comparison and returns true if the objects
                 *   are exactly identical.
                 * - The binary comparison will work for instances of classes containing simple data types, but it won't
                 *   work if the class has non-static pointer members (e.g. int*). In these cases, the evaluation will
                 *   mostly return false because when comparing the member pointer's value against the other, they will
                 *   never be equal.
                 * - In order to solve this, we need to implement "comparison operators".
                 *  - bool operator==(const ClassType& compareTo), return true if equal
                 *  - bool operator!=(const ClassType& compareTo), return true if unequal
                 *
                 * - The inequality operator can be the inverse (logical NOT) of the result of the equality operator.
                 */

                cout << "Equality and Inequality implementation!" << endl;

                DateClass::Date date(8, 27, 2024);
                DateClass::Date date2(8, 27, 2024);
                DateClass::Date date3(8, 27, 2025);

                cout << "Date is: " << static_cast<const char*>(date) << endl;
                cout << "Date2 is: " << static_cast<const char*>(date2) << endl;
                cout << "Date3 is: " << static_cast<const char*>(date3) << endl;

                cout << "Comparing Date and Date2" << endl;

                if(date == date2)
                {
                    cout << "Equality operator. The date is the same." << endl;
                }
                else
                {
                    cout << "Equality operator. The date is not the same." << endl;
                }

                cout << "Comparing Date and Date3" << endl;

                if(date != date3)
                {
                    cout << "Inequality operator. The date is not the same." << endl;
                }
                else
                {
                    cout << "Inequality operator. The date is the same." << endl;
                }

                cout << "\n\n" << endl;
            }

            // Conditional checking through < , > , <= , >= operators
            {
                /*
                 * - Once a class is smart enough to evaluate the equality of its objects, we can implement
                 *   conditional checking.
                 */

                cout << "Conditional checking with operator overloading implementation!" << endl;

                DateClass::Date date(8, 27, 2024);
                DateClass::Date date2(8, 27, 2025);
                DateClass::Date date3(8, 24, 2024);
                DateClass::Date date4(8, 27, 2024);

                cout << "Date is: " << static_cast<const char*>(date) << endl;
                cout << "Date2 is: " << static_cast<const char*>(date2) << endl;
                cout << "Date3 is: " << static_cast<const char*>(date3) << endl;
                cout << "Date4 is: " << static_cast<const char*>(date4) << endl;

                cout << "Comparing Date and Date2" << endl;

                if(date < date2)
                {
                    cout << "Operator<: Date happened first" << endl;
                }

                cout << "Comparing Date2 and Date3" << endl;
                if(date2 > date3)
                {
                    cout << "Operator>: Date2 happened first" << endl;
                }

                cout << "Comparing Date and Date4" << endl;
                if(date <= date4)
                {
                    cout << "Operator<=: Same date or before Date4" << endl;
                }

                cout << "Comparing Date2 and Date4" << endl;
                if(date2 >= date4)
                {
                    cout << "Operator>=: Same date or after Date4" << endl;
                }

                cout << "\n\n" << endl;
            }

            // The spaceship operator (<=>)
            {
                /*
                 * - C++ 20 introduced the THREE WAY COMPARISON OPERATOR.
                 * - This operator simplifies the use of =, <, >, !=, <=, and >=.
                 *
                 * - This is the syntax:
                 *  - auto operator <=>(const Type& otherObject)
                 */

                cout << "Implementing <=> operator!" << endl;

                std::random_device rd; // Seed random number generator
                std::mt19937 gen(rd()); // Mersenne Twister engine
                std::uniform_int_distribution<> dayDist(1, 31);
                // Used to generate random integers within specified ranges

                int randDay1 = dayDist(gen);
                int randDay2 = dayDist(gen);

                DateClass::Date date(8, randDay1, 2024);
                DateClass::Date date2(8, randDay2, 2024);

                cout << "Date is: " << static_cast<const char*>(date) << endl;
                cout << "Date2 is: " << static_cast<const char*>(date2) << endl;

                auto result = date <=> date2;

                if(result < 0)
                {
                    cout << "Date1 occurs before Date2" << endl;
                }
                else if(result > 0)
                {
                    cout << "Date1 occurs after Date2" << endl;
                }
                else
                {
                    cout << "Same dates" << endl;
                }

                cout << "\n\n" << endl;
            }

            // The copy assignment operator
            {
                /*
                 * - There will be times when you want/need to assign the contents of one object instance into another.
                 *  - date2 = date
                 *
                 * - This assignment invokes the default copy assignment operator that the compiler has built into the
                 *   class when you don't implement one. As we saw before, classes that managed complex types or
                 *   dynamically allocated memory, the default copy-constructor is inadequate.
                 * - In order to ensure deep copies, we need to specify an accompanying copy assignment operator that
                 *   follows the same logic as the copy constructor.

             classType& operator=(const ClassType& copySource) { if(this != &copySource) { copy logic} return *this}

                 * - This code snippet: if(this != &copySource) protects against copying into itself
                 */

                cout << "Copy assignment operator implementation!" << endl;

                BufferClass::MyBuffer buffer(5);
                std::random_device rd; // Seed random number generator
                std::mt19937 gen(rd()); // Mersenne Twister engine
                std::uniform_int_distribution<> dayDist(1, 31);
                // Used to generate random integers within specified ranges

                for(unsigned int i = 0; i < 5; i++)
                {
                    buffer.SetValue(i, dayDist(gen));
                }

                cout << "Displaying original buffer: " << endl;
                buffer.DisplayBuffer();

                BufferClass::MyBuffer copyBuffer{1};

                cout << "Displaying copy buffer before copy assignment: " << endl;
                copyBuffer.DisplayBuffer();

                copyBuffer = buffer; // Copy assignment operator!

                cout << "Displaying copy buffer after copy assignment: " << endl;
                copyBuffer.DisplayBuffer();

                cout << "Displaying original buffer: " << endl;
                buffer.DisplayBuffer();
            }
            cout << "\n\n" << endl;

            // The subscript operator
            {
                /*
                 * - This is the operator that allows array-style access to a class. The typical syntax is as follows:
                 *  - return_type& operator[](subscript_type& subscript);
                 *
                 * - When creating classes that encapsulate a dynamic array of any kind, the subscript operator makes it
                 *   easy to access a specific index from the collection.
                 *
                 * - Add const to operator declaration to prevent changes from happening outside the class.
                 *
                 * - Const method/operator implementation will be needed in order for const variables to be declared!
                 *  - You can declare both versions of the method to support const instances and dynamic instances.
                 *  - Dynamic: int& operator[](const unsigned int index) - Allows for modifications.
                 *  - Static: const int& operator[](const unsigned int index) const - No modifications allowed
                 */

                cout << "Subscript operator implementation!" << endl;

                BufferClass::MyBuffer buffer(5);
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dayDist(1, 31);

                for(unsigned int i = 0; i < 5; i++)
                {
                    buffer.SetValue(i, dayDist(gen));
                }

                cout << "Displaying buffer through function: " << endl;
                buffer.DisplayBuffer();

                cout << "Displaying buffer values through subscript operator buffer[i]: " << endl;
                for(unsigned int i = 0; i < 5; i++)
                {
                    cout << buffer[i] << endl;
                }

                cout << "Modifying a value of the buffer through subscript operator: " << endl;
                buffer[3] =  dayDist(gen);

                buffer.DisplayBuffer();

                const BufferClass::MyBuffer copyBuffer(buffer);

                cout << "Displaying const copy buffer: " << endl;
                copyBuffer.DisplayBuffer();

                //copyBuffer[3] = 10; // This line prevents compilation because of the const correctness
                int value = copyBuffer[3]; // You can, however, extract the value and use it for other operations!
                cout << "Value extracted into another variable from copyBuffer: " <<value << endl;
            }
            cout << "\n\n" << endl;

            // The function operator ( () )
            {
                /*
                 * - The function operator makes objects behave like functions.
                 * - This operator is heavily used in the Standard Template Library and STL Algorithms.
                 * - This operator can be used to make decisions, and depending on the number of operands they work on,
                 *   they can be unary or binary. We call this concept, unary predicate or binary predicate.
                 *
                 * - The compiler in this case allows the object to function as a function object, also called a
                 *   functor. More on this in the FunctionObjects.cpp
                 */

                cout << "Operator () implementation" << endl;

                class Display
                {
                public:
                    void operator()(const string& inputString) const
                    {
                        cout << inputString << endl;
                    }
                };

                Display display;
                display("Hello World!"); // Equivalent to display.operator("Hello World")

                cout << "\n\n" << endl;
            }

            // Move constructor and move assignment operator for High Performance Coding
            {
                /*
                 * - Performance optimization features that became part of the C++ standard in C++11.
                 * - They ensure that temporary values (rvalues that do not exist beyond the invoking statement) are not
                 *   wastefully copied.
                 * - This is incredibly useful when dealing with objects of class that manage dynamically allocated
                 *   resources.
                 *
                 * - Let's analyze our Date class, declared at the top of this file.
                 * - The addition operator creates a copy of the Date argument. This copy is then modified and finally
                 *   its sent back as the return of the function. If we were to implement that same operator in our
                 *   Buffer class, that concatenates the data of one buffer to the other we would end up with a long
                 *   process of copies...
                 *   - Buffer1{5}
                 *   - Buffer2{5}
                 *   - Buffer3(Buffer1 + Buffer2) -> operator+, copy constructor called
                 *   - BufferTotal()
                 *   - BufferTotal = Buffer1 + Buffer2 + Buffer3 -> operator+, copy constructors, copy assigment op.
                 *
                 * - As you can see, the process ends up generating multiple short-lived copies, that need to allocate
                 *   memory, copy the values, modify the values, add new values, etc. All this will occupy many more
                 *   resources and thus affect the performance of our program.
                 * - Hence why the move constructor and move assignment operator were added to the standard. They help
                 *   avoid the multiple internal copy process, enhancing the performance of the copy and assignment
                 *   steps.
                 *
                 * - The declaration is as follows, do note the &&:
                 * - Constructor
                 *  Class(Class&& moveSource)
                 *  {
                 *      dynamicResourceN = moveSource.dynamicResourceN; We take ownership of the resource and move it
                 *      moveSource.dynamicResourceN = nullptr;
                 *  }
                 * - Operator
                 *  Class& operator=(Class&& moveSource)
                 *  {
                 *      delete/delete[] dynamicResourceN; Free owning resource
                 *      dynamicResourceN = moveSource.dynamicResourceN; We take ownership of the resource and move it
                 *      moveSource.dynamicResourceN = nullptr;
                 *  }
                 *
                 *  \^o^/ Where N represents any number of dynamic resources (Most commonly pointers)
                 *
                 * - For this particular constructor and operator, the arguments cannot be made const as they have to be
                 *   modified. So if they were to be const, no modification would be possible, and we will run into
                 *   issues.
                 *
                 * - In standard-compliant compilers, it will be ensured that for rvalues temporaries, the move operator
                 *   and constructor are used. This way, instead of creating a whole new copy, you are simply moving
                 *   resources around, eliminating the need of extra steps.
                 */

                cout << "Move constructor and move assignment operator implementation!" << endl;

                BufferClass::MyBuffer buffer(5);
                BufferClass::MyBuffer buffer2(15);

                cout << "Concatenate buffers with operator+ overload!" << endl;
                BufferClass::MyBuffer buffer3(buffer + buffer2);
                BufferClass::MyBuffer buffSum(1);

                cout << "Concatenate buffers with assignment operator!" << endl;
                buffSum = buffer + buffer2 + buffer3;

                /*
                 * - Depending on the compiler you are using, the output message will be different. For this instance,
                 *   the project has been built with g++. So this is the output:
                 *   - Constructing new instance with: 5 elements.
                 *   - Constructing new instance with: 15 elements.
                 *   - Concatenate buffers with operator+ overload!
                 *   - Operator+: concatenation of buffers
                 *   - Constructing new instance with: 20 elements.
                 *   - Constructing new instance with: 1 elements.
                 *   - Concatenate buffers with assignment operator!
                 *   - Operator+: concatenation of buffers
                 *   - Constructing new instance with: 20 elements.
                 *   - Operator+: concatenation of buffers
                 *   - Constructing new instance with: 40 elements.
                 *   - Move assignment operator -> Move assignment operator was called!
                 *
                 * - The compiler does not automatically generate move constructors and move assignment operators.
                 *   You always have to provide them yourself! In case they are not implemented, the compiler will
                 *   revert to the copy constructor/assignment operator and create deep copies.
                 *
                 * - Although move constructors and operators are not required for the proper behaviour of a class,
                 *   adding them helps to improve the performance of your code when dealing with dynamic resources that
                 *   don't always require a full copy.
                 */
            }
            cout << "\n\n" << endl;

            // User-defined literals
            {
                /*
                 * - Ever since C++11, the C standard has included features that enable you to define your own literals.
                 * - To define your own literal, you define the ("") operator as follows:
                 *  - ReturnType operator"" YourLiteral(ValueType value)
                 *    {
                 *      Conversion code here
                 *    }
                 *
                 *  - For the ValueType in literals, things work a little different. Depending on the nature of the
                 *    user-defined literal, the argument of the literal will be restricted to one of the following:
                 *    - unsigned long long for integral literal.
                 *    - long double for floating-point literal.
                 *    - char, wchar_t, char16_t, or char32_t for character literal.
                 *    - const char* for raw string literal.
                 *    - const char* together with size_t for string literal.
                 *    - const wchar_t* together with size_t for string literal.
                 *    - const char16_t together with size_t for string literal.
                 *    - const char32_t together with size_t for string literal.
                 *
                 * - Now, for what is this useful? In really specific use cases, it can make your code/application a lot
                 *   simpler to read and maintain.
                 * - Imagine you are working on a scientific application and all your calculations will be based off the
                 *   Kelvin scale. With that being the case, you can declare all your temperatures as follows:
                 *   - Temperature k1 = 32.15_F, k2 = 0.0_C
                 *   - Notice the _F and the _C? These are literals that you can define in order to make your code more
                 *     readable. For this case, they represent Celsius and Fahrenheit, but depending on your application
                 *     you will declare literals that better fit your requirements.
                 */

                cout << "Literals implementation!" << endl;

                using namespace Literals; // So that we can use the operator overloads

                Temperature k1 = 31.73_F;
                Temperature k2 = 0.0_C;

                cout << "k1 = 31.73_F is: " << k1.Kelvin << endl;
                cout << "k2 = 0.0_C is: " << k2.Kelvin << endl;

                // As you can see pn the console log, the literals immediately perform the conversion logic that was
                // declared in the body of the overload. Really handy tool!

                cout << "\n\n" << endl;
            }

            // Operators that cannot be overloaded!
            {
                /*
                 * - The following list are the operators that C++ does not allow you to overload.
                 *  - .      Member selection.
                 *  - .*     Pointer to member selection.
                 *  - ::     Scope resolution.
                 *  - ?:     Conditional ternary operator.
                 *  - sizeof Get size of an object/class.
                 *
                 * - The compiler will not allow these operators to be overloaded because they are expected to perform
                 *   consistently and have really specific use cases for them. Overloading them would result in loss
                 *   of functionality or unexpected behaviours, so the compiler does not allow them to be overloaded.
                 */
            }


            // Final thoughts
            {
                /*
                 * - Program as many operators as you need in order to make your class easier to consume (use) and
                 *   implement. However, do not overdo it and program operators that serve no function!
                 *
                 * - Remember to add the keyword EXPLICIT to conversion operators to avoid implicit conversions,
                 *   ensuring type safety and better programming standards.
                 *
                 * - If your class contains dynamic memory resources, always ensure the copy constructor and copy
                 *   assignment operator are implemented! If the class is a base class, ensure the destructor is
                 *   implemented and marked as virtual to ensure polymorphism and proper memory management.
                 *
                 * - Tied to the point above, if you have dynamic memory resources, do program move constructor and move
                 *   assignment operator. This will make your class more performant and prevent heavy loads of memory
                 *   allocation and deallocation.
                 *
                 * - Don't assume the compiler will create a move constructor and assignment operator for you. It won't!
                 *   It is not a requirement so the compiler will just avoid creating them and rely on the copy
                 *   operations, hence why it is important to properly implement in case you don't program move logic.
                 */
            }
        }
    }

    return 0;
}