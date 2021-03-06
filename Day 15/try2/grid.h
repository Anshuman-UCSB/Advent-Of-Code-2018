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
    int dx[4] = {0,-1,1,0};
    int dy[4] = {-1,0,0,1};
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
                else if(d[y][x] < 10)
                    cout << "\033[1;"<<(31+d[y][x]%6)<<"m"<<d[y][x]%10<<"\033[0m";
                else
                    cout<<" ";

            }cout<<endl;
        }
        cout<<endl;
    }

    bool canMove(int x, int y){
        for(int i =0;i<4;i++){
            if(g[y+dy[i]][x+dx[i]]->id == '.'){
                return true;
            }
        }
        return false;
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

    void atk(int x, int y){
        char enem;
        if (g[y][x]->id=='G'){
            enem = 'E';
        } else if (g[y][x]->id == 'E'){
            enem = 'G';
        }
        Unit* target = new Unit('T',-1);
        target->hp = 201;
        if(g[y][x]->hp>0){
            if(g[y-1][x]->id == enem){
                target = g[y-1][x];
            }
            if(g[y][x-1]->id == enem && g[y][x-1]->hp<target->hp){
                target = g[y][x-1];
            }
            if(g[y][x+1]->id == enem && g[y][x+1]->hp<target->hp){
                target = g[y][x+1];
            }
            if(g[y+1][x]->id == enem && g[y+1][x]->hp<target->hp){
                target = g[y+1][x];
            }
        }
        target->hp-=g[y][x]->dmg;
        // cout<<g[y][x]->toStr()<<" attacked "<<target->toStr()<<endl;
        if(target->hp<=0){
            Coord c = find(target->uniqueId);
            g[c.y][c.x]->id='.';
            g[c.y][c.x]->hp = 0;
            g[c.y][c.x]->dmg = 0;
            g[c.y][c.x]->uniqueId = -1;
        }
    }

    void updateDist(int x, int y){
        d = vector<vector<int> >(g.size(), vector<int>(g[0].size(),-5));
        //-2 is space, -1 wall, 0 is center
        for(int y = 0;y<g.size();y++){
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->id == '#'){
                    d[y][x] = -1;
                }else if(g[y][x]->id == '.'){
                    d[y][x] = -2;
                }else if(g[y][x]->id == 'E'){
                    d[y][x] = -2;
                }else if(g[y][x]->id == 'G'){
                    d[y][x] = -2;
                } else{
                    d[y][x] = -5;
                }
            }
        }
        d[y][x] = 0;
        for(int i= 0;i<4;i++){
            //if adjacent spot is 
            if(d[y+dy[i]][x+dx[i]] == -2){
                d[y+dy[i]][x+dx[i]] = 1;
            }
        }
        bool change = true;
        int cur = 1;
        while(change){
            change = false;
            for(int y = 0;y<g.size();y++){
                for(int x = 0;x<g[0].size();x++){
                    if(d[y][x] == cur && g[y][x]->id == '.'){
                        for(int i= 0;i<4;i++){
                            //if adjacent spot is 
                            if(d[y+dy[i]][x+dx[i]] == -2){
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

    int getMove(int x, int y){
        Coord target = getClosest(x,y);
        if(target.y == -1 && target.x == -1){
            cout<<g[y][x]->toStr()<<" Was not able to find a path!"<<endl;
            return -1;
        }
        updateDist(target.x,target.y);
        int dir = -1;
        int min = 99999;
        for(int i= 0;i<4;i++){
            int dist = d[y+dy[i]][x+dx[i]]<=0?99999:d[y+dy[i]][x+dx[i]];
            if(dist<min && g[y+dy[i]][x+dx[i]]->id == '.'){
                dir = i;
                min = dist;
            }
        }
        return dir;
    }


    int sumGame(){
        int out = 0;
        bool hasG(false), hasE(false);
        for(int y = 0;y<g.size();y++){
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->id == 'G'){
                    hasG = true;
                }
                if(g[y][x]->id == 'E'){
                    hasE = true;
                }
                if(hasG && hasE){
                    return -1;
                }
            }
        }
        if(hasG || hasE){
            char find = hasG?'G':'E';
            for(int y = 0;y<g.size();y++){
                for(int x = 0;x<g[0].size();x++){
                    if(g[y][x]->id == find){
                        out+=g[y][x]->hp;
                    }
                }
            }
        }
        return out;
    }

    void takeTurn(int x,int y){
        Unit* target = g[y][x];
        if(!canAtk(x,y)) {//if you can't attack
            if(canMove(x,y)){
                int dir = getMove(x,y);
                if(dir == -1){
                    return;
                }
                move(x,y,dir);
            }
        }
        Coord c = find(target->uniqueId);
        if(canAtk(c.x,c.y)){
            // cout<<target->toStr()<<" is at "<<c.x<<", "<<c.y<<endl;
            atk(c.x,c.y);
            // cout<<"ATTACKING"<<endl;
        }

    }

    Coord findId(int uq){
        for(int y = 0;y<g.size();y++){
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->uniqueId == uq){
                    return Coord(x,y);
                }
            }
        }
        return Coord(-1,-1);
    }

    void printUnits(){
        for(int y = 0;y<g.size();y++){
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->id == 'G' || g[y][x]->id == 'E'){
                    cout<<g[y][x]->toStr()<<endl;
                }
            }
        }
    }

    vector<int> getOrder(){
        vector<int> order;
        for(int y = 0;y<g.size();y++){
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->id == 'G' || g[y][x]->id == 'E'){
                    order.push_back(g[y][x]->uniqueId);
                }
            }
        }
        return order;
    }

    Coord find(int uq){
        for(int y = 0;y<g.size();y++){
            for(int x = 0;x<g[0].size();x++){
                if(g[y][x]->uniqueId==uq){
                    return Coord(x,y);
                }
            }
        }
        cout<<"DID NOT FIND UNIQUE ID!!"<<endl;
        return Coord(-1,-1);
    }

    void iter(){
        vector<int> order = getOrder();
        
        for(int i = 0;i<order.size();i++){
            Coord c = find(order[i]);
            if(c.y == -1 && c.x == -1){
                cout<<"Could not find character for move"<<endl;
                continue;
            }
            // cout<<"Moved "<<order[i]<<" at "<<c.x<<", "<<c.y<<endl;
            takeTurn(c.x,c.y);
        }
        
    }

    int play(){
        int gen = 0;
        do{
            gen++;
            cout<<"Generation: "<<gen<<endl;
            iter();
            print();
            printUnits();
        }while(sumGame()==-1);
        cout<<"gameSum: "<<sumGame()<<endl;
        cout<<"Final gen is "<<gen<<endl;
        return gen*sumGame();
    }


};


#endif