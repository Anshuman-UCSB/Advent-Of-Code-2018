#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "grid.h"
using namespace std;


struct Coord{
    int x, y;

    Coord(){
        x = -1;
        y = -1;
    }

    Coord(int ix, int iy){
        x = ix;
        y = iy;
    }
};

struct Particle{
    Coord coord;
    int xVel;
    int yVel;

    Particle(string inp){

        //position=< 9,  1> velocity=< 0,  2>
        string temp = inp;
        temp = temp.substr(temp.find("=<")+2);
        coord.x = stoi(temp.substr(0,temp.find(",")));
        temp = temp.substr(temp.find(",")+1);
        coord.y = stoi(temp.substr(0,temp.find(">")));
        temp = temp.substr(temp.find("=<")+2);
        xVel = stoi(temp.substr(0,temp.find(",")));

        temp = temp.substr(temp.find(",")+1);
        yVel = stoi(temp.substr(0,temp.find(">")));
    }

};

#define SCALE 100

void paint(Grid<char>& grid, const vector<Particle>& parts, int t){
    for(int i = 0;i<grid.grid.size();i++){
        for(int j = 0;j<grid.grid[0].size();j++){
            grid.grid[i][j] = '.';
        }
    }
    for(Particle p: parts){
        grid.grid[(p.coord.y+p.yVel*t)/1000+grid.yCen][(p.coord.x+p.xVel*t)/1000+grid.xCen] = '#';
    }
}

int main(){
    string line;
    vector<Particle> parts;
    fstream file("day10.txt");
    while(getline(file, line)){
        parts.push_back(Particle(line));
    }
    Grid<char> grid = Grid<char>('.');
    grid.extend(120000/1000,120000/1000);
    grid.setCen(60000/1000,60000/1000);
    int i = 0;
    while(true){
        paint(grid, parts, i++);
        grid.file();
        cin>>line;
    }
}