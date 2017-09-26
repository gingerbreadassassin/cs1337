/***********************************************************************************************************************
 *
 *  This program demonstrates two sorting algorithms; bubble sort and select sort. The requested program calls for
 *  two identical arrays, each of which will be sorted by one algorithm or another. The program should also print the
 *  array after each comparison.
 *
 *  I have taken things a few steps further. To begin with, instead of imagining up eight values and manually placing
 *  them out of order, this fills the array with pseudorandom integers from 0-999. In the interest of trying to
 *  better understand how the algorithms function, I have also made the printed text a little more verbose. It now
 *  includes the numbers being compared and whatever changes have been made. This program also counts how many
 *  comparisons and swaps have been made in order to sort the array.
 *
 *  Very large arrays (bigger than the 8 elements requested) can be created by changing the "elements" definition.
 *
 **********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define elements 8                                            // const int doesn't work in C :(

// Function prototypes
void bubbleSortArray(int array[], int size);                  // Prototype the bubble sort function
void selectSortArray(int array[], int size);                  // Prototype the select sort function
void printArray(int array[], int size);                       // Prototype the array printer function

/*
 * The main loop here creates the array to be sorted, then calls the sorting functions, passing the array into the
 * function. When passed, the function wound up editing the memory address containing the array, so the second sorting
 * function would never have any work to do. To address this, I created two copies of the original array.
 */
int main() {

    int origArray[elements],                                  // Initialize the arrays
        bubbleArray[elements],
        selectArray[elements];

    srand((unsigned int)time(NULL));                          // Seed the rand() function with computer's time

    for (int i = 0; i < elements; i++)                        // Fill the array with random integers less than 1000
    {
        origArray[i] = rand() % 1000;
    }

    for (int i = 0; i < elements; i++)                        // Copy the array because C likes to change things
    {
        bubbleArray[i] = origArray[i];
        selectArray[i] = origArray[i];
    }

    printf("The original array is:\n");
    printArray(origArray, elements);
    puts("");
    printf("Sorting with bubble sort!\n");
    bubbleSortArray(bubbleArray, elements);
    printf("The original array was:\n");
    printArray(origArray, elements);
    puts("");
    printf("Now sorting with select sort!\n");
    selectSortArray(selectArray, elements);
    return 0;
}

/*
 * The bubble sort function here starts at the first element in an array and compares it to the next. If the first
 * is larger than the second, they are swapped. This continues until the end of the array, at which point the
 * algorithm starts back at the beginning of the array. It iterates through until no swaps are made.
 */
void bubbleSortArray(int array[], int size)                   // Define the bubble sort function
{
    int swap,                                                 // 'swap' will be either 0 or 1 to stand in for 'bool'
        temp,
        iterations = 0,
        swapCount = 0;                                        // will count how many swaps had to be made

    do
    {
        swap = 0;                                             // set 'swap' flag to false
        for (int count = 0; count < (size - 1); count++)      // run for each element in array until penultimate
        {
            printArray(array, size);
            if (array[count] > array[count + 1])              // if current element is greater than next, swap
            {
                temp = array[count];                          // save the current array element
                array[count] = array[count + 1];              // change the current array element to the next
                array[count + 1] = temp;                      // change the next array element to the current
                swap = 1;                                     // set 'swap' flag to true
                swapCount++;
                printf("%i is greater than %i, swapping! %i swaps so far.\n",
                       array[count], array[count + 1], swapCount);
            }
            else
            {
                printf("%i is less than %i; no change made.\n", array[count], array[count + 1]);
            }
            iterations++;                                     // count number of iterations NOT SWAPS!!!

        }
    } while (swap == 1);                                      // keep sorting when 'swap' has happened (is true)
    printf("Bubble sorting done in %i iterations and %i swaps.\n", iterations, swapCount);
}

/*
 * The select sort function scans through the entire array and finds the smallest value. If the smallest value
 * happens to be in the first position, it continues to the next smallest number. If the next smallest number
 * doesn't appear in the next array index, it swaps it with the value currently there. This continues until it reaches
 * the penultimate position, at which point the largest number must have been moved to the last position.
 */
void selectSortArray(int array[], int size)                     // Define the select sort function
{
    int startScan, minIndex, minValue, iterations = 0,
        swapCount = 0;

    for (startScan = 0; startScan < (size - 1); startScan++)   // Begin scanning at the 0th element and increment
                                                               //   until the penultimate element.
    {
        printArray(array, size);
        minIndex = startScan;                                  // In case the smallest value is at this index already
        minValue = array[startScan];                           // Set the current min to the value in current index
        for (int index = startScan + 1; index < size; index++) // Look at next element until last is reached
        {
            if (array[index] < minValue)                       // if the observed value is less than the stored min,
            {
                minValue = array[index];                       // set the stored min to the observed value, and
                minIndex = index;                              // select the index at which the smallest value is found
            }
        }
        if (startScan == 0 && array[startScan] != minValue)    // make the printing sensible with conditions
        {
            printf("The smallest number is %i; swapping with %i, which is in position %i.",
                   array[minIndex], array[startScan], startScan);
            swapCount++;
        }
        else if (startScan == 0 && array[startScan] == minValue)
        {
            printf("The smallest number is %i, which is already in position %i.",
                   minValue, startScan);
        }

        else if (array[startScan] == minValue)
        {
            printf("The next smallest number is %i, which is already in position %i.",
                   minValue, startScan);
        }
        else
        {
            printf("The next smallest number is %i; swapping with %i, which is in position %i.",
                   array[minIndex], array[startScan], startScan);
            swapCount++;
        }
        array[minIndex] = array[startScan];                    // move value at current position to where min was found
        array[startScan] = minValue;                           // store the minimum value at the current position
        puts("");
        iterations++;
    }
    printArray(array, size);
    printf("The last position must be the largest number.\n");
    printf("Select sorting done in %i iterations and %i swaps.\n", iterations, swapCount);

}

/*
 * The array printing function prints out the contents of an array contained in brackets and formatted in a
 * human-readable list.
 */
void printArray(int array[], int size)                         // Define the array printer function
{

    printf("[ ");                                              // begin the line with open square brackets
    for (int count = 0; count < (size); count++)               // step through and print each element in array
    {
        printf("%i", array[count]);                            // print the element

        if (count < (size - 1))                                // unless this is the last element, append comma+space
        {
            printf(", ");
        }
    }
    printf(" ] ");                                            // append space and close square bracket
}

