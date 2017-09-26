//
// Created by Connor on 4/27/2017.
//

#ifndef INC_6_INHERITANCE_AND_POLYMORPHISM_COPY_H
#define INC_6_INHERITANCE_AND_POLYMORPHISM_COPY_H


#include "FileFilter.h"

class Copy : FileFilter {
public:
    Copy() {return;}
    void doFilter(ifstream &in, ofstream &out);
};


#endif //INC_6_INHERITANCE_AND_POLYMORPHISM_COPY_H
