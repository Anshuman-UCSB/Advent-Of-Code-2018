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
    void turn(){
        switch(intersection){
            case 0:
            dir+=3; break;
            case 2:
            dir+=1;
            break;
        }
        dir%=4;
        intersection++;
        intersection%=3;
    }
};


class Grid{
    int count = -1;
    vector<string> inp;
    vector<vector<char> > grid;
    vector<vector<Cart*> > carts;
    vector<vector<Cart*> > temp;
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
        temp = vector<vector<Cart*> >(l, vector<Cart* >(w, 0));
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
    
    void iter2(){
        if(count == 1){
            return;
        }
        temp = vector<vector<Cart*> >(grid.size(), vector<Cart* >(grid[0].size(), 0));
        for(int y = 0;y<grid.size();y++){
            for(int x = 0;x<grid[0].size();x++){
                if(carts[y][x]){
                    //if theres a cart at this position
                    int nX, nY;
                    switch(carts[y][x]->dir){
                        case 0: nX = x; nY = y-1; break;
                        case 1: nX = x+1; nY = y; break;
                        case 2: nX = x; nY = y+1; break;
                        case 3: nX = x-1; nY = y; break;
                        default: break;
                    }
                    bool crash = false;
                    if(temp[y][x] || temp[nY][nX]){
                        //There already is a cart where this one should be, meaning it crashed
                        temp[y][x] = 0;
                        temp[nY][nX] = 0;
                        carts[y][x] = 0;
                        carts[nY][nX] = 0;
                        cout<<"(temp) Crash found at "<<nX<<","<<nY<<endl<<endl;
                        crash = true;
                        continue;
                    }
                    if(carts[nY][nX]){
                        temp[y][x] = 0;
                        temp[nY][nX] = 0;
                        carts[y][x] = 0;
                        carts[nY][nX] = 0;
                        cout<<"(temp) Crash found at "<<nX<<","<<nY<<endl<<endl;
                        crash = true;
                        continue;
                    }
                    switch(grid[nY][nX]){
                        case '+':
                            carts[y][x]->turn();                           
                            break;
                        case '/':
                            switch(carts[y][x]->dir){
                                case 0:
                                    carts[y][x]->dir = 1;
                                    break;
                                case 1:
                                    carts[y][x]->dir = 0;
                                    break;
                                case 2:
                                    carts[y][x]->dir = 3;
                                    break;
                                case 3:
                                    carts[y][x]->dir = 2;
                                    break;
                            }
                            break;
                        case '\\':
                            switch(carts[y][x]->dir){
                                case 0:
                                    carts[y][x]->dir = 3;
                                    break;
                                case 1:
                                    carts[y][x]->dir = 2;
                                    break;
                                case 2:
                                    carts[y][x]->dir = 1;
                                    break;
                                case 3:
                                    carts[y][x]->dir = 0;
                                    break;
                            }
                            break;
                    }
                    if(!crash){
                        temp[nY][nX] = carts[y][x];
                        carts[y][x] = 0;
                    }
                }
            }
        }
        count = 0;
        for(int y = 0;y<carts.size();y++){
            for(int x = 0;x<carts[0].size();x++){
                carts[y][x] = temp[y][x];
                if(temp[y][x] != 0){
                    count++;
                }
            }
        }
        //wasn't 74,29
        if(count == 1){
            for(int y = 0;y<carts.size();y++){
                for(int x = 0;x<carts[0].size();x++){
                    if(carts[y][x]){
                        cout<<"Last cart at: "<<x<<","<<y<<endl;
                        return;
                    }
                }
            }
        }
    }

    void iter(){
        temp = vector<vector<Cart*> >(grid.size(), vector<Cart* >(grid[0].size(), 0));
        for(int y = 0;y<grid.size();y++){
            for(int x = 0;x<grid[0].size();x++){
                if(carts[y][x]){
                    //if theres a cart at this position
                    int nX, nY;
                    switch(carts[y][x]->dir){
                        case 0: nX = x; nY = y-1; break;
                        case 1: nX = x+1; nY = y; break;
                        case 2: nX = x; nY = y+1; break;
                        case 3: nX = x-1; nY = y; break;
                        default: break;
                    }
                    if(temp[y][x] || temp[nY][nX]){
                        //There already is a cart where this one should be, meaning it crashed
                        cout<<"(temp) Crash found at "<<nX<<","<<nY<<endl<<endl;
                        string line;
                        cin>>line;
                    }
                    if(carts[nY][nX]){
                        //Crash
                        cout<<"(carts) Crash found at "<<nX<<","<<nY<<endl<<endl;
                        string line;
                        cin>>line;
                        //manual pause lol
                    }
                    switch(grid[nY][nX]){
                        case '+':
                            carts[y][x]->turn();                           
                            break;
                        case '/':
                            switch(carts[y][x]->dir){
                                case 0:
                                    carts[y][x]->dir = 1;
                                    break;
                                case 1:
                                    carts[y][x]->dir = 0;
                                    break;
                                case 2:
                                    carts[y][x]->dir = 3;
                                    break;
                                case 3:
                                    carts[y][x]->dir = 2;
                                    break;
                            }
                            break;
                        case '\\':
                            switch(carts[y][x]->dir){
                                case 0:
                                    carts[y][x]->dir = 3;
                                    break;
                                case 1:
                                    carts[y][x]->dir = 2;
                                    break;
                                case 2:
                                    carts[y][x]->dir = 1;
                                    break;
                                case 3:
                                    carts[y][x]->dir = 0;
                                    break;
                            }
                            break;
                    }
                    
                    temp[nY][nX] = carts[y][x];
                    carts[y][x] = 0;
                }
            }
        }
        for(int y = 0;y<carts.size();y++){
            for(int x = 0;x<carts[0].size();x++){
                carts[y][x] = temp[y][x];
            }
        }
    }


};

#endif