/*
 * Connor Ness - cdn073000
 * CE1337.007
 * Homework 8
 */

#include <iostream>
#include "TimeClock.h"

using namespace std;

int main() {
    int startHour;
    int startSec;
    cout << "Enter the starting hour in 24Hr HHMM format: ";
    cin >> startHour;
    cout << "Enter the starting second in SS format: ";
    cin >> startSec;
    MilTime obj1;
    obj1.setMilHours(startHour);
    obj1.setSeconds(startSec);

    int endHour;
    int endSec;
    cout << "Enter the ending hour in 24Hr HHMM format: ";
    cin >> endHour;
    cout << "Enter the ending second in SS format: ";
    cin >> endSec;
    TimeClock obj2(obj1.getMilHours(), obj1.getSeconds(), endHour, endSec);

    cout << "The time difference between " << obj2.getHours() << ":" << obj2.getMinutes()
         << " and " << obj2.getEndHr() << " in 24Hr HHMM format is: "
         << obj2.TimeDifference() << endl;
    return 0;
}