//
// Created by Connor on 4/27/2017.
//

#include "Encryption.h"

void Encryption::doFilter(ifstream &in, ofstream &out) {
    in.open("test.txt");
    out.open("Encrypted.txt", ios::app);
    char ch;
    while(in.get(ch)){
        char ck = ch + key;
        if(ck >= 32 && ck <= 126){
            out.put(ck);
        }
        else if(ck < 32){
            ck = (ck % 95) + 95;
            out.put(ck);
        }
        else {
            ck = (ck % 95);
            out.put(ck);
        }
    }
    in.clear();
    in.close();
    out.clear();
    out.close();
}