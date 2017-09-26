/*
 * Connor Ness - cdn073000
 * Project 4 - Ticket to Knowhere
 * CE1337.007
 * April 9 2017
 *
 * This program simulates an intergalactic space station capable of docking
 * only 10 ships at a time. Input is read from "Knowhere.dat" and if a
 * ship stays past its purchased time, it is issued a fine for 2000 credits
 * per minute over.
 *
 * This program makes use of linked lists and classes. An array of objects
 * is used to represent the docking bays.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "linkedList.h"
#include "node.h"
#include "meter.h"
#include "ticket.h"

using namespace std;

void makeNode(node &, string, string, string);
void writeTicket(ticket*);

int main() {

    // open input file, validate
    fstream inFile;
    inFile.open("Knowhere.dat", ios::in);
    if(!inFile){
        cout << "Failed to open file!";
        return -1;
    }

    // create an array of meter pointers to represent the docking bays
    meter* dockingBay[10];
    for(int i = 0; i < 10; i++)
        dockingBay[i] = new meter;

    // instantiate the linked list queue
    linkedList queue;

    // while there is a line to read in the file
    while(!inFile.eof()){
        // set up necessary variables
        string action = "";
        string hour = "";
        string minute = "";
        string sName = "";
        string sID = "";
        string credit = "";

        // determine whether a ship is arriving or departing
        getline(inFile, action, ' ');

        // if a ship enters
        if(action == "enter") {
            // populate the variables with the ship's information
            getline(inFile, hour, ':');
            getline(inFile, minute, ' ');
            getline(inFile, sName, ' ');
            getline(inFile, sID, ' ');
            getline(inFile, credit);
            // create a node to represent the ship
            node *ship = new node;
            makeNode(*ship, sName, sID, credit);
            // place the ship in the queue
            queue.append(ship);
        }

        // if a ship leaves
        else if(action == "exit"){
            // populate the variables with the ship's information
            getline(inFile, sID, ' ');
            getline(inFile, hour, ':');
            getline(inFile, minute);
            // find the docking bay where the ship is, remove it, and see if a ticket is necessary
            for(int i = 0; i < 10; i++){
                if(dockingBay[i]->getShip() && (dockingBay[i]->getShip()->getID() == sID)){
                    ticket* citation = new ticket;
                    citation->setMinOut(stoi(minute));
                    citation->setHourOut(stoi(hour));
                    citation->setMeter(dockingBay[i]);
                    citation->setNode(dockingBay[i]->getShip());
                    if(citation->getTimeDiff() > 0)
                        writeTicket(citation);
                    // clean up
                    delete citation;
                    delete (dockingBay[i]->getShip());
                    delete dockingBay[i];
                    // create a new meter object
                    dockingBay[i] = new meter;
                    break;
                }
            }
        }

        // if a bay is available, move the first ship in queue to the dock, update timestamps
        for(int i = 0; i < 10; i++){
            if(!dockingBay[i]->getShip()){
                dockingBay[i]->setShip(queue.getFirst());
                dockingBay[i]->setHourIn(stoi(hour));
                if(action == "enter")
                    dockingBay[i]->setMinIn(stoi(minute));
                else if(action == "exit")
                    dockingBay[i]->setMinIn(stoi(minute)+15);
                queue.removeFirst();
                break;
            }
        }
    }

    // clean things up
    inFile.clear();
    inFile.close();

    for(int i = 0; i < 10; i++) {
        delete (dockingBay[i]->getShip());
        delete dockingBay[i];
    }
    return 0;
}

// this function simplifies node creation
void makeNode(node &obj, string n, string i, string c){
    obj.setName(n);
    obj.setID(i);
    obj.setCredit(stoi(c));
}

// writes ticket information to a file with pretty formatting
void writeTicket(ticket* citation){

    // open output file
    fstream outFile;
    outFile.open("Tickets.txt", ios::app|ios::out);
    outFile << setw(25) << left << "Ship ID:" << right << citation->getNode()->getID() << endl;
    outFile << setw(25) << left << "Name:" << right << citation->getNode()->getName() << endl;
    outFile << setw(25) << left << "Time In:" << right << setw(2) << setfill('0') << citation->getMeter()->getHourIn()
                                   << ":" << setw(2) << citation->getMeter()->getMinIn() << endl << setfill(' ');
    outFile << setw(25) << left << "Time Out:" << right << setw(2) << setfill('0') << citation->getHourOut() << ":"
                                   << setw(2) << citation->getMinOut() << endl << setfill(' ');
    outFile << setw(25) << left << "Credited Minutes:" << right << citation->getNode()->getCredit() << endl;
    outFile << setw(25) << left << "Extra Minutes:" << right << citation->getTimeDiff() << endl;
    outFile << setw(25) << left << "Fine:" << right << citation->getTimeDiff()*2000 << endl << endl;
    outFile.close();
}