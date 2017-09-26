//
// Created by CNESS on 4/6/2017.
//

#include "node.h"

// constructors
node::node(string n, string i, int c) {
    name = n;
    ID = i;
    credit = c;
    next = nullptr;
}
// destructor
node::~node() {
    name = "";
    ID = name;
    credit = 0;
    next = nullptr;
}
// accessors
// mutators