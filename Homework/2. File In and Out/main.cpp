/*
 * This program extracts vowels from a user-defined text file. It requests the
 * name of the file from the user, then appends all the vowels into another
 * file of the same name but with a "vowel_" prefix. Because newline
 * characters behave differently in Windows, it also asks the user if they
 * are running the program in a Windows environment. All of this is done
 * with a single filestream (only one file is open at any given time).
 */

#include <iostream>
#include <fstream>

using namespace std;

// Function prototypes in order of use
string getFile();
bool isWindows();
int getFileLen(string fileName);
char getChar(fstream &, int position);
bool checkVowel(char ch);
void putChar(fstream &, char c);


/*
 * The main function keeps track of its position in the file from which the
 * vowels are being read, while handling user I/O. It initializes several
 * variables, then asks the user for the name of the file. Once the file
 * name is obtained, it asks the user if they are running Windows. It then
 * opens a filestream, gets the length of the file in bytes, and reads through
 * the file. When it finds a vowel, it copies the letter, preserving the case,
 * into the vowel file. When it finds a line break, it inserts a line break
 * into the vowel file. Finally, it adds a line break to the end of the
 * vowel file, so that when appending to the file, two lines of vowels
 * don't run together.
 */
int main() {
    string inFileName, outFileName;
    char ch;
    int inFilePos = 0,                              // to track byte position
        fileLength = 0;                             // to stop writing
    bool windows;

    inFileName = getFile();
    outFileName = "vowels_" + inFileName;

    windows = isWindows();

    fstream fs;
    fileLength = getFileLen(inFileName);
    while(inFilePos < fileLength)
    {
        fs.open(inFileName, ios::in);               // open input file
        ch = getChar(fs, inFilePos);                // get character from file
        inFilePos++;                                // count position
        if(checkVowel(ch))                          // check if ch is a vowel
        {
            fs.open(outFileName, ios::app);         // append to output file
            putChar(fs, ch);                        // put character into file
        }
        if(ch == '\n')                              // check for line break
        {
            fs.open(outFileName, ios::app);
            fs << endl;                             // print new line
            fs.close();
            if(windows)                             // if windows:
            {
                inFilePos++;                        // count position twice
            }
        }
    }
    fs.open(outFileName, ios::app);
    fs << endl;
    fs.close();
    return 0;
}


/*
 * The getFile function asks the user for the name of the file from which
 * they want to extract the vowels. It checks if the file opens
 * successfully. If it does, it returns the known good filename to the
 * main function for use as the input file. If it does not, it keeps
 * bugging the user for a valid file. The filestream in this function
 * is opened and closed before the main function creates another.
 */
string getFile()
{
    string fileName;
    cout << "Please enter the name of a text file"
         << " from which you wish to extract the"
         << " vowels: ";
    getline(cin, fileName);

    fstream fs;
    fs.open(fileName, ios::in);


    while (fs.fail())
    {
        cout << endl << "Error opening file! \n";
        cout << "Please enter the name of a text"
             << " file from which you wish to"
             << " extract the vowels: ";
        getline(cin, fileName);
        fs.open(fileName, ios::in);
    }
    fs.close();
    return fileName;
}


/*
 * The isWindows function asks the user whether they are running on a Windows
 * operating system. If the user enters anything other than the requested
 * Y or N letters, it calls itself again. If the user is running Windows,
 * the main function will ignore the redundant new line character that
 * Microsoft thought was so important.
 */
bool isWindows()
{
    cout << "Are you running Windows? Y/N: ";
    char resp;
    cin >> resp;
    cout << endl;
    resp = char(tolower(resp));                     // converts to lowercase
    if(resp == 'y')
    {
        return true;
    }
    else if(resp == 'n')
    {
        return false;
    }
    else
    {
        cout << "Please use Y or N." << endl;
        isWindows();
    }
    return false;                                   // to avoid IDE warning
}


/*
 * The getFileLen function reads through the source file byte-by-byte,
 * and counts how many there are. It opens the source file in binary
 * to avoid odd compiler behavior.
 */
int getFileLen(string fileName)
{
    fstream fs;
    fs.open(fileName, ios::in|ios::binary);
    int fileSize = 0;
    do
    {
        fs.get();
        fileSize++;
    }while(fs);
    fs.close();
    return fileSize;
}


/*
 * The getChar function inherits a filestream and byte position from
 * the main function. It grabs the letter at this position and
 * returns it to the main function after closing the filestream.
 */
char getChar(fstream & inFile, int position)
{
    char ch;
    inFile.seekg(position, ios::beg);
    inFile.get(ch);
    inFile.close();
    return ch;
}


/*
 * The checkVowel function does exactly what its name implies. It
 * converts the letter to lowercase (to make my life easier) and
 * returns a true or false value to the main function, depending
 * on whether the letter is indeed a vowel.
 */
bool checkVowel(char ch)
{
    ch = char(tolower(ch));
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}


/*
 * The putChar function inherits a filestream and a letter from
 * the main function. It writes the letter to the file and then
 * closes the filestream.
 */
void putChar(fstream &  outFile, char ch)
{
    outFile.put(ch);
    outFile.close();
}
