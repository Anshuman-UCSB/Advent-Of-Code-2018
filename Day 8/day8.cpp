#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "node.h"

using namespace std;

vector<int> parse(){
    vector<int> out;
    string line;
    fstream file("day8.txt");
    getline(file,line);
    string temp = "";
    for(char letter: line){
        if(letter != ' '){
            temp+=letter;
        } else{
            out.push_back(stoi(temp));
            temp = "";
        }
    }
    out.push_back(stoi(temp));
    return out;
}

void printVector(const vector<int>& vect){
    for(int i  = 0;i<vect.size();i++){
        cout<<vect[i]<<" ";
    }cout<<endl;
}

void part1(){
    vector<int> input = parse();
    printVector(input);
    int tmpId = 0;
    char tmpChar = 'A';
    Node* head = new Node(input, tmpId, tmpChar);
    cout<<"["<<head->id<<"]"<<endl;
    printVector(head->metadata);
    head->printMeta();
}

int main(){
    part1();
}