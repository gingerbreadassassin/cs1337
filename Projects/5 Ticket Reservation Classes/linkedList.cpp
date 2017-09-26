//
// Created by CNESS on 4/24/2017.
//

#include "linkedList.h"

linkedList::linkedList(nodeRes* nu){
    append(nu);
}
// destructor deletes the entire list
linkedList::~linkedList() {
    while(head && head->getNext()){
        nodeRes* hold = head;
        head = head->getNext();
        delete hold;
    }
    delete head;
}

// accessors
nodeRes* linkedList::getIndex(int index) {
    nodeRes* cur = head;
    if(!head)
        return nullptr;
    else if(head == tail && index != 0)
        return nullptr;
    else {
        while(index > 0 && cur->getNext()) {
            cur = cur->getNext();
            index--;
        }
    }
    return cur;
}

// mutators
void linkedList::append(nodeRes* nu){
    if(!head){
        head = nu;
        tail = nu;
    }
    else if(!head->getNext()){
        head->setNext(nu);
        tail = nu;
        tail->setLast(head);
    }
    else{
        nodeRes* cur = head;
        while(cur->getNext())
            cur = cur->getNext();
        cur->setNext(nu);
        tail = nu;
        tail->setLast(cur);
    }
    length++;
}
