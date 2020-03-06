#include <iostream>
using namespace std;
template<class T>
class Node{
    public:
    T data;
    Node<T>* next;

    Node(T data){
        this->data = data;
        next = 0;
    }

};
template <class T>
bool operator<(const Node<T>& n1, const Node<T>& n2){
    return(n1.data<n2.data);
}

template <class T>
void insert(Node<T>*& head, T dat){
    insert(head,new Node<T>(dat));
}

template <class T>
void insert(Node<T>*& head, Node<T>* n){
    if(head == 0){
        head = n;
        return;
    }
    if(n->data<=head->data){
        n->next = head;
        head = n;
        return;
    }
    Node<T>* p = head->next;
    Node<T>* l = head;
    for(;p;p=p->next){
        if(n->data<=p->data){
            l->next = n;
            n->next = p;
            return;
        }
        l = l->next;
    }
    l->next = n;

}

template <class T>
bool inList(Node<T>*& head, T n){
    for(Node<T>* p = head;p;p=p->next){
        if(p->data == n){
            return true;
        }
    }
    return false;
}