/*
 * Project 3 - Ticket Reservation Redux (Linked List version)
 * Authored by Connor Ness -- cdn073000
 *
 * This program emulates a user interface to select seats in a theater which has three
 * auditoriums. It displays the seat availability in the auditoriums and labels the
 * rows and columns so that the user may easily choose a group of seats.
 *
 * The auditorium states are loaded into memory from files using structures to represent
 * the auditoriums. Each auditorium structure has four integer variables: width and depth in seats,
 * and the number of available and occupied seats. Each auditorium structure also has two linked lists:
 * one for available seats and one for occupied seats. The linked lists consist of nodes representing
 * seats. The nodes have two integers: row and seat. The nodes also have a pointer to the next node
 * in the list.
 */

#include <iostream>
#include <fstream>
#include <limits>
using namespace std;


// Create the linked list node structure
struct sNode{
    int row,
        seat;
    sNode* next;
};

// Create auditorium structures
struct aud{
    int width,
        depth,
        av,
        occ;
    sNode* avHead;
    sNode* occHead;
} a[4]; // a[0] is never used


// Function prototypes
void mainMenu();
void dispAud(int);
void writeAud(int);
int audSelect();
void seatSelect(int);
void viewReport();
void onExit();
int getAudDepth(int);
int getAudWidth(int);
void popLists(aud &, int);
void addNode(sNode* &, int, int);
void delNode(sNode* &, int, int);
bool findNode(sNode*, int, int);
int countNode(sNode*);
int getInput();
void listDestruct(sNode* &);


// Define the labels globally to save room in functions
int label[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};


int main(){
    // initialize the auditorium structures
    for(int i = 1; i < 4; i++){
        a[i].width = getAudWidth(i);
        a[i].depth = getAudDepth(i);
        a[i].avHead = nullptr;
        a[i].occHead = nullptr;
        popLists(a[i], i);
        a[i].av = countNode(a[i].avHead);
        a[i].occ = countNode(a[i].occHead);
    }
    mainMenu();
    return 0;
}


// Display the mainMenu user interface.
void mainMenu(){
    cout << "Please choose an option from the menu:\n"
         << "1. Reserve Seats\n"
         << "2. View Auditorium\n"
         << "3. Ticket Report\n"
         << "4. Exit\n";

    int choice;
    choice = getInput();

    switch(choice){
        case 1: seatSelect(audSelect());                    // execute seat selection based on auditorium selection
            mainMenu();
        case 2: dispAud(audSelect());                       // display auditorium based on selection
            mainMenu();
        case 3: viewReport();                               // view report
            mainMenu();
        case 4: viewReport();                               // view report and exit
            onExit();
            exit(0);
        default: cout << "You must enter 1, 2, or 3\n";     // validate user input
            mainMenu();
    }
}


// Get auditorium depth in seats
int getAudDepth(int n){
    string line;
    ifstream in("A"+to_string(n)+".txt");
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
    if(in.bad()){
        cout << "error opening file!";
        exit(0);
    }
    in.seekg(0, ios::beg);
    // as long as the filestream has not reached the end of the file...
    while(!in.eof()) {
        // for each row
        for (int d = 1; d < audN.depth + 1; d++) {
            // for each seat
            for (int w = 1; w < audN.width + 1; w++) {
                // initialize variable to avoid bugs and get character from file
                char ch = 'x';
                in.get(ch);
                // if character is '#', add node to the "available" list
                if(ch == '#')
                    addNode(audN.avHead, d, w);
                // if character is '.', add node to the "occupied" list
                else if(ch == '.')
                    addNode(audN.occHead, d, w);
                // to handle different endline behaviors
                else if(ch == '\n'){
                    in.get(ch);
                    if(ch == '#')
                        addNode(audN.avHead, d, w);
                    else if(ch == '.')
                        addNode(audN.occHead, d, w);
                }
            }
        }
    }
    // clean up
    in.clear();
    in.close();
}


// Add node to a linked list
void addNode(sNode* &h, int row, int seat){
    // create the new node
    sNode* nNode;
    nNode = new sNode;
    nNode->row = row;
    nNode->seat = seat;
    nNode->next = nullptr;
    // in case the list is empty
    if(!h){
        h = nNode;
        return;
    }
    // in case the first item in the list should come after the new node
    else if(row < h->row){
        nNode->next = h;
        h = nNode;
        return;
    }
    else if(row == h->row && seat < h->seat){
        nNode->next = h;
        h = nNode;
        return;
    }
    // otherwise...
    else{
        // create placeholder pointer
        sNode* cur = h;
        // as long as there is a next item in the list
        while(cur->next){
            // if the selected row is less than the next item's row, insert new node before next
            if(row < cur->next->row){
                nNode->next = cur->next;
                cur->next = nNode;
                return;
            }
            // if the selected row is the next item's row
            else if(row == cur->next->row){
                // if the selected seat is less than the next item's seat, insert new node before next
                if(seat < cur->next->seat){
                    nNode->next = cur->next;
                    cur->next = nNode;
                    return;
                }
                // otherwise, advance the placeholder pointer to the next node
                else
                    cur = cur->next;
            }
            // otherwise, advance the placeholder pointer to the next node
            else
                cur = cur->next;
        }
        // if the node belongs at the end of the list, add it there
        cur->next = nNode;
    }
}


// Delete node from a linked list
void delNode(sNode* &h, int r, int s){
    // if the first node in the list should be deleted
    if(r == h->row && s == h->seat){
        // create a holder pointer
        sNode* hold = h;
        // set the header pointer to the next node
        h = h->next;
        // delete the original header pointer
        delete hold;
        return;
    }
    // otherwise...
    else{
        // create a placeholder pointer
        sNode* cur = h;
        // for as long as there is a next item in the list
        while(cur->next){
            // if the next item is the one to be deleted
            if(r == cur->next->row && s == cur->next->seat){
                sNode* hold = cur->next;
                cur->next = cur->next->next;
                delete hold;
                return;
            }
            // otherwise, advance the placeholder pointer
            else
                cur = cur->next;
        }
    }
}


// Display the auditorium state to the user
void dispAud(int n){
    // Start with some space for pretty formatting
    cout << "  ";
    // print the column labels and a newline
    int x = 0;
    for(int l = 0; l < a[n].width; l++){
        cout << label[x];
        x++;
        if(x == 10)
            x = 0;
    }
    cout << endl;

    // reset the label counter
    x = 0;

    // for each row, print the row label...
    for(int r = 1; r < a[n].depth + 1; r++) {
        cout << label[x] << " ";
        x++;
        // reset the label counter
        if (x == 10)
            x = 0;
        // for each seat in the row,
        for (int s = 1; s < a[n].width + 1; s++){
            // if the seat is available, print '#'
            if(findNode(a[n].avHead, r, s))
                cout << '#';
            // otherwise, print '.'
            else
                cout << '.';
        }
        // and a newline
        cout << endl;
    }
}


// Do this before exiting
void onExit(){
    // for each auditorium...
    for(int i = 1; i < 4; i++){
        // write the state of the auditorium to its respective file
        writeAud(i);
        // delete the linked list for each auditorium
        listDestruct(a[i].avHead);
        listDestruct(a[i].occHead);
    }
}


// Write the state of the auditorium to its file
void writeAud(int n){
    // open the file
    ofstream out("A"+to_string(n)+".txt");
    // if the file cannot be opened, end the program
    if(out.bad()){
        cout << "error opening file!";
        exit(0);
    }
    // for each row
    for(int r = 1; r < a[n].depth + 1; r++) {
        // for each seat
        for (int s = 1; s < a[n].width + 1; s++){
            // if the seat is available, write '#' to file
            if(findNode(a[n].avHead, r, s))
                out.put('#');
            // otherwise, write '.' to file
            else
                out.put('.');
        }
        // if this is not the last row, add a newline to file
        if(r != a[n].depth)
            out.put('\n');
    }
    // close the file
    out.close();
}


// search a list for a node
bool findNode(sNode* cur, int r, int s){
    // as long as the node exists....
    while(cur){
        // if this is the desired node, return 'true'
        if(r == cur->row && s == cur->seat)
            return true;
        // otherwise, advance the pointer
        cur = cur->next;
    }
    // the entire list has been searched and the node was not found (cur is nullptr), return 'false'
    return false;
}


// count how many nodes are in a list
int countNode(sNode* cur){
    // initialize the counter variable to 0
    int count = 0;
    // as long as there is a node
    while(cur){
        // count up
        count++;
        // and advance the pointer
        cur = cur->next;
    }
    // return the number of nodes counted
    return count;
}


// ask the user to select an auditorium and return the number
int audSelect(){
    cout << "Choose an auditorium:\n"
         << "1. Auditorium 1\n"
         << "2. Auditorium 2\n"
         << "3. Auditorium 3\n";

    int choice = 0;

    while(choice < 1 || choice > 3){
        cout << "Enter 1, 2, or 3\n";
        choice = getInput();
    }
    return choice;
}


// ask the user to select a seat for a given auditorium
void seatSelect(int n){
    // display the auditorium
    dispAud(n);
    // initialize variables
    int row = 0, seat = 0, num = -1;

    // ask user for the row
    cout << "In which row would you like to sit?\n";
    while(row < 1 || row > a[n].depth){
        cout << "Please choose a number from 1 to "
             << a[n].depth << ".\n";
        row = getInput();
    }

    // ask user for the column (seat)
    cout << "From which seat does your group begin?\n";
    while(seat < 1 || seat > a[n].width){
        cout << "Please choose a number from 1 to "
             << a[n].width << ".\n";
        seat = getInput();
    }

    // ask the user for number of seats
    cout << "How many seats would you like to reserve? (enter 0 to quit)\n";
    while(num < 0){
        cout << "Please choose a number from 0 to "
             << a[n].width - (seat - 1) << ".\n";
        num = getInput();
    }

    // confirmation for compatibility with extra credit. this input not used
    cout << "Confirm selection y/n\n";
    getInput();

    // create a flag as true
    bool available = true;

    // if any seat cannot be found in the "available" list, set flag to false
    for(int i = seat; i < seat + num; i++){
        if(!findNode(a[n].avHead, row, i)) {
            available = false;
        }
    }

    // if the seats were all available
    if(available) {
        // for each seat, add a node to the occupied list and remove one from the available list
        for (int i = seat; i < seat + num; i++){
            addNode(a[n].occHead, row, i);
            delNode(a[n].avHead, row, i);
        }
        // update the auditorium's availability stats
        a[n].av = a[n].av - num;
        a[n].occ = a[n].occ + num;
        // indicate that the seats were reserved
        cout << "Seats reserved!\n";
    }
    // otherwise, indicate that the seats were not reserved
    else {
        cout << "Seats unavailable!\n";
    }
}


// display a report containing the sales for each auditorium and for all
void viewReport(){
    int sales[4][3] = {{0}};                        // initialize a 4x3 array to hold seat sales data
    for(int c = 1; c < 4; c++)
    {
        sales[c - 1][0] = a[c].occ;                 // set the first element to the auditorium's occupied seats
        sales[c - 1][1] = a[c].av;                  // set the second to the auditorium's available seats
        sales[c - 1][2] = 7 * sales[c - 1][0];      // multiply the occupied seats by 7 to get total sales
    }
    for(int c = 0; c < 3; c++)                      // for each column...
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
        for(int c = 0; c < 3; c++)
        {
            cout << " ";
            if(c == 2)
                cout << "$";                        // print a dollar sign to indicate money
            cout << sales[r][c];
        }
        cout << endl;
    }

}


// Get user input and validate it
int getInput(){
    int choice = 0;
    cin >> choice;

    if(!cin.good()){                                        // validate user input
        cin.clear();                                        // clear input stream
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); // purge input stream
        choice = 0;                                         // return predetermined error value
    }
    return choice;
}


// destroy a linked list for memory purposes
void listDestruct(sNode* & h){
    // as long as there is a node to delete
    while(h){
        // create a holder pointer to the node
        sNode* hold = h;
        // move the header pointer to the next node
        h = h->next;
        // delete the original header pointer
        delete[]hold;
    }
    // just in case, delete the pointer
    delete[]h;
}