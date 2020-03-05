#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Node{
    int32_t data;
    Node* next;
    Node(){
        data = 0;
        next = 0;
    }
    Node(int dat, Node* n){
        data = dat;
        next = n;
    }
};

int main(){
    fstream file("day1.txt");
    cout<<"started"<<endl;
    Node* head, *end;
    Node* visited, *vend;
    visited =0;
    vend = 0;
    head = 0;
    end = 0;
    string line;
    if(file.is_open()){
        while(getline(file,line)){
            if(head == 0){
                head = new Node(stoi(line), 0);
                end = head;
            } else {
                end->next = new Node(stoi(line), 0);
                end = end->next;
            }
        }
        file.close();
    }
    end->next = head;
    int freq = 0;
    visited=new Node(0,0);
    vend = visited;
    for(Node* p = head;p;p=p->next){
        freq+=p->data;
        for(Node* k = visited;k;k=k->next){
            if(k->data == freq){
                cout<<"Frequency repeated: "<<k->data<<endl;
                return 0;
            }
        }
        vend->next = new Node(freq, 0);
        vend = vend->next;
        //cout<<p->data<<" -> "<<freq<<endl;
    }
}