/*
 * Project 5 - Ticket Reservation (OOP version)
 * Authored by Connor Ness -- cdn073000
 *
 * This program emulates a user interface to select seats in a theater which has three
 * auditoriums. It displays the seat availability in the auditoriums and labels the
 * rows and columns so that the user may easily choose a group of seats.
 *
 * The auditorium states are loaded into memory from files using structures to represent
 * the auditoriums. Each auditorium structure has seven integer variables representing width,
 * depth, available and occupied seats, and adult, senior, and child ticket sales. Each auditorium
 * structure also contains a linked list object to hold its seats, as well as a function that
 * returns total sales (to keep later code more tidy).
 *
 * This program also offers the user the best available seats based on the number of seats they want.
 * It does this by 'scoring' groups of as many consecutive available seats as the user requested with
 * a float number representing the distance of each seat from the middle of the auditorium. The group
 * of seats with the lowest score is the winner, and is returned back to the user asking whether
 * they wish to reserve the seats or not. If there are no available seats, the program tells the user.
 *
 * Overloaded operator usages:
 *  linkedlist []:
 *      198
 *      231
 *      310
 *      356
 *      363
 *      387
 *      389
 *      394
 *  linkedlist +=:
 *      175
 *  nodeRes >>:
 *      174
 *  nodeRes << ostream:
 *      216
 *  nodeRes << ofstream:
 *      249
 */

#include <iostream>
#include "linkedList.h"
#include "nodeRes.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <c++/cstring>
#include <c++/cmath>

using namespace std;

// Create auditorium structures
struct aud{
    int width,
        depth,
        av,
        occ,
        adult,
        senior,
        child;
    linkedList list;
    int sales(){return ((adult*7) + (senior*5) + (child*3));}
};


// Function prototypes
void mainMenu(aud*);
void dispAud(aud &);
void writeAud(aud &, int);
aud& audSelect(aud*);
void seatSelect(aud&);
void viewReport(aud*);
void onExit(aud*);
int getAudDepth(int);
int getAudWidth(int);
void popLists(aud &, int);
bool seatSeq(nodeRes *, int, int);
float getScore(nodeRes *seat, int midRow, int midSeat);
int toIndex(int, int, int width);
int getInput();
bool getYorN();



// Define the labels globally to save room in functions
int label[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};


int main(){
    aud a[4];
    // initialize the auditorium structures
    for(int i = 1; i < 4; i++){
        a[i].width = getAudWidth(i);
        a[i].depth = getAudDepth(i);
        a[i].adult = a[i].senior = a[i].child = 0;
        popLists(a[i], i);
    }
    mainMenu(a);
    return 0;
}


// Display the mainMenu user interface.
void mainMenu(aud* a){
    cout << "Please choose an option from the menu:\n"
         << "1. Reserve Seats\n"
         << "2. View Auditorium\n"
         << "3. Exit\n";

    int choice;
    choice = getInput();

    switch(choice){
        case 1: seatSelect(audSelect(a));                    // execute seat selection based on auditorium selection
            mainMenu(a);
        case 2: dispAud(audSelect(a));                      // display auditorium based on selection
            mainMenu(a);
        case 3: viewReport(a);                               // view report and exit
            onExit(a);
            exit(0);
        default: cout << "You must enter 1, 2, or 3\n";     // validate user input
            mainMenu(a);
    }
}


// Get auditorium depth in seats
int getAudDepth(int n){
    string line;
    ifstream in("A"+to_string(n)+".txt");
    if(!in){
        cout << "error opening file!";
        exit(0);
    }
    int rowDepth = 0;
    in.seekg(0, ios::beg);      // seek to beginning of the file
    while(getline(in, line))    // Increment a counter each time a newline is found until EOF
        rowDepth++;
    in.clear();                 // reset fstream before returning
    in.close();
    return rowDepth;            // return the "depth", or the number of rows in the auditorium
}


// Get auditorium width in seats
int getAudWidth(int n){
    string line;
    ifstream in("A"+to_string(n)+".txt");
    if(!in){
        cout << "error opening file!";
        exit(0);
    }
    in.seekg(0, ios::beg);      // seek to beginning of the file
    getline(in, line);          // get the first line of the file and store as string
    in.clear();                 // reset fstream before returning
    in.close();
    return (int)line.length();  // return the integer representation of the length of string
}


// Build a linked list by reading in from a file
void popLists(aud &audN, int n){
    ifstream in("A"+to_string(n)+".txt");
    // if the file cannot be opened, end the program
    if(!in){
        cout << "error opening file!";
        exit(0);
    }
    in.seekg(0, ios::beg);

    // for each row
    for (int d = 1; d < audN.depth + 1; d++) {
        // for each seat
        for (int w = 1; w < audN.width + 1; w++) {
            nodeRes* newnode = new nodeRes(d, w);
            in >> newnode;
            audN.list+=newnode;
            if(newnode->getRes())
                audN.occ++;
            }
        }
    audN.av = audN.list.len() - audN.occ;
    // clean up
    in.clear();
    in.close();
}

// Display the auditorium state to the user
void dispAud(aud &audN){
    // Start with some space for pretty formatting
    cout << "  ";
    // print the column labels and a newline
    int x = 0;
    int i = 0;
    for(int l = 0; l < audN.width; l++){
        cout << label[x];
        x++;
        if(x == 10)
            x = 0;
    }
    cout << endl;

    // reset the label counter
    x = 0;

    // for each row, print the row label...
    for(int r = 1; r < audN.depth + 1; r++) {
        cout << label[x] << " ";
        x++;
        // reset the label counter
        if (x == 10)
            x = 0;
        // for each seat in the row,
        for (int s = 1; s < audN.width + 1; s++){
            cout << audN.list[i];
            i++;
        }
        // and a newline
        cout << endl;
    }
}


// Do this before exiting
void onExit(aud* a){
    // for each auditorium...
    for(int i = 1; i < 4; i++){
        // write the state of the auditorium to its respective file
        writeAud(a[i], i);
    }
}


// Write the state of the auditorium to its file
void writeAud(aud &audN, int n){
    // open the file
    ofstream out("A"+to_string(n)+".txt");
    // if the file cannot be opened, end the program
    if(!out){
        cout << "error opening file!";
        exit(0);
    }
    int i = 0;
    // for each row
    for(int r = 1; r < audN.depth + 1; r++) {
        // for each seat
        for (int s = 1; s < audN.width + 1; s++){
            out << audN.list[i];
            i++;
        }
        // if this is not the last row, add a newline to file
        if(r != audN.depth)
            out.put('\n');
    }
    // close the file
    out.close();
}


// ask the user to select an auditorium and return the number
aud& audSelect(aud* a){
    cout << "Choose an auditorium:\n"
         << "1. Auditorium 1\n"
         << "2. Auditorium 2\n"
         << "3. Auditorium 3\n";

    int choice = 0;

    while(choice < 1 || choice > 3){
        cout << "Enter 1, 2, or 3\n";
        choice = getInput();
    }
    return a[choice];
}


// ask the user to select a seat for a given auditorium
void seatSelect(aud &audN){
    // display the auditorium
    dispAud(audN);

    cout << "How many total seats would you like to reserve?\n";

    int tot = -1;
    while(tot < 1) {
        cout << "Please enter an integer 1 or greater:\n";
        tot = getInput();
    }
    int adult, senior, child;
    adult = senior = child = -1;

    // Take user input and validate
    cout << "How many adults?\n";
    while(adult < 0) {
        cout << "Please enter an integer 0 or greater:\n";
        adult = getInput();
    }
    if(adult < tot) {
        cout << "How many seniors?\n";
        while(senior < 0) {
            cout << "Please enter an integer 0 or greater:\n";
            senior = getInput();
        }
        if(adult + senior < tot){
            cout << "How many children?\n";
            while(child < 0) {
                cout << "Please enter an integer 0 or greater:\n";
                child = getInput();
            }
            if(adult + senior + child > tot)
                child = tot - (adult + senior);
        }
        else if(adult + senior > tot)
            senior = tot - adult;
    }
    else if(adult > tot)
        adult = tot;

    // create array of seats to represent user's selection in case seats not consecutive
    nodeRes** selection = new nodeRes*[tot];
    bool isAvailable = true;
    // loop for total seats
    for(int i = 0; i < tot; i++) {
        int row = 0, seat = 0;

        // ask user for the row
        cout << "In which row would you like to sit?\n";
        while(row < 1 || row > audN.depth){
            cout << "Please choose a number from 1 to "
                 << audN.depth << ".\n";
            row = getInput();
        }

        // ask user for the column (seat)
        cout << "Which seat?\n";
        while(seat < 1 || seat > audN.width){
            cout << "Please choose a number from 1 to "
                 << audN.width << ".\n";
            seat = getInput();
        }
        selection[i] = audN.list[toIndex(row, seat, audN.width)];
        // test to see if user's selected seats are available
        if(selection[i]->getRes())
            isAvailable = false;
    }

    // if the user's seats were available, reserve them
    if(isAvailable){
        for(int i = 0; i < tot; i++) {
            selection[i]->setRes();
            audN.av--;
            audN.occ++;
        }
        if(adult > -1)
            audN.adult += adult;
        if(senior > -1)
            audN.senior += senior;
        if(child > -1)
            audN.child += child;
        cout << "Seats reserved!\n";
    }

    /*
     * In case the user's chosen seats are occupied, find the best available seats.
     * This algorithm starts looking in the middle of the theater for the best seats.
     * It ranks the seats based on their distance from the center of the theater using
     * the pythagorean theorem. It is not the most efficient of algorithms as it checks
     * every seat for availability and scores each available seat, but I didn't feel
     * like trying my hand at an NP-Hard algorithm.
     */
    else {
        cout << "The requested seat(s) were not available!\n";
        int middle = (((audN.depth * audN.width) - 1)/2); // find the middle index
        int midRow = (audN.depth + 1)/2; // find the middle row
        int midSeat = (audN.width + 1 )/2; // find the middle seat
        int addorsub = 1; // a flag to look ahead of or behind the middle
        int inc = 0; // how far from the middle index to search
        int start = -1; // initialize starting index to nonsense
        int best = start; // same for best
        // minScore is initialized as the diagonal distance across the entire theater
        // it is mathematically impossible to have a seat further away from the middle
        // than the theater's diagonal
        float minScore = sqrtf(powf(audN.depth, 2) + powf(audN.width, 2))*tot;
        // a node pointer to make the code cleaner
        nodeRes* check;
        float score;// initialize score

        do {
            score = 0;

            start = middle - (inc * addorsub); // set start index
            // catch if start gets too big
            if((start + tot) > (audN.width*audN.depth))
                start-=(tot+inc);
            check = audN.list[start]; // set node pointer

            // check if seat(s) are available
            isAvailable = seatSeq(check, check->getRow(), tot);
            if(isAvailable) {
                // if available, get the group's score
                score += getScore(audN.list[start], midRow, midSeat);

                if(score < minScore) {
                    // if this score is better than the current minimum,
                    // set the current min to this score and the best
                    // index to the current index
                    minScore = score;
                    best = start;
                }
            }

            // only increment inc every other iteration
            if(addorsub == -1)
                inc++;
            // flip the add or subtract flag to check both sides of middle index
            addorsub *= -1;
        } while(start > -1);

        // the best index will only change if suitable seats are found
        // so, if best has changed, seats have been found. Ask user if they
        // wish to reserve them
        if(best > -1) {
            cout << "The best available seats are: ";
            for(int i = 0; i < tot; i++) {
                cout << audN.list[best + i]->getSeat() << ", ";
            }
            cout << "in row " << audN.list[best]->getRow() << ".\n";
            cout << "Would you like to reserve them? Y/N: ";

            if(getYorN()){
                for(int i = 0; i < tot; i++) {
                    audN.list[best + i]->setRes();
                    audN.av--;
                    audN.occ++;
                }
                if(adult > -1)
                    audN.adult += adult;
                if(senior > -1)
                    audN.senior += senior;
                if(child > -1)
                    audN.child += child;
                cout << "Seats reserved!\n";
            }
            else
                cout << "No seats reserved!\n";

        }
        // if best index is still -1, no suitable seats were found
        else
            cout << "No seats could be found!\n";
    }
    // memory management
    delete[]selection;
}


// display a report containing the sales for each auditorium and for all
void viewReport(aud* a){
    int sales[4][6] = {{0}};                        // initialize a 4x3 array to hold seat sales data
    for(int c = 1; c < 4; c++)
    {
        sales[c - 1][0] = a[c].av;                 // set the first element to the auditorium's occupied seats
        sales[c - 1][1] = a[c].occ;                  // set the second to the auditorium's available seats
        sales[c - 1][2] = a[c].adult;
        sales[c - 1][3] = a[c].senior;
        sales[c - 1][4] = a[c].child;
        sales[c - 1][5] = a[c].sales();      // multiply the occupied seats by 7 to get total sales
    }
    for(int c = 0; c < 6; c++)                      // for each column...
    {
        for(int i = 0; i < 3; i++)
        {
            sales[3][c] += sales[i][c];             // find the sum of the cells and store in the bottom cell
        }
    }

    for(int r = 0; r < 4; r++)                      // print out each label and row in the sales array
    {
        if(r < 3)
            cout << "Auditorium " << r + 1 << ":";
        else
            cout << "Total       :";
        for(int c = 0; c < 6; c++)
        {
            cout << " ";
            if(c == 5)
                cout << "$";                        // print a dollar sign to indicate money
            cout << sales[r][c];
        }
        cout << endl;
    }

}


// check to see if seats are available and in the same row
bool seatSeq(nodeRes *seat, int row, int numSeats) {
    --numSeats;
    bool isAv = !seat->getRes();
    bool isSameRow = seat->getRow() == row;
    bool next = true;
    if(numSeats > 0)
        next = seatSeq(seat->getNext(), row, numSeats);
    return isAv && isSameRow && next;
}


// calculate the score for each seat. this is only ever called when consecutive available
// seats are found in the same row, so we don't have to worry about getNext here
float getScore(nodeRes *seat, int midRow, int midSeat) {
    float score = 0.0;
    int row = seat->getRow();
    int s = seat->getSeat();
    score += sqrtf(powf((float)(midRow - row), 2.0) + powf((float)(midSeat - s), 2.0));
    return score;
}


// converts row and seat to an index for [] notation
int toIndex(int row, int seat, int width) {
    return ((row - 1)*width + (seat - 1));
}

// Get user input and validate it
int getInput(){
    float choice = 0;
    cin >> choice;

    if(!cin.good() || choice != (int)choice){               // validate user input
        cin.clear();                                        // clear input stream
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); // purge input stream
        choice = -1;                                        // return predetermined error value
        cout << "Invalid input!\n";
    }
    return (int)choice;
}

bool getYorN() {
    string input;
    char in = 'x';
    while(in != 'Y' && in != 'N') {
        getline(cin, input);
        char *outp = new char[input.length()+1];
        strcpy(outp, input.c_str());
        in = toupper(outp[0]);
        delete[]outp;
        if(in != 'Y' && in != 'N')
            cout << "Please enter Y or N: ";
    }
    return in == 'Y';
}