/*
 * Project 1 - Ticket Reservation
 * Authored by Connor Ness -- cdn073000
 *
 * This program emulates a user interface to select seats in a theater which has three
 * auditoriums. It displays the seat availability in the auditoriums and labels the
 * rows and columns so that the user may easily choose a group of seats. All the while,
 * the files containing the auditorium data are not loaded into memory. Rather, the files
 * are read or written to on a character-by-character basis.
 *
 * Note that I did use a 2D vector to achieve this, but the vector is not populated with
 * characters. Instead, it is populated with the byte-wise position of each character in
 * the file. For example, a file might look like this:
 *
 *          ###
 *          ..#
 *
 * Rather than loading the characters themselves into the vector, the vector representing
 * the contents of the file would look like this:
 *
 *          012
 *          567
 *
 * Note that the newline characters are counted, even though they are invisible when
 * viewing the file. They are also not printed from the file when the file's contents
 * are displayed in this program. This program lets the user interact with the visible
 * characters only.
 */

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;


// Function prototypes
void mainMenu();
void dispAud(string auditorium);
string audSelect();
void seatSelect(string auditorium);
void exitFunc();
int getAudDepth(fstream &);
int getAudWidth(fstream &);
int getAudOcc(fstream &);
int getAudAv(fstream &);
int getInput();


// Define the labels globally to save room in functions
int columnLabel[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
int rowLabel[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

// Leave this at 2 if this is a Windows system. Set to 1 otherwise.
int isWindows = 2;

// Set this to 1 if you want to double-click on the exe
int waitOnExit = 0;


int main()
{
    mainMenu();
    return 0;
}

// Display the mainMenu user interface. Note that some IDE's may warn that this function
// recurses infinitely. This is intentional. The only function that should end the
// program is exitFunc(), which is chosen from this mainMenu() loop.
void mainMenu()
{
    cout << "Please choose an option from the menu:\n"
         << "1. Reserve Seats\n"
         << "2. View Auditorium\n"
         << "3. Exit\n";

    int choice;
    choice = getInput();

    switch(choice)
    {
        case 1: seatSelect(audSelect());                    // execute seat selection based on auditorium selection
            mainMenu();
        case 2: dispAud(audSelect());                       // display auditorium based on selection
            mainMenu();
        case 3: exitFunc();                                 // exit the program
        default: cout << "You must enter 1, 2, or 3\n";     // validate user input
            mainMenu();
    }
}


// Display the selected auditorium
void dispAud(string auditorium)
{
    fstream inFile(auditorium);                     // initialize fstream for selected auditorium

    if (!inFile)                                    // check to make sure the file exists
    {
        cerr << "Could not open file." << endl;
        mainMenu();                                     // instead of crashing, return back to mainMenu menu
    }

    int rowDepth, rowWidth;                         // get dimensions of auditorium
    rowDepth = getAudDepth(inFile);
    rowWidth = getAudWidth(inFile);

    vector< vector<int> > seatGrid(rowDepth, vector<int>(rowWidth));

    int byteCount = 0;
    for (int d = 0; d < rowDepth; d++)
    {
        for (int w = 0; w < rowWidth + isWindows; w++)
        {
            seatGrid[d][w] = byteCount;             // enumerate the 2D array with the POSITION of each
            byteCount++;                            // character in the array, not the character itself
        }
    }

    cout << "  ";                                   // add padding for labels
    int x = 0;
    for (int i = 0; i < rowWidth; i++)              // for each column
    {
        cout << columnLabel[x];                     // print labels 1 through 0
        x++;
        if (x == 10)                                // cycle through labels
        {
            x = 0;
        }
    }

    cout << endl;

    int y = 0;
    for (int i = 0; i < rowDepth; i++)              // for each row
    {
        cout << rowLabel[y] << " ";                 // print labels 1 through 0
        y++;
        if (y == 10)                                // cycle through labels
        {
            y = 0;
        }
        for (int p = 0; p < rowWidth; p++)          // for each element in the 2D array
        {
            inFile.seekg(seatGrid[i][p], ios::beg); // seek to the character's position
            cout << (char)inFile.get();             // print that character
        }
        cout << endl;
    }
    inFile.clear();                                 // reset fstream
    inFile.close();                                 // close the file
}


// Let the user choose their auditorium
string audSelect()
{
    cout << "Choose an auditorium:\n"
         << "1. Auditorium 1\n"
         << "2. Auditorium 2\n"
         << "3. Auditorium 3\n";

    int choice;
    choice = getInput();

    switch(choice)
    {
        case 1: return "A1.txt";
        case 2: return "A2.txt";
        case 3: return "A3.txt";
        default: cout << "You must enter 1, 2, or 3\n";     // verify their input
            return audSelect();
    }
}


// Let the user choose which seats to reserve in the selected auditorium
void seatSelect(string auditorium)
{
    dispAud(auditorium);                            // display the selected auditorium
    fstream inFile(auditorium);                     // initialize fstream for selected auditorium

    if (!inFile)                                    // check to make sure the file exists
    {
        cerr << "Could not open file." << endl;
        mainMenu();                                     // instead of crashing, return back to mainMenu menu
    }

    int rowDepth, rowWidth;                         // get dimensions of auditorium
    rowDepth = getAudDepth(inFile);
    rowWidth = getAudWidth(inFile);

    vector< vector<int> > seatGrid(rowDepth, vector<int>(rowWidth));

    int byteCount = 0;
    for (int d = 0; d < rowDepth; d++)
    {
        for (int w = 0; w < rowWidth + isWindows; w++)
        {
            seatGrid[d][w] = byteCount;             // enumerate the 2D array with the POSITION of each
            byteCount++;                            // character in the array, not the character itself
        }
    }

    int numSeats = 0;
    int colChoice = 0;
    int rowChoice = 0;

    cout << endl << "Choose a row: ";               // ask the user which row they want to sit in
    rowChoice = getInput();

    while(rowChoice < 1 || rowChoice > rowDepth)    // validate their input
    {
        cout << "Sorry, you chose a row that does not exist.\n"
             << "Please choose a valid row: ";
        rowChoice = getInput();
    }

    cout << endl << "Choose a column: ";            // ask the user which column containing their first seat
    colChoice = getInput();

    while(colChoice < 1 || colChoice > rowWidth)    // validate their input
    {
        cout << "Sorry, you chose a seat that does not exist.\n"
             << "Please choose a valid column: ";
        colChoice = getInput();
    }

    cout << "How many seats? (enter zero or any letter "
            "or special character to exit): ";      // ask the user how many seats they want
    numSeats = getInput();

    while((numSeats + colChoice - 1) > rowWidth)    // validate their input
    {
        cout << "Sorry, you cannot choose more seats than\n"
             << "exist in the row. How many seats\n"
             << "would you like to reserve? ";
        numSeats = getInput();
    }
    while(numSeats < 0)                             // validate their input
    {
        cout << "Please enter a non-negative number. ";
        numSeats = getInput();
    }

    char ch = '#';
    char c = '.';
    for (int i = 0; i < numSeats; i++)              // make sure the user's selected seats are available
    {
        inFile.seekg(seatGrid[rowChoice - 1][colChoice + i - 1], ios::beg); // start at beginning of file
        inFile.get(ch);                             // read each character, one at a time
        if(ch == c)                                 // if a selected seat is occupied, ask for a different selection
        {
            cout << "One or more of your seats is already occupied.\n"
                 << "Please make another selection.\n";
            inFile.clear();                         // clear any bad state bits that might have been set
            inFile.close();                         // close the file
            seatSelect(auditorium);                 // go back to the beginning of this function
        }
    }

    if(inFile.bad())                                // check if fstream is in bad state
        inFile.clear();                             // reset it if it is

    for(int i = 0; i < numSeats; i++)               // if the program reaches this point, the seats are open
    {
        inFile.seekp(seatGrid[rowChoice - 1][colChoice + i - 1], ios::beg); // seek to the beginning seat
        inFile.put(c);                              // and overwrite # with . for selected seats
    }

    inFile.clear();                                 // reset the fstream
    inFile.close();                                 // close the file
}


// when exiting, display current sales figures
void exitFunc()
{
    int sales[4][3] = {{0}};                        // initialize a 4x3 array to hold seat sales data
    for(int c = 1; c < 4; c++)
    {
        fstream inFile("A"+to_string(c)+".txt");    // open each file
        sales[c - 1][0] = getAudOcc(inFile);        // set the first value to the auditorium's occupied seats
        sales[c - 1][1] = getAudAv(inFile);         // set the second to t he auditorium's available seats
        sales[c - 1][2] = 7 * sales[c - 1][0];      // multiply the occupied seats by 7 to get total sales
        inFile.close();                             // close each file
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

    if(waitOnExit == 1)
    {
        cout << "Press enter to exit.";                 // wait for user to press enter to exit
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin.get();
    }
    exit(0);
}


// Get auditorium depth in seats
int getAudDepth(fstream & in)
{
    string line;
    int rowDepth = 0;
    in.seekg(0, ios::beg);      // seek to beginning of the file
    while(getline(in, line))    // Increment a counter each time a newline is found until EOF
        rowDepth++;
    in.clear();                 // reset fstream before returning
    return rowDepth;            // return the "depth", or the number of rows in the auditorium
}


// Get auditorium width in seats
int getAudWidth(fstream & in)
{
    string line;
    in.seekg(0, ios::beg);      // seek to beginning of the file
    getline(in, line);          // get the first line of the file and store as string
    in.clear();                 // reset fstream before returning
    return (int)line.length();  // return the integer representation of the length of string
}


// Get auditorium occupancy
int getAudOcc(fstream &in)
{
    in.seekg(0, ios::beg);      // seek to beginning of the file
    char ch;
    int dot = 0;
    do
    {
        in.get(ch);             // read through the file one character at a time
        if(ch == '.')           // if character == dot, increment counter
            dot++;
    }while(in.good());          // until fstream is no longer in a good state
    in.clear();                 // reset fstream before returning
    return dot;                 // return number of available seats
}


// Get auditorium availability
int getAudAv(fstream &in)
{
    in.seekg(0, ios::beg);      // seek to beginning of the file
    char ch;
    int hash = 0;
    do
    {
        in.get(ch);             // read through the file one character at a time
        if(ch == '#')           // if character == hashtag, increment counter
            hash++;
    }while(in.good());          // until fstream is no longer in a good state
    in.clear();                 // reset fstream before returning
    return hash;                // return number of available seats
}


// Get user input and validate it
int getInput()
{
    int choice = 0;
    cin >> choice;

    if(!cin.good())                                         // validate user input
    {
        cin.clear();                                        // clear input stream
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); // purge input stream
        choice = 0;                                         // return predetermined error value
    }
    return choice;
}