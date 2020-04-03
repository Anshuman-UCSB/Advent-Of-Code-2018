#include "oper.h"
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
        for(int i = 0;i<16;i++){
            if(val.exp == machine.eval(i, val.cmd, val.reg)){
                val.possible.insert(i);
                cout<<i<<" ";
            }
        }cout<<endl;
    }
    map<int, int> 
}

