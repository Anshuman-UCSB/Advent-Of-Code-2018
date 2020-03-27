#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Cart{
    public:
    int dir; //0 is up 1 is right 2 is down 3 is left
    int intersection; //0 is left, 1 is straight, 1 is right
    Cart(){
        dir = 0;
        intersection = 0;
    }
    Cart(char raw){
        intersection = 0;
        switch(raw){
            case '^':
            dir = 0;
            break;
            case '>':
            dir = 1;
            break;
            case 'v':
            dir = 2;
            break;
            case '<':
            dir = 3;
            break;
        }
    }
    int turn(){
        return intersection++%3;
    }
};


class Grid{
    vector<string> inp;
    vector<vector<char> > grid;
    vector<vector<Cart*> > carts;
    public:
    Grid(){
        string line;
        fstream file("input.txt");
        
        while(getline(file,line)){
            inp.push_back(line);
        }
        int l,w;
        l = inp.size();
        w = inp[0].size();
        grid = vector<vector<char> >(l, vector<char>(w, ' '));
        carts = vector<vector<Cart*> >(l, vector<Cart* >(w, 0));
        for(int i= 0;i<inp.size();i++){
            for(int j = 0;j<inp[i].size();j++){
                if(inp[i][j]=='^' || inp[i][j]=='v'){
                    carts[i][j] = new Cart(inp[i][j]);
                    grid[i][j] = '|';
                } else if(inp[i][j]=='>' || inp[i][j]=='<'){
                    grid[i][j] = '-';
                    carts[i][j] = new Cart(inp[i][j]);
                } else{
                    grid[i][j] = inp[i][j];
                }
            }
        }
    }

    void print(){
        char dirs[4] = {'^','>','v','<'};
        cout<<"  ";
        for(int i = 0;i<grid[0].size();i++){
            cout<<i%10;
        }cout<<endl;
        for(int y = 0;y<grid.size();y++){
            cout<<y%10<<" ";
            for(int x =0;x<grid[0].size();x++){
                if(carts[y][x] != 0)
                    cout<<dirs[carts[y][x]->dir];
                else
                    cout<<grid[y][x];
            }cout<<endl;
        }
        
    }
    
    void iter(){
        for(int y = 0;y<grid.size();y++){
            for(int x = 0;x<grid[0].size();x++){
                
            }
        }
    }


};

#endif