//
// Created by CNESS on 4/6/2017.
//

#ifndef INC_4_TICKET_TO_KNOWHERE_LINKEDLIST_H
#define INC_4_TICKET_TO_KNOWHERE_LINKEDLIST_H

#include <string>
#include "node.h"
using namespace std;

/*
 * linkedList class creates and manages a linked list. When instantiated,
 * a node pointer named head is created, and points to null (this can be
 * overloaded with an existing node, if desired). A node can be appended
 * to an existing list with the "append" mutator. The first node in the
 * list can be removed with the "removeFirst" mutator. The first node
 * in the list may be accessed with the "getFirst" accessor. When the
 * list is destroyed (scope of instantiation closes, deleted, etc.), the
 * destructor cycles through each node in the list and deletes it, before
 * deleting the head pointer.
 */
class linkedList {
private:
    node* head;

public:
    // constructors
    linkedList(){head = nullptr;}
    linkedList(node*);
    // destructor
    ~linkedList();
    // accessors
    node* getFirst(){return head;}
    // mutators
    void append(node*);
    void removeFirst();

};


#endif //INC_4_TICKET_TO_KNOWHERE_LINKEDLIST_H
