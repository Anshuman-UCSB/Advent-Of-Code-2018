#include <iostream>
#include <fstream>
#include <vector>
#include "worker.h"
using namespace std;

#define WORKERS 5





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

    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0;i<elems.size()-1;i++){
            if(elems[i+1]<elems[i]){
                char temp = elems[i+1];
                elems[i+1] = elems[i];
                elems[i] = temp;
                sorted = false;
            }
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
    
    while(done.size()!=elems.size()){
        cout<<endl<<"Time "<<time<<endl;
        getFinished(workers,done);
        cout<<"Done: ";
        printVector(done);
        updateInProgress(workers, inProgress);
        cout<<"Progress: ";
        printVector(inProgress);
        updateAble(done,inProgress,able, elems, rules);
        cout<<"Able: ";
        printVector(able);
        giveJobs(workers,able);
        for(Worker wrk: workers){
            if(!wrk.working)
                continue;
            cout<<"Worker "<<wrk.id<<":"<<endl;
            cout<<"    "<<wrk.letter<<": "<<wrk.remainingTime<<endl;
        }
        updateTime(time,workers);
    }
    cout<<"Answer: "<<time-1<<endl;
    for(char val: done){
        cout<<val;
    }cout<<endl;
}

//LNRTFJMQZVCIHABKPXYEUGWDSO didn't work