//
// Created by CNESS on 4/6/2017.
//

#include "ticket.h"

// constructors
ticket::ticket() {
    ticket::setNode(nullptr);
    ticket::setMeter(nullptr);
    ticket::setHourOut(0);
    ticket::setMinOut(0);
}
ticket::ticket(node* n, meter* m, int H, int M){
    ticket::setNode(n);
    ticket::setMeter(m);
    ticket::setHourOut(H);
    ticket::setMinOut(M);
}

// destructor
ticket::~ticket() {
    ticket::setNode(nullptr);
    ticket::setMeter(nullptr);
    ticket::setHourOut(0);
    ticket::setMinOut(0);
}

// accessors

// mutators