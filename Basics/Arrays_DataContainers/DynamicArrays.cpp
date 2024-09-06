//
// Created by juanf on 2024-02-13.
//

// Module 04

#include <iostream>
#include <vector>

// Used for test purposes. Bad practice to include all standard namespace.
using namespace std;

int DynamicArrays_main() {
    // Vector of ints, initialized to a size of 3 ints.
    vector<int> dynArray(3);

    // Each element can be accessed as regular static arrays.
    dynArray[0] = 365;
    dynArray[1] = -421;
    dynArray[2] = 789;

    cout << "Elements inside vector: " << dynArray.size() << endl;
    cout << "Capacity of the vector: " << dynArray.capacity() << endl;

    for (const auto value: dynArray) {
        cout << value << endl;
    }

    // Method to add a new variable/element/object with a default value of 10.
    // Constructs an int because of the int type template.
    // At this point, vector dynamically resizes itself to accommodate more data, increasing size and capacity.
    // Important to note that once a vector resizes itself, the capacity increase twofold the current capacity.
    dynArray.push_back(10);

    // Size makes reference to the elements currently present in the vector.
    // Capacity makes reference to the total number of elements it can hold before having to resize itself.

    cout << "Elements inside vector: " << dynArray.size() << endl;
    cout << "Capacity of the vector: " << dynArray.capacity() << endl;
    // When running the code, the line above outputs 6. This new capacity is 2 times the previous capacity of 3!

    for (const auto value: dynArray) {
        cout << value << endl;
    }

    return 0;
}