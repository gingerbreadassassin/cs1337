//
// Created by Connor on 4/27/2017.
//

#ifndef INC_6_INHERITANCE_AND_POLYMORPHISM_FILEFILTER_H
#define INC_6_INHERITANCE_AND_POLYMORPHISM_FILEFILTER_H

#include <fstream>
using namespace std;

class FileFilter {
public:
    virtual void doFilter(ifstream &in, ofstream &out) = 0;

};


#endif //INC_6_INHERITANCE_AND_POLYMORPHISM_FILEFILTER_H
