#include <iostream>
#include "Node.h"

#define PLAYERS 9
#define MARBLE 25

using namespace std;

void printList(Node* head){
    cout<<head->number<<" ";
    for(Node* p = head->next;p!= head;p=p->next){
        cout<<p->number<<" ";
    }cout<<endl;
}

void partOne(){
    Node* head = new Node(0);
    Node* current = head;
    head->next = head;
    int player = 0;
    for(int i = 1;i<MARBLE+1;i++){
        cout<<"Player: "<<player+1<<endl;
        printList(head);
        current = current->next;
        insert(current, new Node(i));
        current = current->next;
        player++;
        player = player%PLAYERS;
    }
}

int main(){
    partOne();
}