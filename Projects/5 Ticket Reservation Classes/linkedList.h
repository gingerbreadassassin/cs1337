//
// Created by CNESS on 4/24/2017.
//

#ifndef INC_5_TICKET_RESERVATION_CLASSES_LINKEDLIST_H
#define INC_5_TICKET_RESERVATION_CLASSES_LINKEDLIST_H

#include <string>
#include "nodeRes.h"
using namespace std;

class linkedList {
private:
    int length = 0;
    nodeRes *head, *tail;


public:
    // constructors
    linkedList(){head = tail = nullptr;}
    linkedList(nodeRes*);

    // destructor
    ~linkedList();

    // accessors
    nodeRes* getFirst(){return head;}
    nodeRes* getLast(){return tail;}
    nodeRes* getIndex(int index);
    nodeRes* operator[](int i){return getIndex(i);}
    int len(){return length;}

    // mutators
    void append(nodeRes*);
    linkedList* operator+=(nodeRes* node)
    {append(node); return this;}

};


#endif //INC_5_TICKET_RESERVATION_CLASSES_LINKEDLIST_H
