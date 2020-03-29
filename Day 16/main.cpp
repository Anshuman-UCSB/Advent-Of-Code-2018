#include <iostream>
#include <fstream>
#include <vector>
#include "dict.h"

using namespace std;

void p1();

int main(){
    p1();
}

int valid(vector<string> set){
    int out = 0;
    int reg[4] = {-1,-1,-1,-1};
    string vals = set[0];
    vals = vals.substr(9);
    vals[vals.size()-1] = ',';
    for(int i = 0;i<4;i++){
        reg[i] = stoi(vals.substr(0,vals.find(",")));
        vals = vals.substr(vals.find(",")+1);
    }
    cout<<"B[ ";
    for(int i = 0;i<4;i++){
        cout<<reg[i]<<" ";
    }cout<<"]\n";

    int expected[4] = {-1,-1,-1,-1};
    vals = set[2];
    vals = vals.substr(9);
    vals[vals.size()-1] = ',';
    for(int i = 0;i<4;i++){
        expected[i] = stoi(vals.substr(0,vals.find(",")));
        vals = vals.substr(vals.find(",")+1);
    }
    cout<<"->A[ ";
    for(int i = 0;i<4;i++){
        cout<<expected[i]<<" ";
    }cout<<"]\n";

    return out;
}

void p1(){
    cout<<valid(vector<string>{"Before: [1, 1, 1, 0]","4 1 0 0","After:  [1, 1, 1, 0]"})<<endl;
    vector<int> vals;
    string line;
    fstream file("p1inp.txt");
    vector<string> temp;
    while(getline(file,line)){
        if(temp.size()==4){
            temp.clear();
        }
        temp.push_back(line);
        if(temp.size()==3){
            vals.push_back(valid(temp));
        }
    }
    cout<<vals.size()<<endl;
}
