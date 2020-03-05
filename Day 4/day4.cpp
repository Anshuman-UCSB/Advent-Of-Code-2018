#include <iostream>
#include <fstream>
#include <cstring>
#include "node.h"
using namespace std;

//[1518-11-09 00:36] falls asleep

struct event{
    int year, month, day, hour, minute;
    string action;
    event(){
        year = month = day = hour = minute = -1;
        action = "";
    }

    event(string str){
        year = stoi(str.substr(1,4));
        month = stoi(str.substr(6,2));
        day = stoi(str.substr(9,2));
        hour = stoi(str.substr(12,2));
        minute = stoi(str.substr(15,2));
        action = str.substr(19);
    }

};

bool operator<(const event& e1, const event& e2){
    string e1conc,e2conc;
    e1conc ="";
    e1conc+=to_string(e1.year);
    e1conc+=to_string(e1.month);
    e1conc+=to_string(e1.day);
    e1conc+=to_string(e1.hour);
    e1conc+=to_string(e1.minute);

    e2conc+=to_string(e2.year);
    e2conc+=to_string(e2.month);
    e2conc+=to_string(e2.day);
    e2conc+=to_string(e2.hour);
    e2conc+=to_string(e2.minute);

    return(stoi(e1conc)<stoi(e2conc));
}
bool operator<=(const event& e1, const event& e2){
    string e1conc,e2conc;
    e1conc ="";
    e1conc+=to_string(e1.year);
    e1conc+=to_string(e1.month);
    e1conc+=to_string(e1.day);
    e1conc+=to_string(e1.hour);
    e1conc+=to_string(e1.minute);

    e2conc+=to_string(e2.year);
    e2conc+=to_string(e2.month);
    e2conc+=to_string(e2.day);
    e2conc+=to_string(e2.hour);
    e2conc+=to_string(e2.minute);

    return(stoi(e1conc)<=stoi(e2conc));
}

int main(){
    fstream file("day4.txt");
    string line;
    Node<event>* head = new Node<event>(event());
    auto end = head;
    while(getline(file,line)){
        end->next = new Node<event>(event(line));
        end = end->next;
    }
    file.close();

    head = head->next;

    for(auto p = head;p;p=p->next){
        cout<<p->data.year<<endl;
    }
}