//
// Created by Connor on 4/27/2017.
//

#include "Uppercase.h"

char Uppercase::transform(char ch) {
    if(ch >= 97 && ch <= 122)
        ch -= 32;
    return ch;
}

void Uppercase::doFilter(ifstream &in, ofstream &out) {
    in.open("test.txt");
    out.open("Uppercase.txt", ios::app);
    char ch;
    while(in.get(ch)){
        ch = transform(ch);
        out.put(ch);
    }
    in.clear();
    in.close();
    out.clear();
    out.close();
}