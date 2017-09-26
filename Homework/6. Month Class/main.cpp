/*
 * Connor Ness - cdn073000
 * CE1337.007
 * Homework 7 - Months and Classes
 */

#include <iostream>
#include "Month.h"

using namespace std;

int main() {
    Month test;
    cout << test;
    Month test2(test--);
    Month test3;
    cin >> test3;
    Month test4("June");
    Month test5(4);
    Month test6("dasdasd");
    Month test7(13);
    test6.setMonthN(3);
    test7.setMonthA("July");
    cout << test << test2 << test3 << test4 << test5 << test6 << test7;
    Month test8(test++);
    cout << test << test8;
    cout << --test << ++test8;
    test.setMonthA(test5.getMonthA());
    cout << test;
    test.setMonthN(test4.getMonthN());
    cout << test;
    return 0;
}