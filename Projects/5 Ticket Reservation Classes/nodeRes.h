//
// Created by CNESS on 4/24/2017.
//

#ifndef INC_5_TICKET_RESERVATION_CLASSES_NODERES_H
#define INC_5_TICKET_RESERVATION_CLASSES_NODERES_H

#include <string>
#include <iostream>
#include <fstream>
#include "node.h"
using namespace std;

class nodeRes : public node {
private:
    bool isReserved;
    nodeRes *next, *last;

public:
    // constructors
    nodeRes() {next = last = nullptr;}
    nodeRes(int row, int seat);
    nodeRes(int row, int seat, bool isRes);

    // destructor


    // accessors
    nodeRes* getNext(){return next;}
    nodeRes* getPrev(){return last;}
    bool getRes(){return isReserved;}
    int getRow() {return row;}

    friend ostream& operator <<(ostream&, const nodeRes*);
    friend ofstream& operator <<(ofstream&, const nodeRes*);

    // mutators
    void setNext(nodeRes* nu){next = nu;}
    void setLast(nodeRes* nu){last = nu;}
    void setRes(){isReserved = true;}

    friend ifstream& operator >>(ifstream&, nodeRes*);

};


#endif //INC_5_TICKET_RESERVATION_CLASSES_NODERES_H
