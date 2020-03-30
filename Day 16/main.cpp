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
    // for(int i = 0;i<set.size();i++){
    //     cout<<set[i]<<endl;
    // }
    int out = 0;
    vector<int> reg(4);
    string vals = set[0];
    vals = vals.substr(9);
    vals[vals.size()-1] = ',';
    for(int i = 0;i<4;i++){
        reg[i] = stoi(vals.substr(0,vals.find(",")));
        vals = vals.substr(vals.find(",")+1);
    }
    // cout<<"B[ ";
    // for(int i = 0;i<4;i++){
    //     cout<<reg[i]<<" ";
    // }cout<<"]\n";

    string cmdRaw = set[1];
    vector<int> cmd(4);
    cmd[0] = stoi(cmdRaw.substr(0,cmdRaw.find(" ")));
    cmdRaw = cmdRaw.substr(cmdRaw.find(" ")+1);
    cmd[1] = stoi(cmdRaw.substr(0,cmdRaw.find(" ")));
    cmdRaw = cmdRaw.substr(cmdRaw.find(" ")+1);
    cmd[2] = stoi(cmdRaw.substr(0,cmdRaw.find(" ")));
    cmdRaw = cmdRaw.substr(cmdRaw.find(" ")+1);
    cmd[3] = stoi(cmdRaw);

    vector<int> expected(4);
    vals = set[2];
    vals = vals.substr(9);
    vals[vals.size()-1] = ',';
    for(int i = 0;i<4;i++){
        expected[i] = stoi(vals.substr(0,vals.find(",")));
        vals = vals.substr(vals.find(",")+1);
    }
    // cout<<"->A[ ";
    // for(int i = 0;i<4;i++){
    //     cout<<expected[i]<<" ";
    // }cout<<"]\n";
    for(int i = 0;i<16;i++){
        out+=workingOpCode(reg,cmd,expected, i);
    }
    return out;
}

void p1(){
    // cout<<valid(vector<string>{"Before: [3, 2, 1, 1]","9 2 1 2","After:  [3, 2, 2, 1]"})<<endl;
    // return;
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
    int threeOrMore = 0;
    cout<<"[ ";
    for(int i = 0;i<vals.size();i++){
        cout<<vals[i]<<" ";
        threeOrMore+=vals[i]>=3;
    }
    cout<<"]"<<endl;
    cout<<threeOrMore<<" is answer for part 1."<<endl;
}
