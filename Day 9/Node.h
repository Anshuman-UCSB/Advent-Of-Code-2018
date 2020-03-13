#include <iostream>
using namespace std;

struct Node{
    long long int number;
    Node* next;
    Node* last;
    Node(long long int dat){
        number = dat;
    }
};

void insert(Node* before, Node* ins, long long int& size){
    ins->next = before->next;
    ins->next->last = ins;
    ins->last = before;
    before->next = ins;
    size++;
}

void insert(Node* before, long long int val, long long int& size){
    insert(before, new Node(val), size);
}

long long int remove(Node* rem, long long int& size){
    rem->last->next = rem->next;
    rem->next->last = rem->last;
    long long int ret = rem->number;
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

void print(Node* head, long long int size){
    Node* p = head;
    for(long long int i =0;i<size;i++){
        cout<<p->number<<" ";
        right(p);
    }cout<<endl;
}