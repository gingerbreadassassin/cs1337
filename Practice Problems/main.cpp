#include <iostream>
using namespace std;

int arraySum(int array[], int size);
int multiply(int x, int y);
int power(int x, int y);
bool isMember(int array[], int target, int size);

int main() {
    cout << "Hello, World!" << endl;
    cout << multiply(7, 4) << endl;
    int testArray[6] = {1, 2, 3, 4, 5, 6};
    cout << arraySum(testArray, 6) << endl;
    cout << power(3, 3) << endl;
    if(isMember(testArray, 2, 6))
        cout << "Found!\n";
    return 0;
}


int arraySum(int array[], int size)
{
    if(size > 0)
        return array[size] + arraySum(array, size - 1);
    return 0;
}


int multiply(int x, int y)
{
    if(y > 0)
        return x + multiply(x, y - 1);
    return 0;
}


int power(int x, int y)
{
    if(y > 0)
        return x * power(x, y - 1);
    return 1;
}


bool isMember(int array[], int target, int size)
{
    if (target == array[size])
        return true;
    else if(size < 0)
        return false;
    else // (target != array[size])
        isMember(array, target, size - 1);
    // return false;
}