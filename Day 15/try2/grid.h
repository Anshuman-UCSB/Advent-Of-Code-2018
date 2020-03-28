#ifndef GRID
#define GRID
#include "unit.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Grid{
    public:
    vector<vector<Unit*> > g;
    vector<vector<int> > d;
    int dx[4] = {0,1,0,-1};
    int dy[4] = {-1,0,1,0};
    Grid(){
        g.clear();
    }
    Grid(string inp){
        string line;
        fstream file = fstream(inp.c_str());
        int id = 1;
        while(getline(file,line)){
            g.push_back(vector<Unit*>());
            for(int i = 0;i<line.size()-1;i++){
                g[g.size()-1].push_back(new Unit(line[i], id++));
            }
        }
    }

    void print(){
        cout<<endl<<"  ";
        for(int x = 0;x<g[0].size();x++){
            cout<<x%10;
        }cout<<endl;
        for(int y = 0;y<g.size();y++){
            cout<<y%10<<" ";
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->id == 'G')
                    cout << "\033[1;"<<(31)<<"m"<<g[y][x]->id<<"\033[0m";
                else if(g[y][x]->id == 'E')
                    cout << "\033[1;"<<(32)<<"m"<<g[y][x]->id<<"\033[0m";
                else
                    cout<<g[y][x]->id;
            }cout<<endl;
        }
        cout<<endl;
    }
    void printDist(){
        cout<<endl<<"  ";
        for(int x = 0;x<g[0].size();x++){
            cout<<x%10;
        }cout<<endl;
        for(int y = 0;y<d.size();y++){
            cout<<y%10<<" ";
            for(int x = 0;x<d[0].size();x++){
                if(d[y][x] == -5)
                    cout << " ";
                else if(d[y][x] == -3)
                    cout << "E";
                else if(d[y][x] == -4)
                    cout << "G";
                else if(d[y][x] == -2)
                    cout << ".";
                else if(d[y][x] == -1)
                    cout << "#";
                else if(d[y][x] == 0)
                    cout << "@";
                else
                    cout << "\033[1;"<<(31+d[y][x]%6)<<"m"<<d[y][x]%10<<"\033[0m";

            }cout<<endl;
        }
        cout<<endl;
    }

    bool canAtk(int x, int y){
        char enem = g[y][x]->id == 'E'?'G':'E';
        for(int i = 0;i<4;i++){
            if(g[y+dy[i]][x+dx[i]]->id == enem){
                return true;
            }
        }
        return false;
    }

    void move(int x, int y, int dir){
        //0 up, 1 right, 2 down, 3 left
        Unit* temp= g[y][x];
        g[y][x] = g[y+dy[dir]][x+dx[dir]];
        g[y+dy[dir]][x+dx[dir]] = temp;
    }

    void updateDist(int x, int y){
        int enem = g[y][x]->id == 'E'?-4:-3;
        d = vector<vector<int> >(g.size(), vector<int>(g[0].size(),-5));
        //-2 is space, -1 wall, 0 is center
        for(int y = 0;y<g.size();y++){
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->id == '#'){
                    d[y][x] = -1;
                }else if(g[y][x]->id == '.'){
                    d[y][x] = -2;
                }else if(g[y][x]->id == 'E'){
                    d[y][x] = -3;
                }else if(g[y][x]->id == 'G'){
                    d[y][x] = -4;
                } else{
                    d[y][x] = -5;
                }
            }
        }
        d[y][x] = 0;
        bool change = true;
        int cur = 0;
        while(change){
            change = false;
            for(int y = 0;y<g.size();y++){
                for(int x = 0;x<g[0].size();x++){
                    if(d[y][x] == cur){
                        for(int i= 0;i<4;i++){
                            if(d[y+dy[i]][x+dx[i]] == -2 || d[y+dy[i]][x+dx[i]] == enem){
                                d[y+dy[i]][x+dx[i]] = cur+1;
                                change = true;
                            }
                        }
                    }
                }
            }
            cur++;
        }
    }

    Coord getClosest(int x, int y){
        updateDist(x,y);
        char enem = g[y][x]->id == 'G'?'E':'G';
        int minDist = 99999;
        int ax(-1), ay(-1);
        for(int y = 0;y<d.size();y++){
            for(int x = 0;x<d[0].size();x++){
                if(g[y][x]->id!=enem){
                    continue;
                }
                //x,y is an enemy
                int dist = d[y][x] <= 0? 99999: d[y][x];
                if(dist<minDist){
                    minDist = dist;
                    ax = x;
                    ay = y;
                    x = 0;
                    y = 0;
                }
            }
        }
        return Coord(ax,ay);
    }

    
};


#endif