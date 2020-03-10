#include <vector>
#include <iostream>
using namespace std;

struct Node{
    char id;
    int nodeCount, meta;
    vector<Node*> nodes;
    vector<int> metadata;


    Node(const vector<int>& inp, int& ind, char& id){
        nodeCount = inp[ind++];
        this->id = id;
        meta = inp[ind++];
        for(int i = 0;i<nodeCount;i++){
            id++;
            nodes.push_back(new Node(inp, ind, id));
        }
        for(int i = 0;i<meta;i++){
            metadata.push_back(inp[ind++]);
        }
        cout<<"meta for id "<<this->id<<": "<<meta<<endl;
        printMeta();
    }

    void printMeta(){
        for(int i  = 0;i<metadata.size();i++){
            cout<<metadata[i]<<" ";
        }cout<<endl;
    }

    Node(const vector<int>& inp){
        int ind = 0;
        char id = 'A';
        Node(inp, ind, id);
    }
};