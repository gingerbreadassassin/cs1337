/*
 * Connor Ness - cdn073000
 * Homework 4 - Linked List Queue
 * March 6, 2017
 *
 * This program simulates a customer/client queue handled via a linked list. The two
 * main functions, nQ and dQ, add or remove nodes from the list, respectively. Each
 * node created has a unique ID associated with it. This ID increments with each
 * successive node. IDs are not recycled.
 */

#include <iostream>
#include <limits>

using namespace std;


struct client{
    int x;
    client* next;
};


void mainMenu(client* &, int &);
void addClient(client* &, int &);
void removeClient(client* &);
void nQ(int, client* &);
void dQ(client* &);
void showQ(client*);
void listDestruct(client* &);
int getInput();


int main(){
    // create a unique number which will increment for each new node
    int clientID = 1;
    // create the head pointer
    client* head;
    head = nullptr;
    // run the mainMenu function
    mainMenu(head, clientID);
    return 0;
}


// the program will return to the main menu until the user wishes to exit
void mainMenu(client* & h, int & ID) {
    cout << "Select an item from the menu using the item's number.\n"
         << "1. Add to Queue\n"
         << "2. Remove from Queue\n"
         << "3. Display Queue\n"
         << "4. Exit\n";

    int choice = getInput();

    switch(choice){
        case 1: addClient(h, ID);
            mainMenu(h, ID);
        case 2: removeClient(h);
            mainMenu(h, ID);
        case 3: showQ(h);
            mainMenu(h, ID);
        case 4: listDestruct(h);
            exit(0);
        default: cout << "You must enter 1, 2, 3, or 4\n";
            mainMenu(h, ID);
    }
}


// handler to add a specified number of nodes to the list
void addClient(client* & h, int & ID){
    cout << "How many items would you like to add?\n";

    int items = -1;
    while(items < 0){
        cout << "Please enter a number 0 or greater.\n";
        items = getInput();
    }

    for(int i =0; i < items; i++)
        nQ(ID++, h);
    showQ(h);
}


// handler to remove a specified number of nodes from the list.
void removeClient(client* & h){
    // if list is empty, tell the user
    if(h == nullptr){
        cout << "There is nothing to deQueue!\n";
    }
    else {
        cout << "How many items would you like to remove?\n";

        int items = -1;
        while(items < 0){
            cout << "Please enter a number 0 or greater.\n";
            items = getInput();
        }

        // as long as there is a node to delete, delete requested number of nodes
        int i = 0;
        while (h != nullptr && i < items) {
            dQ(h);
            i++;
        }
    }
    showQ(h);
}


// create new node at end of list with given number. No modification of head pointer needed.
void nQ(int i, client* &h){
    // create the new node
    client* newClient;
    newClient = new client;
    // set new node's number as specified and next pointer to null
    newClient->x = i;
    newClient->next = nullptr;

    if(h == nullptr){
        h = newClient;
    }
    else {
        // create "current" pointer to traverse list, set to head pointer
        client *cur;
        cur = h;
        // move cur to next node until next node is null
        while (cur->next != nullptr)
            cur = cur->next;
        // set next node to the new node
        cur->next = newClient;
    }
}


// remove the first element from the Queue. Pass by reference so that head pointer is modified
void dQ(client* & h){
    if(h->next == nullptr){
        cout << "The last client, " << h->x << " removed from the Queue!\n";
        // create holder node so that node may be deleted after head pointer is modified
        client* hold;
        hold = h;
        // set head pointer to null
        h = nullptr;
        // delete the only remaining node in the list
        delete[]hold;
    }
    else {
        cout << "Client " << h->x << " removed from Queue!\n";
        // create holder node so that node may be deleted after head pointer is modified
        client *hold;
        hold = h;
        // change the head pointer to the second node in list
        h = h->next;
        // delete the first node in list
        delete[]hold;
    }
}


// print the current Queue
void showQ(client* h){
    while(h != nullptr){
        cout << h->x;
        if(h->next != nullptr)
            cout << ", ";
        h = h->next;
    }
    cout << "\n";
}


// delete all nodes in a list
void listDestruct(client* & h){
    while(h != nullptr){
        client* hold;
        hold = h;
        h = h->next;
        delete[]hold;
    }
    delete[]h;
}


// validate that user input is an integer
int getInput(){
    int choice;

    cin >> choice;

    if(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        choice = 0;
    }
    return choice;
}
