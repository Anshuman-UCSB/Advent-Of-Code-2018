#include <iostream>
#include <fstream>
#include <vector>
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

int getTotalDist(Coord c1, vector<Coord> coords){
    int sum = 0;
    for(int i =0;i<coords.size();i++){
        sum+=getDist(c1, coords[i]);
    }
}

int getDist(Coord c1, Coord c2){
    int deltaX = abs(c1.x-c2.x);
    int deltaY = abs(c1.y-c2.y);
    return deltaX+deltaY;
}

void evalGrid(char grid[365][365], vector<Coord> coords, int range){
    for(int y = 0;y<365;y++){
        for(int x= 0;x<365;x++){
            if(grid[y][x] != '#'){
                Coord c(x,y);
            }
        }
    }
}


void printGrid(char grid[365][365]){
    ofstream file("day6_2out.txt");

    for(int i = 0;i<365;i++){
        for(int j = 0;j<365;j++){
            cout<<grid[i][j];
            file<<grid[i][j];
        }cout<<endl;
        file<<endl;
    }
    file.close();
}

int main(){
    fstream file("day6.txt");
    string line;
    vector<Coord> coords;

    while(getline(file,line)){
        coords.push_back(Coord(line));
    }

    for(int i = 0;i<coords.size();i++){
        cout<<i<<": "<<coords[i].x<<", "<<coords[i].y<<endl;
    }

    char grid[365][365];
    for(int i = 0;i<365;i++){
        for(int j = 0;j<365;j++){
            grid[j][i] = '.';
        }
    }

    for(int i = 0;i<coords.size();i++){
        grid[coords[i].y][coords[i].x] = '#';
    }
    printGrid(grid);

}