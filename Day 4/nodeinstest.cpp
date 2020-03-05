#include <iostream>
#include "node.h"

using namespace std;

int main(){
    Node<int>* head;
    for(int i = 9;i>0;i--){
        insert(head,i);
    }
    insert(head,new Node<int>(-1));
    insert(head,new Node<int>(1));
    for(auto p = head;p;p=p->next){
        cout<<p->data<<" -> ";
    }cout<<endl;
}