#ifndef OPER_H
#define OPER_H

#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <fstream>
using namespace std;

/*
Before: [1, 1, 1, 0]
4 1 0 0
After:  [1, 1, 1, 0]
*/
struct example{
    set<int> possible;
    vector<int> reg, cmd, exp;
    int opc;
    example(vector<string> inp){
        string temp = inp[0].substr(9);
        temp[temp.size()-1]=',';
        for(int i = 0;i<4;i++){
            reg.push_back(stoi(temp.substr(0,temp.find(","))));
            temp = temp.substr(1+temp.find(","));
        }
        temp = inp[1];
        temp+=" ";
        for(int i = 0;i<4;i++){
            cmd.push_back(stoi(temp.substr(0,temp.find(" "))));
            temp = temp.substr(1+temp.find(" "));
        }

        temp = inp[2].substr(9);
        temp[temp.size()-1]=',';
        for(int i = 0;i<4;i++){
            exp.push_back(stoi(temp.substr(0,temp.find(","))));
            temp = temp.substr(1+temp.find(","));
        }
        opc = cmd[0];
    }
};

struct evaluator{
    set<int> possbile;
    map<int, string> translate{
        {0 , "addr"},
        {1 , "addi"},
        {2 , "mulr"},
        {3 , "muli"},
        {4 , "banr"},
        {5 , "bani"},
        {6 , "borr"},
        {7 , "bori"},
        {8 , "setr"},
        {9 , "seti"},
        {10 , "gtir"},
        {11 , "gtri"},
        {12 , "gtrr"},
        {13 , "eqir"},
        {14 , "eqri"},
        {15 , "eqrr"}
    };

    void addr(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]+reg[cmd[2]];
    }

    void addi(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]+cmd[2];
    }

    void mulr(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]*reg[cmd[2]];
    }

    void muli(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]*cmd[2];
    }

    void banr(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]&reg[cmd[2]];
    }

    void bani(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]&cmd[2];
    }

    void borr(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]^reg[cmd[2]];
    }

    void bori(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]^cmd[2];
    }

    void setr(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]];
    }

    void seti(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = cmd[1];
    }

    void gtir(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]>cmd[2]?1:0;
    }

    void gtri(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = cmd[1]>reg[cmd[2]]?1:0;
    }

    void gtrr(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]>reg[cmd[2]]?1:0;
    }

    void eqir(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]==cmd[2]?1:0;
    }

    void eqri(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = cmd[1]==reg[cmd[2]]?1:0;
    }

    void eqrr(const vector<int>& cmd, vector<int>& reg){
        reg[cmd[3]] = reg[cmd[1]]==reg[cmd[2]]?1:0;
    }


    vector<int> eval(int opc, const vector<int> cmd, const vector<int>& reg){
        vector<int> temp(reg);
        switch(opc){
            case 0: addr(cmd, temp); break;
            case 1: addi(cmd, temp); break;
            case 2: mulr(cmd, temp); break;
            case 3: muli(cmd, temp); break;
            case 4: banr(cmd, temp); break;
            case 5: bani(cmd, temp); break;
            case 6: borr(cmd, temp); break;
            case 7: bori(cmd, temp); break;
            case 8: setr(cmd, temp); break;
            case 9: seti(cmd, temp); break;
            case 10: gtir(cmd, temp); break;
            case 11: gtri(cmd, temp); break;
            case 12: gtrr(cmd, temp); break;
            case 13: eqir(cmd, temp); break;
            case 14: eqri(cmd, temp); break;
            case 15: eqrr(cmd, temp); break;
        }
        return temp;
    }

};

template <class T>
void print(vector<T> v){
    cout<<"[ ";
    for(T& val: v){
        cout<<val<<" "<<endl;
    }cout<<"]\n";
}


#endif