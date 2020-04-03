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
    example s(vector<string>{"Before: [1, 1, 1, 0]","4 1 0 0","After:  [1, 1, 1, 0]"});
    vector<example> ex = parse1();
    for(auto& val:ex){
        cout<<val.opc<<endl;
    }
}

