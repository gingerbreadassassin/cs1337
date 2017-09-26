/*
* This is code adapted from a previous assignment, replacing all bracket notation manipulation
* of arrays with pointers and pointer manipulation in C
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define elements 10                                         // const int doesn't work in C :(

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

    printf("The original array is:\n");
    printArray(origArray, elements);
    puts("");
    printf("Sorting with bubble sort!\n");
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
    int swap,                                               // 'swap' will be either 0 or 1 in lieu of 'bool'
        iterations = 0,
        swapCount = 0;                                      // will count how many swaps had to be made

    do
    {
        swap = 0;                                           // set 'swap' flag to false
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
                swap = 1;                                   // set 'swap' flag to true
                swapCount++;
            }
        }
        iterations++;
    } while (swap == 1);                                    // keep sorting when 'swap' has happened (is true)
    printf("Bubble sorting done in %i iterations and %i swaps.\n", iterations, swapCount);
}

/*
 * The array printing function prints out the contents of an array contained in brackets and formatted in a
 * human-readable list.
 */
void printArray(char *arrayPtr, int size)                   // Define the array printer function
{
    printf("[ ");                                           // begin the line with open square brackets
    for (int count = 0; count < (size); count++)            // step through and print each element in array
    {
        printf("%c", *arrayPtr);                            // print the element
        if (count < (size - 1))                             // append comma+space
        {
            printf(", ");
        }
        arrayPtr = arrayPtr + 1;
    }
    printf(" ] ");                                          // append space and close square bracket
}

/*
 * The arrayPop function generates a pseudo-random number and uses that to populate an array with
 * characters from a list.
 */
void arrayPop(char *arrayPtr, int size) {

    srand((unsigned int) time(NULL));                       // Seed the rand() function with computer's time

    for (int i = 0; i < size; i++)                          // Fill the array with random characters
    {
        *arrayPtr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
        arrayPtr++;
    }
}

