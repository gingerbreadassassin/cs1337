/*
 * Connor Ness - cdn073000
 * CS 1337.007
 * Homework 5 - C Strings
 */

#include <iostream>
#include <cstring>

using namespace std;

char *inputStr(){
    string input;
    getline(cin, input);
    char *outp = new char[input.length()];
    strcpy(outp, input.c_str());
    return outp;
}

void namePrint(){
    cout << "Please type your first name: ";
    char* first = inputStr();
    cout << "Please type your middle name: ";
    char* middle = inputStr();
    cout << "Please type your last name: ";
    char* last = inputStr();
    char* whole = new char[strlen(first)+strlen(middle)+strlen(last)+4];
    strcpy(whole, last);
    strcat(whole, ", ");
    strcat(whole, first);
    strcat(whole, " ");
    strcat(whole, middle);
    for(int i = 0; i < strlen(whole); i++)
        cout << whole[i];
    cout << '\n';
}

int passwd(){
    cout << "Please enter a password (6-14 characters long, at least one of: "
            "\n uppercase, lowercase, digit, punctuation: ";
    char *pw = inputStr();

    if(strlen(pw) < 6){
        cout << "Password too short!\n";
        return 0;
    }
    else if(strlen(pw) > 14){
        cout << "Password too long!\n";
        return 0;
    }
    bool upper = false, lower = false, digit = false, punc = false;
    for(int i = 0; i < strlen(pw); i++){
        if(isupper(pw[i]))
            upper = true;
        else if(islower(pw[i]))
            lower = true;
        else if(isdigit(pw[i]))
            digit = true;
        else if(ispunct(pw[i]))
            punc = true;
        else{
            cout << "You have entered and invalid character!\n";
                 return 0;
        }
    }
    if(upper && lower && digit && punc)
        return 1;
    else{
        if(!upper)
            cout << "Need uppercase letter!\n";
        if(!lower)
            cout << "Need lowercase letter!\n";
        if(!digit)
            cout << "Need digit!\n";
        if(!punc)
            cout << "Need punctuation!\n";
        return 0;
    }
}

int main() {
    namePrint();
    int pass = 0;
    while(!pass)
        pass = passwd();
    return 0;
}

