//
// Created by CNESS on 4/6/2017.
//

#ifndef INC_4_TICKET_TO_KNOWHERE_NODE_H
#define INC_4_TICKET_TO_KNOWHERE_NODE_H

#include <string>
using namespace std;

/*
 * The node class defines an object that will be added to a
 * linked list. In this application, the node represents
 * a spaceship. Each node has a name, an ID, an int
 * representing the amount of paid time, and a pointer to
 * the next node in the list.
 */

class node {
private:
    string name;
    string ID;
    int credit;
    node* next = nullptr;

public:
    // constructors
    node(){"", "", 0, nullptr;}
    node(string name, string ID, int credit);

    // destructor
    ~node();

    // accessors
    node* getNext(){return next;}
    string getName(){return name;}
    string getID(){return ID;}
    int getCredit(){return credit;}

    // mutators
    void setNext(node* nu){next = nu;}
    void setName(string n){name = n;}
    void setID(string i){ID = i;}
    void setCredit(int c){credit = c;}

};


#endif //INC_4_TICKET_TO_KNOWHERE_NODE_H
