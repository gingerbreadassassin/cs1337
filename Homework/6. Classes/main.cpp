/*
 * Connor Ness - cdn073000
 * Homework 6 - "Classes"
 *
 * This program is a basic example of how to define a class and create an
 * object of the class type.
 */

#include <iostream>
#include "farray.h"

using namespace std;

int main() {
    farray *test = new farray(5);
    test->farput(0, 123.3451);
    test->farput(1, 44.4123);
    test->farput(2, 5512.33);
    test->farput(3, 12.33);
    test->farput(4, 2.33);
    cout << "Value at index 2 is: " << test->farget(2) << endl;
    cout << "Maximum is: " << test->farmax() << endl;
    cout << "Minimum is: " << test->farmin() << endl;
    cout << "Average is: " << test->faravg() << endl;
    delete test;
    return 0;
}


