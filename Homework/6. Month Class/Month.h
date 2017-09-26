//
// Created by CNESS on 4/17/2017.
//

#ifndef INC_6_MONTH_CLASS_MONTH_H
#define INC_6_MONTH_CLASS_MONTH_H

#include <string>
#include <iostream>

using namespace std;

class Month {
private:
    string name;
    int monthNumber;
    string julian[13] = {"foo", "January", "February", "March", "April", "May", "June",
                         "July", "August", "September", "October", "November", "December"};
    int searchArr(string);
    bool inValA(string);

public:
    // constructors
    Month(){name = "January", monthNumber = 1;}
    Month(string nom){setMonthA(nom);}
    Month(int j){setMonthN(j);}
    Month(const Month &obj){name = obj.name, monthNumber = obj.monthNumber;}
    // accessors
    string getMonthA(){return name;}
    int getMonthN(){return monthNumber;}
    friend ostream& operator<<(ostream &, const Month &);
    // mutators
    void setMonthA(string);
    void setMonthN(int);
    Month operator++();
    Month operator++(int);
    Month operator--();
    Month operator--(int);
    friend istream& operator>>(istream &, Month &);

};


#endif //INC_6_MONTH_CLASS_MONTH_H
