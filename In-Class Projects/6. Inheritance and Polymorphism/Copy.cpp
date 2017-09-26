//
// Created by Connor on 4/27/2017.
//

#include "Copy.h"

void Copy::doFilter(ifstream &in, ofstream &out) {
    in.open("test.txt");
    out.open("Copy.txt", ios::app);
    char ch;
    while(in.get(ch))
        out.put(ch);
    in.clear();
    in.close();
    out.clear();
    out.close();
}