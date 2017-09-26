//
// Created by CNESS on 4/6/2017.
//

#ifndef INC_4_TICKET_TO_KNOWHERE_METER_H
#define INC_4_TICKET_TO_KNOWHERE_METER_H

#include "node.h"
using namespace std;

/*
 * The meter class keeps track of arrival times for each
 * ship. The node pointer attaches a ship to the meter.
 */

class meter {
private:
    int hourIn, minIn;
    node* ship;

public:
    // constructors
    meter();
    meter(int, int, node*);

    // destructor
    ~meter();

    // accessors
    int getHourIn(){return hourIn;}
    int getMinIn(){return minIn;}
    node* getShip(){return ship;}

    // mutators
    void setHourIn(int h){hourIn = h;}
    void setMinIn(int);
    void setShip(node* s){ship = s;}
};


#endif //INC_4_TICKET_TO_KNOWHERE_METER_H
