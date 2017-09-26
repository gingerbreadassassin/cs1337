/*
 * Connor Ness - cdn073000
 * Matthew Nevle - man160530
 *
 * April 6 2017
 * CS 1337.007
 */
#include <iostream>
#include "isFreezing.h"

using namespace std;

int main() {
    int temp;
    cout << "Enter a temperature to see what freezes and what boils: ";
    cin >> temp;
    isFreezing t;
    t.setTemp(temp);
    cout << "\nThese will freeze:\n";
    if(t.isEthylFreezing())
        cout << "Ethyl Alcohol\n";
    if(t.isOxygenFreezing())
        cout << "Oxygen\n";
    if(t.isWaterFreezing())
        cout << "Water\n";
    cout << "These will boil:\n";
    if(t.isEthylBoiling())
        cout << "Ethyl Alcohol\n";
    if(t.isOxygenBoiling())
        cout << "Oxygen\n";
    if(t.isWaterBoiling())
        cout << "Water\n";
    return 0;
}