#include <iostream>
#include <fstream>
#include <cstring>
#include "node.h"
using namespace std;

//[1518-11-09 00:36] falls asleep

struct event{
    int year, month, day, hour, minute;
    long relNum;
    string raw;
    string action;
    event(){
        year = month = day = hour = minute = -1;
        action = "";
    }

    event(string str){
        raw = str;
        year = stoi(str.substr(1,4));
        month = stoi(str.substr(6,2));
        day = stoi(str.substr(9,2));
        hour = stoi(str.substr(12,2));
        minute = stoi(str.substr(15,2));
        action = str.substr(19);
        string comb = str.substr(1,4)+ str.substr(6,2) + str.substr(9,2) + str.substr(12,2) + str.substr(15,2);
        relNum = stol(comb);
    }

};

bool operator<(const event& e1, const event& e2){
    return((e1.relNum)<(e2.relNum));
}
bool operator<=(const event& e1, const event& e2){

    return((e1.relNum)<=(e2.relNum));
}

int main(){
    fstream file("day4.txt");
    string line;
    Node<event>* head;
    while(getline(file,line)){
        //cout<<line<<endl;
        insert(head,event(line));
    }
    file.close();

    head = head->next;
    for(auto p = head; p;p=p->next){
        cout<<p->data.raw<<endl;
    }

}