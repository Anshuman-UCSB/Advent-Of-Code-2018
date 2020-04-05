#include "oper.h"
#include <sstream>
using namespace std;

vector<example> parse1(){
    fstream file("input1.txt");
    string line;
    vector<example> out;
    vector<string> temp;
    try{
        while(getline(file,line)){
            temp.push_back(line);
            if(temp.size()==4){
                out.push_back(example(temp));
                temp.clear();
            }
        }
    }catch(...){}

    return out;
}

int main(){
    evaluator machine;
    //example s(vector<string>{"Before: [3, 2, 1, 1]","9 2 1 2","After:  [3, 2, 2, 1]"});
    //for(int i = 0;i<16;i++){
    //    if(s.exp == machine.eval(i, s.cmd, s.reg)){
    //        s.possible.insert(i);
    //        cout<<machine.translate[i]<<" ";
    //    }
    //}
    //return 0;
    vector<example> ex = parse1();
    for(example& val:ex){
        cout<<">";
        for(int i = 0;i<16;i++){
            if(val.exp == machine.eval(i, val.cmd, val.reg)){
                val.possible.insert(i);
                cout<<i<<" ";
            }
        }cout<<endl;
        if (val.possible.size()==0){
            print(val.reg);
            print(val.cmd);
            print(val.exp);
        }

    }
    map<int, int> OPCmap;
    while(machine.iter(ex,OPCmap)){}
    for(auto it = OPCmap.begin(); it != OPCmap.end(); it++){
        cout<<it->first<<" -> "<<machine.translate[it->second]<<endl;
    }
    //by now, OPCmap takes opc and converts it into appropriate int for method

    string line;
    string tok;
    fstream file("input2.txt");
    vector<int> reg(4,0);
    vector<vector<int>> instr;
    vector<int> temp;
    while(getline(file,line)){
        stringstream stream(line);
        temp.clear();
        while(getline(stream, tok, ' ')){
            temp.push_back(stoi(tok));
        }
        //print(temp);
        instr.push_back(temp);
    }
    bool space = false;
    //for(auto& v:instr){
    //    if (space) {cout<<" ";}
    //    cout<<"Cmd: ";
    //    print(v);
    //    if (space) {cout<<" ";}
    //    cout<<v[0]<<" -> "<<machine.translate[OPCmap[v[0]]]<<", on regs ";
    //    space=!space;
    //    print(reg);
    //    reg = machine.eval(OPCmap[v[0]], v, reg);
    //}
    //print(reg);
    
}

//not 0
/*
Expected:
gtir
setr
bori
gtrr
gtri
eqir
seti
eqri
eqrr
borr
addr
mulr
bani
muli
banr
addi

Actual:
gtri
bani
bori
gtrr
gtir
eqri
seti
eqir
eqrr
borr
addr
mulr
muli
banr
addi

*/