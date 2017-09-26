//
// Created by Connor on 4/27/2017.
//

#ifndef INC_6_INHERITANCE_AND_POLYMORPHISM_ENCRYPTION_H
#define INC_6_INHERITANCE_AND_POLYMORPHISM_ENCRYPTION_H


#include "FileFilter.h"

class Encryption : FileFilter {
private:
    int key;

public:
    Encryption() {key = 0;};
    Encryption(int k) {key = k;}
    void doFilter(ifstream &in, ofstream &out);
};


#endif //INC_6_INHERITANCE_AND_POLYMORPHISM_ENCRYPTION_H
