//
// Created by CNESS on 4/6/2017.
//

#include "linkedList.h"

// constructors
linkedList::linkedList(node* nu){
    append(nu);
}
// destructor deletes the entire list
linkedList::~linkedList() {
    while(head && head->getNext()){
        node* hold = head;
        head = head->getNext();
        delete hold;
    }
    delete head;
}

// accessors

// mutators
void linkedList::append(node* nu){
    if(!head){
        head = nu;
    }
    else if(!head->getNext()){
        head->setNext(nu);
    }
    else{
        node* cur = head;
        while(cur->getNext())
            cur = cur->getNext();
        cur->setNext(nu);
    }
}

// removing the first node does not delete the node
// as that would lose the ship
void linkedList::removeFirst() {
    if(!head){
        return;
    }
    else if(!(head->getNext())){
        head = nullptr;
    }
    else{
        node* hold = head;
        head = head->getNext();
        hold->setNext(nullptr);
    }
}