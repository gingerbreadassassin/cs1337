/*
 * Evan Lieu exl160530
 * Connor Ness cdn073000
 * CS 1337.004
 * In-Class Assignment 1: Recursion
 * February 2, 2017
 */

#include <iostream>
using namespace std;


bool arraySearch(int array[], int search, int size);
void toBinary(int baseTen);

int main() {
    int num = 0;
    int testArray[15] = {12, 51, 23, 65, 123, 16, 98, 19, 15, 99, 33, 67, 81, 90, 69};
    cout << "Please enter a number: ";
    cin >> num;
    cout << endl;
    if(arraySearch(testArray, num, 14))
        toBinary(num);
    else
        cout << "The number was not found in the array." << endl;
    return 0;
}


bool arraySearch(int array[], int search, int size)
{
    if (size < 0)
        return false;
    else if (search == array[size])
        return true;
    else
        arraySearch(array, search, size - 1);
}

void toBinary(int baseTen)
{
    if(baseTen == 1)
        cout << 1;
    else if(baseTen % 2 == 1)
    {
        toBinary(baseTen / 2);
        cout << 1;
    }
    else if(baseTen % 2 == 0)
    {
        toBinary(baseTen / 2);
        cout << 0;
    }
}