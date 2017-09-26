//
// Created by CNESS on 4/6/2017.
//

#ifndef INC_4_TICKET_TO_KNOWHERE_TICKET_H
#define INC_4_TICKET_TO_KNOWHERE_TICKET_H
#include "node.h"
#include "meter.h"
using namespace std;

/*
 * The ticket class keeps track of departure times
 * for each ship. The getTimeDiff accessor function
 * returns an integer value representing the difference
 * in time between docking and departure and the credit
 * that the ship paid for.
 */

class ticket {
private:
    node* ship;
    meter* dockingBay;
    int hourOut, minOut;

public:
    // constructors
    ticket();
    ticket(node*, meter*, int, int);

    // destructor
    ~ticket();

    // accessors
    int getTimeDiff() {
        return (((hourOut*60 + minOut)-((dockingBay->getHourIn()*60)+dockingBay->getMinIn()))-ship->getCredit());
    }
    node* getNode(){return ship;}
    meter* getMeter(){return dockingBay;}
    int getHourOut(){return hourOut;}
    int getMinOut(){return minOut;}

    // mutators
    void setNode(node* s){ship = s;}
    void setMeter(meter* d){dockingBay = d;}
    void setHourOut(int h){hourOut = h;}
    void setMinOut(int m){minOut = m;}
};


#endif //INC_4_TICKET_TO_KNOWHERE_TICKET_H
