//
// Created by Connor on 4/27/2017.
//

#ifndef INC_6_INHERITANCE_AND_POLYMORPHISM_UPPERCASE_H
#define INC_6_INHERITANCE_AND_POLYMORPHISM_UPPERCASE_H

#include "FileFilter.h"

class Uppercase : FileFilter{
public:
    Uppercase(){return;}
    char transform(char ch);
    void doFilter(ifstream &in, ofstream &out);
};


#endif //INC_6_INHERITANCE_AND_POLYMORPHISM_UPPERCASE_H
