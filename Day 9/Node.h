#include <iostream>
using namespace std;

struct Node{
    int number;
    Node* next;
    Node* last;
    Node(int dat){
        number = dat;
    }
};

void insert(Node* before, Node* ins, int& size){
    ins->next = before->next;
    ins->next->last = ins;
    ins->last = before;
    before->next = ins;
    size++;
}

void insert(Node* before, int val, int& size){
    insert(before, new Node(val), size);
}

int remove(Node* rem, int& size){
    rem->last->next = rem->next;
    rem->next->last = rem->last;
    int ret = rem->number;
    delete rem;
    size--;
    return (ret);
}

void right(Node*& p){
    p = p->next;
}

void left(Node*& p){
    p = p->last;
}

void print(Node* head, int size){
    Node* p = head;
    for(int i =0;i<size;i++){
        cout<<p->number<<" ";
        right(p);
    }cout<<endl;
}