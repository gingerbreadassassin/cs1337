/*
 * This is code adapted from a previous assignment, replacing all bracket notation manipulation
 * of arrays with pointers and pointer manipulation
 */

#include <iostream>
#include <random>
#include <chrono>
using namespace std;

const int elements = 10;

// Function prototypes
void bubbleSortArray(char *, int size);                     // Prototype the bubble sort function
void printArray(char *, int size);                          // Prototype the array printer function
void arrayPop(char *, int size);                            // Prototype the array populator function

/*
 * The main loop here creates the array to be sorted, then calls the sorting functions,
 * passing the array into the function.
 */
int main() {

    char origArray[elements];                               // Initialize the array
    arrayPop(origArray, elements);                          // Populate the array

    cout << "The original array is:\n";
    printArray(origArray, elements);
    cout << endl;
    cout << "Sorting with bubble sort!\n";
    bubbleSortArray(origArray, elements);
    printArray(origArray, elements);
    return 0;
}

/*
 * The bubble sort function here starts at the first element in an array and compares it to the next.
 * If the first is larger than the second, they are swapped. This continues until the end of the array,
 * at which point the algorithm starts back at the beginning of the array. It iterates through until
 * no swaps are made.
 */
void bubbleSortArray(char *arrayPtr, int size)              // Define the bubble sort function
{
    char temp;
    char *anchor;
    anchor = arrayPtr;                                      // create a pointer that will not be manipulated
    bool swap;
    int iterations = 0,
        swapCount = 0;                                      // will count how many swaps had to be made

    do
    {
        swap = false;
        for (int count = 0; count < (size - 1); count++)    // run for each element in array until penultimate
        {
            arrayPtr = anchor + count;
            char cur, next;
            cur = *arrayPtr;
            arrayPtr++;
            next = *arrayPtr;
            arrayPtr = anchor + count;
            if (cur < next)                                 // if current element is less than next, swap
            {
                temp = cur;                                 // save the current array element
                cur = next;                                 // change the current array element to the next
                *arrayPtr = cur;
                arrayPtr++;                                 // Re-assign the pointer to the next address
                next = temp;                                // change the next array element to the current
                *arrayPtr = next;
                swap = true;                                // set 'swap' flag to true
                swapCount++;
            }
        }
        iterations++;
    } while(swap);                                          // keep sorting when 'swap' has happened (is true)
    cout << "Bubble sorting done in " << iterations << " iterations and "
         << swapCount << " swaps.\n";
}

/*
 * The array printing function prints out the contents of an array contained in brackets and formatted in a
 * human-readable list.
 */
void printArray(char *arrayPtr, int size)                   // Define the array printer function
{
    cout << "[ ";                                           // begin the line with open square brackets
    for (int count = 0; count < (size); count++)            // step through and print each element in array
    {
        cout << *arrayPtr;                                  // print the element
        if (count < (size - 1))                             // append comma+space
        {
            cout << ", ";
        }
        arrayPtr++;
    }
    cout << " ] ";                                          // append space and close square bracket
}

/*
 * The arrayPop function generates a pseudo-random number and picks from a list of capital letters
 * to populate each element in an array.
 */
void arrayPop(char *arrayPtr, int size)
{
    unsigned seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine random(seed);
    uniform_int_distribution<int> dist(0,25);

    for (int i = 0; i < size; i++)                          // Fill the array with random characters
    {
        *arrayPtr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[dist(random)];
        arrayPtr++;
    }
}