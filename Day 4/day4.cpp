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
        string comb = str.substr(1,4)+ str.substr(6,2) + str.substr(9,2);
        if(str.substr(12,2) == "00"){
            comb+="50";
        }else{
            comb+=str.substr(12,2);
        }
        comb+=str.substr(15,2);
        relNum = stol(comb);
    }

};

struct guard{
    int id;
    int timesSlept[60];
    guard(){id = -1;}
    guard(int id){
        this ->id = id;
        for(int i = 0;i<60;i++){
            timesSlept[i] = 0;
        }
    }
    void logSleep(int l, int r){
        for(int i = l;i<r;i++){
            timesSlept[i]++;
        }
    }
};

bool operator==(const guard& g1, const guard& g2){
    return (g1.id==g2.id);
}

bool operator<(const guard& g1, const guard& g2){
    return(g1.id<g2.id);
}

bool operator<=(const guard& g1, const guard& g2){
    return(g1.id<=g2.id);
}

bool operator<(const event& e1, const event& e2){
    return((e1.relNum)<(e2.relNum));
}
bool operator<=(const event& e1, const event& e2){

    return((e1.relNum)<=(e2.relNum));
}

int sumSleep(guard g){
    int sum = 0;
    for(int i =0;i<60;i++){
        sum+=g.timesSlept[i];
    }
    return sum;
}

int main(){
    fstream file("day4.txt");
    string line;
    Node<event>* head = 0;
    while(getline(file,line)){
        insert(head,event(line));
    }
    file.close();
    head = head->next;
    auto p = head;

    Node<guard>* guards = 0;
    int cId = -1;
    for(Node<event>* p = head; p;p=p->next){
        if(p->data.action[0] == 'G'){
            string cut = p->data.action.substr(7);
            cut = cut.substr(0,cut.find(" "));
            guard g = guard(stoi(cut));
            cId = g.id;
            if(!inList(guards,g)){
                insert(guards,g);
            }
        }
        if(p->data.action[0] == 'f'){
            Node<guard>* g;
            for(g = guards;g->data.id!=cId;g=g->next){
                // iterate till gets to proper guard node
            }
            g->data.logSleep(p->data.minute,p->next->data.minute);
        }
        if(cId == 2753){
            cout<<p->data.raw<<endl;
        }
    }

    guard mostSleep;
    int maxSleep = -1;
    for(auto p = guards;p;p=p->next){
        int sleepSum = sumSleep(p->data);
        cout<<p->data.id<<", min slept: "<<sumSleep(p->data)<<endl;
        if(sleepSum>maxSleep){
            maxSleep = sleepSum;
            mostSleep = p->data;
        }
        if(p->data.id == -1){
            for(int i = 0;i<60;i++){
                cout<<p->data.timesSlept[i]<<" ";
            }
            cout<<endl;
        }
    }

    cout<<"Most sleep guard is "<<mostSleep.id<<".\n";
    int most = -1;
    int time = -1;
    for(int i = 0;i<60;i++){
        cout<<mostSleep.timesSlept[i]<<" ";
        if(mostSleep.timesSlept[i]>most){
            most = mostSleep.timesSlept[i];
            time = i;
        }
    }cout<<endl;
    //not 1332452, 2753, min slept: 484
    cout<<"He slept the most at "<<time<<".\n";
    
}