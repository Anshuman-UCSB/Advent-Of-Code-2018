#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Step F must be finished before step E can begin.
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
bool isInVector(vector<T> vect, T val){
    for(int i =0;i<vect.size();i++){
        if(vect[i] == val){
            return true;
        }
    }
    return false;
}

void updateAble(vector<char>& able, const vector<char>& made, const vector<Rule>& rules, const vector<char>& elems){
    able.clear();
    for(char elem: elems){
        if(!isInVector<char>(made, elem))
            able.push_back(elem);
    }
    for(Rule rule:rules){
        if(isInVector<char>(able,rule.make)){ //if result is in able vector
            if(!isInVector<char>(made, rule.pre)){
                //if prereq is not made,
                
            }
        }
    }
}

int main(){
    fstream file("day7.txt");
    string line;
    vector<Rule> rules;
    while(getline(file,line)){
        rules.push_back(Rule(line));
    }

    char last, first;
    vector<char> elems;

    for(int i =0;i<rules.size();i++){
        cout<<rules[i].to_str()<<endl;
        if(!isInVector<char>(elems,rules[i].pre)){
            elems.push_back(rules[i].pre);
        }
        if(!isInVector<char>(elems,rules[i].make)){
            elems.push_back(rules[i].make);
        }
    }
    for(int i = 0;i<elems.size();i++){
        cout<<elems[i]<<" ";
    }cout<<endl;

    vector<char> done;
    vector<char> able;


}