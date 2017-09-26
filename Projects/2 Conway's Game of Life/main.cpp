/*
 * Conway's Game of Life - Project 2
 * CS 1337.007
 * Connor Ness - cdn073000
 *
 * This program recreates Conway's "Game of Life" in C++ using
 * pointers and pointer arithmetic. The input file must be named
 * "simbac.txt" and must have the same number of characters in each
 * line. Live cells are indicated witn '*'. Blank spaces are dead.
 */

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

void getDepth(fstream &, int*);
void getWidth(fstream &, int*);
void getInput(int*);
int neighborSum(int, int, int, int, int*);
int arraySum(int*, int);

int main() {
    // Open the simbac.txt file
    fstream petri;
    petri.open("simbac.txt");

    if(!petri) {
        cout << "Could not open file.";
        exit(-1);
    }

// set petriWidth to the petriWidth of the first line in the simbac.txt file
// set petriDepth to the number of lines in the simbac.txt file
    int petriDepth, petriWidth;
    getDepth(petri, &petriDepth);
    petri.clear();
    getWidth(petri, &petriWidth);
    petri.clear();
    petri.seekg(0, ios::beg);

// Ask the user how many generations should be simulated (maximum of 10)
// validate user input is both an integer and 1 <= input <= 10
    int gens = 0;
    cout << "How many generations do you wish to simulate (1 to 10): \n";
    getInput(&gens);
    while(gens < 1 || gens > 10) {
        cout << "\n Please choose an integer in the range 1-10: \n";
        getInput(&gens);
    }

// Create the petriDish array with petriDepth * petriWidth elements
    int *petriDish;
    petriDish = new int[petriDepth * petriWidth];
    // create an anchor for the beginning of the array
    int *petriAnchor;
    petriAnchor = petriDish;

//   Create a new array with the same length as
//   petriDish. Call it nextGen. This is so that
//   the current state of the organisms may be analyzed without being
//   modified.
    int *nextGen;
    nextGen = new int[petriDepth * petriWidth];
    int *nextGenAnchor;
    nextGenAnchor = nextGen;

// Populate the petriDish array (ignores newline characters)
    int count = 0;
    char ch = 'x';
    while(!petri.eof()) {
        petri.get(ch);
        if(ch == '*') {
            *petriDish = 1;
            petriDish++;
        } else if(ch == ' ') {
            *petriDish = 0;
            petriDish++;
        }
        count++;
    }
    petri.clear();
    petri.seekg(0, ios::beg);

//  gracefully exit if each line in the file does not contain
//  the same number of characters or ends with newline
    if(ch == '\n' || ch == '\r')
        count++;
    if(count % petriDepth != 0){
        cout << "Check that your simbac.txt file has the same number of characters for each line,\n"
                "or that a newline character does not exist at the end of the file.";
        exit(-1);
    }

    // reset the petriDish pointer to the beginning of the array
    petriDish = petriAnchor;

//  For each generation,
//   Set each cell in nextGen to the sum of its representative neighbors
//   in petriDish.
    for(int g = 0; g < gens; g++) {
        for (int y = 0; y < petriDepth; y++) {
            for (int x = 0; x < petriWidth; x++) {
                if (*petriDish == 1)
                    *nextGen = neighborSum(y, x, petriDepth, petriWidth, petriDish) - 1;
                else if (*petriDish == 0)
                    *nextGen = neighborSum(y, x, petriDepth, petriWidth, petriDish);
                petriDish++;
                nextGen++;
            }
        }
        petriDish = petriAnchor;
        nextGen = nextGenAnchor;

//   Write the results to the console while simultaneously setting up the
//       next petriDish. If the space is currently occupied and has 2 or
//       3 neighbors, it survives. Any more or less and it dies. If a space
//       is unoccupied and has exactly 3 neighbors, a cell is born.
        for (int i = 0; i < petriDepth; i++) {
            for (int j = 0; j < petriWidth; j++) {
                if (*petriDish == 1) {
                    if (*nextGen > 1 && *nextGen < 4) {
                        cout << '*';
                        *petriDish = 1;
                    } else {
                        cout << ' ';
                        *petriDish = 0;
                    }
                } else if (*petriDish == 0) {
                    if (*nextGen == 3) {
                        cout << '*';
                        *petriDish = 1;
                    } else {
                        cout << ' ';
                        *petriDish = 0;
                    }
                }
                petriDish++;
                nextGen++;
            }
            cout << '\n';
        }
        petriDish = petriAnchor;
        nextGen = nextGenAnchor;
    }

    // upon the final generation, save the current state to the simbac.txt file
    petri.trunc;
    for(int y = 0; y < petriDepth; y++) {
        for(int x = 0; x < petriWidth; x++) {
            if(*petriDish == 1)
                petri.put('*');
            else if(*petriDish == 0)
                petri.put(' ');
            petriDish++;
        }
        // don't print a newline on the last line
        if(y < petriDepth - 1)
            petri.put('\n');
    }

    // do some cleaning up
    petri.clear();
    petri.close();
    delete [] petriAnchor;
    delete [] nextGenAnchor;

    cout << "The simulation is complete.";
    return 0;
}

// count how many lines exist in the file
void getDepth(fstream & in, int *lines) {
    *lines = 0;
    string line;
    in.seekg(0, ios::beg);
    while(getline(in, line))
        (*lines)++;
}

// count how many characters exist in a line
void getWidth(fstream & in, int *chars) {
    *chars = 0;
    string line;
    in.seekg(0, ios::beg);
    getline(in, line);
    *chars = (int)line.length();
}

// validate that user input is an integer
void getInput(int *choice) {
    cin >> *choice;

    if(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        *choice = 0;
    }
}

/*
 * neighborSum needs the current coordinates of petriDish, y and x.
 *  Care must be taken at the corners and on the edges of the dish
 *  For each case, an array with as many elements as the target
 *  space has neighbors is created. The elements will either be 1
 *  or 0, corresponding to the occupancy of the neighboring spaces.
 *  The sum of this array's contents is then returned.
 *  Returns -1 if something goes wrong.
 */
int neighborSum(int y, int x, int depth, int width, int *petri) {
    int sum = -1;
    int *anchor;

    // when looking at spaces between the top and bottom rows
    if(y > 0 && y < depth - 1) {
        // when looking at spaces between the top and bottom rows and
        // between the leftmost and rightmost columns
        if(x > 0 && x < width - 1) {
            int *array = new int[9];
            anchor = array;
            petri -= (width + 1);
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 3);
            }
            array = anchor;
            sum = arraySum(array, 9);
            delete[]array;
        }
        // when looking at spaces between the top and bottom rows and
        // in the leftmost column
        else if(x == 0) {
            int *array = new int[6];
            anchor = array;
            petri -= width;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 2; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 2);
            }
            array = anchor;
            sum = arraySum(array, 6);
            delete[]array;
        }
        // when looking at spaces between the top and bottom rows and
        // in the rightmost column
        else if(x == width - 1) {
            int *array = new int[6];
            anchor = array;
            petri -= (width + 1);
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 2; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 2);
            }
            array = anchor;
            sum = arraySum(array, 6);
            delete[]array;
        }
    }
    // when looking at the top row
    else if(y == 0) {
        // when looking at the top row and
        // between the leftmost and rightmost columns
        if(x > 0 && x < width - 1) {
            int *array = new int[6];
            anchor = array;
            petri--;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 3; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 3);
            }
            array = anchor;
            sum = arraySum(array, 6);
            delete[]array;
        }
        // when looking at the top row and
        // the leftmost column (the top left corner)
        else if(x == 0) {
            int *array = new int[4];
            anchor = array;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 2);
            }
            array = anchor;
            sum = arraySum(array, 4);
            delete[]array;
        }
        // when looking at the top row and
        // the rightmost column (the top right corner)
        else if(x == width - 1) {
            int *array = new int[4];
            anchor = array;
            petri--;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 2);
            }
            array = anchor;
            sum = arraySum(array, 4);
            delete[]array;
        }
    }
    // when looking at the bottom row
    else if(y == depth - 1) {
        // when looking at the bottom row and
        // between the leftmost and rightmost columns
        if(x > 0 && x < width - 1) {
            int *array = new int[6];
            anchor = array;
            petri -= (width + 1);
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 3; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 3);
            }
            array = anchor;
            sum = arraySum(array, 6);
            delete[]array;
        }
        // when looking at the bottom row and
        // the leftmost column (the bottom left corner)
        else if(x == 0) {
            int *array = new int[4];
            anchor = array;
            petri -= width;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 2);
            }
            array = anchor;
            sum = arraySum(array, 4);
            delete[]array;
        }
        // when looking at the bottom row and
        // at the rightmost column (the bottom right corner)
        else if(x == width - 1) {
            int *array = new int[4];
            anchor = array;
            petri -= (width + 1);
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    *array = *petri;
                    array++;
                    petri++;
                }
                petri += (width - 2);
            }
            array = anchor;
            sum = arraySum(array, 4);
            delete[]array;
        }
    }

    if(sum < 0 || sum > 9)
        sum = -1;

    return sum;
}

/*
 * arraySum will require an array and the size, and will return the sum
 *  of its elements
 */
int arraySum(int *array, int size)
{
    if(size == 0)
        return 0;
    else
        return *array += arraySum((array + 1), size - 1);
}