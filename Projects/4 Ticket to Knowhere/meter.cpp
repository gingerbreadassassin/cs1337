//
// Created by CNESS on 4/6/2017.
//

#include "meter.h"

// constructors
meter::meter() {
    hourIn = 0;
    minIn = hourIn;
    ship = nullptr;
}

meter::meter(int h, int m, node* s) {
    hourIn = h;
    minIn = m;
    ship = s;
}

// destructor
meter::~meter() {
    hourIn = 0;
    minIn = hourIn;
    ship = nullptr;
}

// accessors
// mutators
void meter::setMinIn(int m) {
    if(m < 60)
        minIn = m;
    else {
        hourIn++;
        minIn = (m - 60);
    }
}