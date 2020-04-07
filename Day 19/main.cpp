#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

void eval(const vector<int>& cmd, vector<int>& reg){
    switch(cmd[0]){
        case 0:
            reg[cmd[3]] = reg[cmd[1]] + reg[cmd[2]];
            break;
        case 1:
            reg[cmd[3]] = reg[cmd[1]] + cmd[2];
            break;
        case 2:
            reg[cmd[3]] = reg[cmd[1]] * reg[cmd[2]];
            break;
        case 3:
            reg[cmd[3]] = reg[cmd[1]] * cmd[2];
            break;
        case 4:
            reg[cmd[3]] = reg[cmd[1]] & reg[cmd[2]];
            break;
        case 5:
            reg[cmd[3]] = reg[cmd[1]] & cmd[2];
            break;
        case 6:
            reg[cmd[3]] = reg[cmd[1]] | reg[cmd[2]];
            break;
        case 7:
            reg[cmd[3]] = reg[cmd[1]] | cmd[2];
            break;
        case 8:
            reg[cmd[3]] = reg[cmd[1]];
            break;
        case 9:
            reg[cmd[3]] = cmd[1];
            break;
        case 10:
            reg[cmd[3]] = cmd[1] > reg[cmd[2]];
            break;
        case 11:
            reg[cmd[3]] = reg[cmd[1]] > reg[cmd[2]];
            break;
        case 12:
            reg[cmd[3]] = reg[cmd[1]] > reg[cmd[2]];
            break;
        case 13:
            reg[cmd[3]] = cmd[1] == reg[cmd[2]];
            break;
        case 14:
            reg[cmd[3]] = reg[cmd[1]] == reg[cmd[2]];
            break;
        case 15:
            reg[cmd[3]] = reg[cmd[1]] == reg[cmd[2]];
            break;
    }
}

void print(const vector<int>& v){
    for(auto& c:v){
        cout<<c<<" ";
    }cout<<endl;
}

void print(const vector<vector<int>>& v){
    for(auto& c: v){
        print(c);
    }
}

int main(){
    map <string, int> trans={
        {"addr",0},
        {"addi",1},
        {"mulr",2},
        {"muli",3},
        {"banr",4},
        {"bani",5},
        {"borr",6},
        {"bori",7},
        {"setr",8},
        {"seti",9},
        {"gtir",10},
        {"gtri",11},
        {"gtrr",12},
        {"eqir",13},
        {"eqri",14},
        {"eqrr",15},
    };


    string line;
    fstream file("input.txt");
    getline(file,line);
    vector<int> reg(6,0);
    stringstream ss(line);
    string temp;
    ss>>line>>temp;
    int& ip = reg[stoi(temp)];
    vector<vector<int>> instructions;
    //cout<<ip<<endl;
    
    while(getline(file,line)){
        stringstream ss(line);
        vector<int> t;
        ss>>temp;
        t.push_back(trans[temp]);
        ss>>temp;
        t.push_back(stoi(temp));
        ss>>temp;
        t.push_back(stoi(temp));
        ss>>temp;
        t.push_back(stoi(temp));
        instructions.push_back(t);
    }
    //print(instructions);

    while(true){
        //void eval(const vector<int>& cmd, vector<int>& reg)
        eval(instructions[ip],reg);
        if(ip<0 || ip>=instructions.size()-1){
            break;
        }
        ip++;
        //print(reg);
    };
    cout<<"\nFinal register: "<<endl;
    print(reg);
    cout<<"Part 1: "<<reg[0]<<endl;

}