#include <vector>
#include <iostream>
using namespace std;

struct Node{
    char id;
    int nodeCount, meta;
    vector<Node> nodes;
    vector<int> metadata;


    Node(const vector<int>& inp, int& ind, char& id){
        nodeCount = inp[ind++];
        this->id = id;
        meta = inp[ind++];
        for(int i = 0;i<nodeCount;i++){
            id++;
            nodes.push_back(Node(inp, ind, id));
        }
        for(int i = 0;i<meta;i++){
            metadata.push_back(inp[ind++]);
        }
        cout<<"meta for id "<<this->id<<": "<<meta<<endl;
    }

    void printMeta(){
        for(int i  = 0;i<metadata.size();i++){
            cout<<metadata[i]<<" ";
        }cout<<endl;
    }
};

int recursiveSum(Node n){
    int sum = 0;
    for(int i = 0;i<n.metadata.size();i++){
        sum += n.metadata[i];
    }
    for(int i = 0;i<n.nodes.size();i++){
        sum+= recursiveSum(n.nodes[i]);
    }
    return sum;
}