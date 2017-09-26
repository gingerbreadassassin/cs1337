//
// Created by CNESS on 4/24/2017.
//

#ifndef INC_5_TICKET_RESERVATION_CLASSES_NODE_H
#define INC_5_TICKET_RESERVATION_CLASSES_NODE_H


class node {

protected:
    int row, seat;

public:
    // constructors
    node(){row = seat = 0;}
    node(int r, int s) {row = r, seat = s;}

    // destructor

    // accessors
    virtual int getRow() = 0;
    int getSeat() {return seat;}

    // mutators
    void setRow(int r) {row = r;}
    void setSeat(int s) {seat = s;}

};


#endif //INC_5_TICKET_RESERVATION_CLASSES_NODE_H
