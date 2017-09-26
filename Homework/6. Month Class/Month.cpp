//
// Created by CNESS on 4/17/2017.
//

#include <limits>
#include "Month.h"

// accessors
ostream& operator << (ostream & out, const Month & obj) {
    out << obj.name << " " << obj.monthNumber << endl;
    return out;
}

int Month::searchArr(string nom){
    for(int i = 1; i < 13; i++) {
        if(nom == julian[i])
            return i;
    }
    return -1;
}

// mutators
void Month::setMonthA(string nom){
    if(inValA(nom)){
        name = nom;
        monthNumber = searchArr(nom);
    }
    else {
        cout << "Month not found!" << endl;
        name = "January";
        monthNumber = 1;
    }
}

void Month::setMonthN(int j) {
    if(j > 0 && j < 13) {
    name = julian[j];
    monthNumber = j;
    }
    else{
        cout << "Invalid month number!" << endl;
        name = "January";
        monthNumber = 1;
    }
}

Month Month::operator++() {
    if(monthNumber == 12)
        setMonthN(1);
    else
        setMonthN(monthNumber+1);
    return *this;
}

Month Month::operator++(int) {
    Month temp = *this;
    if(monthNumber == 12)
        setMonthN(1);
    else
        setMonthN(monthNumber+1);
    return temp;
}

Month Month::operator--() {
    if(monthNumber == 1)
        setMonthN(12);
    else
        setMonthN(monthNumber+1);
    return *this;
}

Month Month::operator--(int) {
    Month temp(*this);
    if(monthNumber == 1)
        setMonthN(12);
    else
        setMonthN(monthNumber-1);
    return temp;
}

istream& operator>>(istream & in, Month & obj) {
    int choice = 0;
    string nom;

    cout << "Enter the name of the month: ";

    in >> nom;
    if(!in.good()){
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input!" << endl;
        return in;
    }

    if(!obj.inValA(nom)){
        cout << "Invalid input!" << endl;
        return in;
    }

    cout << "Enter the number of the month: ";

    in >> choice;
    if(!in.good()){
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input!" << endl;
        return in;
    }

    if(choice == obj.searchArr(nom)){
        obj.name = nom;
        obj.monthNumber = choice;
    }
    else
        cout << "The name and number you entered do not match!" << endl;

    return in;
}

// doers
bool Month::inValA(string nom) {
    if(searchArr(nom) < 1)
        return false;
    return true;
}