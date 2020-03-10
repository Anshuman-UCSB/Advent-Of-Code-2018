#include <iostream>
#include <fstream>
#include <vector>
#include "worker.h"
using namespace std;

#define WORKERS 2

struct Rule{
    char pre;
    char make;

    Rule(string inp){
        pre = inp[5];
        make = inp[36];
    }

    string to_str(){
        string out = "";
        out+=pre;
        out+=" -> ";
        out+= make;
        return out;
    }
};



template <class T>
void printVector(vector<T> vect){
    for(T elem: vect){
        cout<< elem << " ";
    }cout<<endl;
}


int main(){
    fstream file("day7.txt");
    string line;
    vector<Rule> rules;
    while(getline(file,line)){
        rules.push_back(Rule(line));
    }
    
    vector<char> elems;
    for(Rule rule: rules){
        int ind = find(elems,rule.pre); 
        if( ind == -1){
            elems.push_back(rule.pre);
        }
    }
    for(Rule rule: rules){
        int ind = find(elems,rule.make); 
        if( ind == -1){
            elems.push_back(rule.make);
        }
    }

    //By now, rules has all rules in Rule struct,
    //elems has all elements in rules

    vector<Worker> workers;
    int time = 0;
    for(int i = 0;i<WORKERS;i++){
        workers.push_back(Worker(i+1));
    }
    //initialize workers
    vector<char> done, inProgress, able;
    
    
}