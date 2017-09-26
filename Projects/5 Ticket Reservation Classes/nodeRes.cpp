//
// Created by CNESS on 4/24/2017.
//

#include "nodeRes.h"

nodeRes::nodeRes(int row, int seat) : node(row,seat) {
    next = last = nullptr;
}

nodeRes::nodeRes(int row, int seat, bool isRes) : node(row, seat) {
    isReserved = isRes;
    next = last = nullptr;
}

ostream& operator <<(ostream &out, const nodeRes *node) {
    if(node->isReserved)
        out << ".";
    else
        out << "#";
    return out;
}

ofstream& operator <<(ofstream &oFile, const nodeRes *node) {
    if(node->isReserved)
        oFile.put('.');
    else
        oFile.put('#');
    return oFile;
}

ifstream& operator >>(ifstream &iFile, nodeRes *node) {
    char ch = 'x';
    while(!iFile.eof() && ch != '#' && ch != '.')
        iFile.get(ch);
    if(ch == '#')
        node->isReserved = false;
    else if(ch == '.') {
        node->isReserved = true;
    }
    return iFile;
}