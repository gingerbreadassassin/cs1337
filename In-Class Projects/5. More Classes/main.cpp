/*
 * Connor Ness - cdn073000
 * Kyle Bailey - kdb160630
 *
 * CE1337.007
 * In-Class Project 5
 */

#include <iostream>
#include "NumDays.h"

using namespace std;

int main() {
    NumDays test1(20.6667);
    NumDays test2(test1);
    test1.setHours(14.99);
    cout << test1+test2 << endl;
    cout << test1-test2 << endl;
    cout << (++test1).getHours() << endl;
    cout << (test2++).getHours() << endl;
    cout << (test1<test2) << endl;
    cout << (test1>test2) << endl;
    cout << test1.getDays() << " " << test2.getDays();

    return 0;
}