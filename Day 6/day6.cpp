#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;

struct Coord{
    int x;
    int y;

    Coord(){
        x = y = 0;
    }
    Coord(int xin, int yin){
        x = xin;
        y = yin;
    }

    Coord(string inp){
        x = stoi(inp.substr(0,inp.find(", ")));
        y = stoi(inp.substr(2+inp.find(", ")));
    }
};



void expandGrid(vector<vector<char>>& grid, int x, int y){
    for(int i = 0;i<x;i++){
        for(int row = 0;row<grid.size();row++){
            grid[row].push_back('.');
        }
    }
    for(int i = 0;i<y;i++){
        grid.push_back(vector<char>());
        for(int j = 0;j<grid[0].size();j++){
            grid[grid.size()-1].push_back('.');
        }
    }
}

void printGrid(const vector<vector<char>>& grid){
    for(int y = 0; y<grid.size();y++){
        for(int x = 0;x<grid[0].size();x++){
            cout<<grid[y][x];
        }cout<<endl;
    }
}

void addCoord(vector<vector<char>>& grid, int x, int y, char id){
    if(x>grid[0].size()){
        expandGrid(grid, x-grid[0].size()+2,0);
    }
    if(y>grid.size()){
        expandGrid(grid, 0, y-grid.size()+2);
    }

    grid[y][x] = id;
}

int getDist(Coord c1, Coord c2){
    int deltaX = abs(c1.x-c2.x);
    int deltaY = abs(c1.y-c2.y);
    return deltaX+deltaY;
}

void evalGrid(vector<Coord> coords, vector<vector<char>> &grid){
    int* arr = new int(coords.size());
    int min = 10000000;
    int ind;
    bool dupe;
    for(int x =0;x<grid[0].size();x++){
        for(int y = 0;y<grid.size();y++){
            if(grid[y][x] == '.'){
                min = 1000000;
                dupe = true;
                Coord c(x,y);
                for(int i = 0;i<coords.size();i++){
                    arr[i] = getDist(c, coords[i]);
                    if(arr[i]<min){
                        ind = i;
                        min = arr[i];
                        dupe = false;
                    } else if (arr[i] == min){
                        dupe = true;
                    }
                }

                if(dupe){
                    addCoord(grid,c.x,c.y,'.');
                } else {
                    addCoord(grid,c.x,c.y,'a'+ind);
                }
                
            }
        }
    }
}

int getArea(vector<vector<char>> &grid, char search){
    int sum = 1;    //account for starting coord
    for(unsigned int i = 0;i<grid.size();i++){
        for(unsigned int j = 0;j<grid[0].size();j++){
            if(grid[i][j] == search){
                sum++;
            }
        }
    }
    return sum;
}

bool isInfinite(vector<vector<char>> &grid, char search){
    for(unsigned int i = 0;i<grid.size();i++){
        if(grid[i][0] == search){
            return true;
        }
        if(grid[i][grid[0].size()-1] == search){
            return true;
        }
    }
    for(unsigned int i = 0;i<grid.size();i++){
        if(grid[0][i] == search){
            return true;
        }
        if(grid[grid.size()-1][i] == search){
            return true;
        }
    }
    return false;
}

int main(){
    string line;
    fstream file("day6.txt");
    vector<string> data;
    vector<Coord> coords;
    while(getline(file, line)){
        data.push_back(line);
    }

    int maxX(0), maxY(0);
    
    for(unsigned int i = 0;i<data.size();i++){
        coords.push_back(Coord(data[i]));
    }

    //Initializing grid
    vector<vector<char>>grid;
    grid.push_back(vector<char>());
    grid[0].push_back('.');
    //Done initializing Grid

    expandGrid(grid, 4, 4);
    char id = 'A';
    for(int i = 0;i<coords.size();i++){
        addCoord(grid,coords[i].x,coords[i].y,id+i);
    }
    printGrid(grid);
    
    //getDist(c1, c2) returns manhattan distance
    evalGrid(coords,grid);
    cout<<"################"<<endl;
    printGrid(grid);
    char check = 'a';
    cout<<"Area of "<<check<<" is "<<getArea(grid, check)<<endl;
    if(isInfinite(grid,check)){
        cout<<check<<" is infinite."<<endl;
    } else{
        cout<<check<<" is not infinite."<<endl;
    }
}