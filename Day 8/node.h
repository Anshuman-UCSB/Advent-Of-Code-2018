#include <vector>
#include <iostream>
using namespace std;

struct Node{
    int id;
    int nodeCount, meta;
    vector<Node> nodes;
    vector<int> metadata;


    Node(const vector<int>& inp, int& ind, int& id){
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

void printTree(Node n, int level){
    for(int i = 2;i<level*2;i++){
        cout<<" ";
    }
    cout<<"|_";
    cout<<n.id<<endl;
    for(int i = 0;i<n.nodes.size();i++){
        printTree(n.nodes[i], level+1);
    }
}

int recursiveValue(Node n){
    int sum = 0;
    if(n.nodeCount == 0){
        for(int val:n.metadata){
            sum+=val;
        }

        return sum;
    }
    for(int i = 0;i<n.metadata.size();i++){
        if(n.metadata[i]<=n.nodes.size() && n.metadata[i]>0){
            sum+=recursiveValue(n.nodes[n.metadata[i]-1]);
        }else{
            cout<<"Invalid node ["<<n.id<<"] location ["<<n.metadata[i]<<"], giving 0. ";
            cout<<"Node had ["<<n.nodeCount<<"] children nodes."<<endl;
        }
    }
    return sum;
}