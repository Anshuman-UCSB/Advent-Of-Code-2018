#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

struct Grid{
    vector<vector<char>> g;
    map<vector<vector<char>>, vector<int>> visited;
    int min = 0;
    Grid(){
        fstream file("input.txt");
        string line;
        while(getline(file,line)){
            vector<char> t;
            for(auto& c:line){
                t.push_back(c);
            }
            t.pop_back();
            g.push_back(t);
        }
    }

    void print(){
        cout<<endl;
        for(auto& v:g){
            for(auto& c:v){
                cout<<c;
            }cout<<endl;
        }
        cout<<endl;
    }

    int neighbor(int x, int y, int search){
        int found = 0;
        for(int i = x-1;i<=x+1;i++){
            for(int j = y-1;j<=y+1;j++){
                if(i == x && j == y){
                    continue;
                }
                if(j<0||j>=g.size() || i<0 || i>=g[0].size()){
                    continue;
                }
                found+=g[j][i]==search;
                
            }
        }
        return found;
    }

    void iter(){
        vector<vector<char>> t(g.size(), vector<char>(g[0].size(),'.'));
        //ground .
        //trees |
        //lumberyard #
        for(int y = 0;y<g.size();y++)
            for(int x = 0;x<g[0].size();x++)
                switch(g[y][x]){
                    case '.':
                        if(neighbor(x,y,'|')>=3){
                            t[y][x] = '|';
                        }else{
                            t[y][x] = '.';
                        }
                        break;
                    case '|':
                        if(neighbor(x,y,'#')>=3){
                            t[y][x] = '#';
                        }else{
                            t[y][x] = '|';
                        }
                        break;
                    case '#':
                        if(neighbor(x,y,'#')>=1 && neighbor(x,y,'|')>=1){
                            t[y][x] = '#';
                        }else{
                            t[y][x] = '.';
                        }
                        break;
                }

        min++;
        if(min == 524){
            cout<<"Skipping iterations"<<endl;
            min+=28*35714000;
        }
        g = t;
        visited[g].push_back(min);
        //for(auto& c:visited[g]){
        //    cout<<c<<" ";
        //}cout<<endl;
    }
    //200349 too low
    //202806
    //Loops every 28

    int part1(){
        int w(0),l(0);
        for(auto& v:g){
            for(auto& c:v){
                if(c=='|'){
                    w++;
                }
                if(c=='#'){
                    l++;
                }
            }
        }
        cout<<"Wood: "<<w<<endl;
        cout<<"Logging: "<<l<<endl;
        return w*l;
    }
};

int main(){
    Grid g;
    g.print();
    for(;g.min<1000000000;){
        if((g.min+1)%1000 == 0){
            cout<<"min: "<<g.min+1<<endl;
        }
        g.iter();
    }
    g.print();
    cout<<"Resource score of "<<g.part1()<<endl;
}