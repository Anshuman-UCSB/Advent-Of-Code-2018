#include <iostream>
#include <fstream>
#include <string>
#include "node.h"
#include <cstring>

using namespace std;

struct Claim{
    int id, x, y, w, h;

    Claim(){
        id = x = y = w = h= 0;
    }
    Claim(string inp){
        char* arg;
        char *cstr = new char[inp.length() + 1];
        strcpy(cstr, inp.c_str());
        arg = strtok(cstr," ,:@#x");
        id = stoi(arg);
        arg = strtok(NULL," ,:@#x");
        x = stoi(arg);
        arg = strtok(NULL," ,:@#x");
        y = stoi(arg);
        arg = strtok(NULL," ,:@#x");
        w = stoi(arg);
        arg = strtok(NULL," ,:@#x");
        h = stoi(arg);
    }
};

int main(){
    fstream file("day3.txt");
    string line;
    Node<string>* dHead = new Node<string>("");
    Node<string>* dEnd = dHead;
    while(getline(file,line)){
        dEnd->insertEnd(line);
        dEnd=dEnd->next;
    }
    dHead = dHead->next;
    Node<Claim>* head = new Node<Claim>(Claim());
    Node<Claim>* end = head;
    int maxX(0), maxY(0);
    for(auto p = dHead;p;p=p->next){        
        end->insertEnd(Claim(p->data));
        end = end->next;
        cout<<p->data<<endl;
        maxX = end->data.x+end->data.w+1 > maxX ? end->data.x+end->data.w+1 : maxX;
        maxY = end->data.y+end->data.h+1 > maxY ? end->data.y+end->data.h+1 : maxY;
    }
    //Head points to linked list of Claim objects
    //Claim has id, x, y, w, h
    cout<<"\nmaking grid of size "<<maxX<<"x"<<maxY<<endl;

    int grid[maxX][maxY];
    


}