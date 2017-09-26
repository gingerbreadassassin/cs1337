/*
 * Connor Ness - cdn073000
 * Kaleb Warneke - ktw160030
 *
 * In-Class Assignment 3
 */

#include <iostream>

using namespace std;

struct node {
    int num;
    node* next;
};

void insert(node* &h, int x){
    node* ptr = new node;
    ptr->num = x;
    ptr->next = nullptr;

    if (!h)
        h = ptr;
    else if (ptr->num < h->num){
        ptr->next = h;
        h = ptr;
    }
    else{
        node* cur = h;
        while (cur->next){
            if (cur->next->num > ptr->num){
                ptr->next = cur->next;
                cur->next = ptr;
                return;
            }
            else
                cur = cur->next;
        }
        cur->next = ptr;
    }
}

void delNode(node* &h, int x){
    node* hold = h;
    if (!h)
        cout <<"Empty List" << endl;
    else if(h->num == x){
        h = h->next;
        delete hold;
    }
    else{
        node* cur = h;
        while (cur->next){
            if (cur->next->num == x){
                hold = cur->next;
                cur->next = hold->next;
                delete hold;
                return;
            }
            else
                cur = cur->next;

        }
        cout << x << " is not in the list" << endl;
    }
}

void print(node* cur){
    while(cur){
        cout << cur->num << " ";
        cur = cur->next;
    }
    cout << endl;
}

int searchList(node* h, int x){
    int pos = 0;
    while(h != nullptr){
        if(h->num == x)
            return pos;
        pos++;
        h = h->next;
    }
    return -1;
}

void insertNode(node* &h, int x, int pos){
    node* newNode = new node;
    newNode->num = x;
    newNode->next = nullptr;


    if(pos == 0) {
        newNode->next = h;
        h = newNode;
    }
    else{
        int curPos = 0;
        node* cur = h;
        while(curPos+1 != pos) {
                    cur = cur->next;
                    curPos++;
                }
        newNode->next = cur->next;
        cur->next = newNode;
            }

}

void removeNode(node* &h, int pos){
    int curPos = 0;

    node* cur = h;

    while(curPos != pos-1){
        cur = cur->next;
        curPos++;
    }
    node* hold = cur;
    hold = cur->next;
    cur->next = cur->next->next;
    delete hold;


}

void listDestruct(node* & h){
    while(h != nullptr){
        node* hold;
        hold = h;
        h = h->next;
        delete[]hold;
    }
    delete[]h;
}

int main(){
    node* head = nullptr;

    for(int i = 1; i < 6; i++){
        insertNode(head, i, 0);
    }

    print(head);

    insertNode(head, 16, 3);

    print(head);

    cout << searchList(head, 16) << endl;

    removeNode(head, 3);

    print(head);

    cout << searchList(head, 16) << endl;

    print(head);

    listDestruct(head);

    return 0;
}