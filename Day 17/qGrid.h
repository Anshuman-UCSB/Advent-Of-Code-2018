#ifndef QGRID
#define QGRID

#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Coord{
    int x, y;
    Coord(int i, int j):x(i),y(j){}
    Coord(){x = -1; y = -1;}
}; 

class qGrid{
    public:
    queue<Coord> q;
    vector<vector<char>> map = vector<vector<char>>(5, vector<char>(1200,'.'));
    qGrid(){
        fstream file("input.txt");
        string line;
        vector<char> empty_row = map[0];
        while(getline(file,line)){
            int xl, xr, yl, yr;
            if(line[0] == 'x'){
                xl = xr = stoi(line.substr(2,line.find(",")));
                yl = stoi(line.substr(line.find("y=")+2,line.find(",")));
                yr = stoi(line.substr(line.find("..")+2));
            }
            else{
                yl = yr = stoi(line.substr(2,line.find(",")));
                xl = stoi(line.substr(line.find("x=")+2,line.find(",")));
                xr = stoi(line.substr(line.find("..")+2));
            }
            map[0][500] = '+';
            map[1][500] = '|';
            for(int y = yl;y<=yr;y++){
                for(int x = xl;x<=xr;x++){
                    while(map.size()<yr+1){
                        map.push_back(empty_row);
                    }
                    map[y][x] = '#';
                }
            }
        }
        file.close();
    }

    void update(Coord c){
        char loc = map[c.y][c.x];
        if(loc != '|' || c.y == map.size()-1){
            return;
        }
        //assume by here loc == '|'
        q.push(Coord(c.x,c.y+1));


        if(map[c.y+1][c.x]=='.' || map[c.y+1][c.x] == '|'){
            map[c.y+1][c.x] = '|';
            q.push(Coord(c.x+1,c.y+1));
            q.push(Coord(c.x-1,c.y+1));
        }else{
            if(map[c.y][c.x-1]=='.'){
                map[c.y][c.x-1]='|';
                q.push(Coord(c.x+1,c.y));
                q.push(Coord(c.x-1,c.y));
            }
            if(map[c.y][c.x+1]=='.'){
                map[c.y][c.x+1]='|';
                q.push(Coord(c.x+1,c.y));
                q.push(Coord(c.x-1,c.y));
            }
        }
        bool right = false;
        bool left = false;
        if(map[c.y+1][c.x] != '|' && map[c.y+1][c.x] != '.'){
            for(int i = c.x;map[c.y+1][i]!='.';i++){
                if(map[c.y][i] == '#' || map[c.y][i]=='~'){
                    right = true;
                    break;
                }
            }
            for(int i = c.x;map[c.y+1][i]!='.';i--){
                if(map[c.y][i] == '#' || map[c.y][i]=='~'){
                    left = true;
                    break;
                }
            }
            if(right && left){
                map[c.y][c.x] = '~';
                q.push(Coord(c.x,c.y-1));
                q.push(Coord(c.x+1,c.y));
                q.push(Coord(c.x-1,c.y));
            }
        }
    }

    void play(){
        q.empty();
        Coord c;
        int last = -1;
        int score = 0;
        while(last != score){
            last = score;
            q.push(Coord(500,1));
            while(!q.empty()){
                c =q.front();
                //cout<<"Updating "<<c.x<<", "<<c.y<<endl;
                update(c);
                q.pop();
            }
            score = sum();
            cout<<"Rebooting... current score is "<<score<<endl;
            cout<<"Rebooting... last score was "<<last<<endl;
        }
    }

    void printMap(){
        for(int y = 0;y<map.size() && y<20;y++){
            for(int x = 490;x<510;x++){
                cout<<map[y][x];
            }cout<<endl;
        }
    }
    int sum(){
        int out = 0;
        for(int y = 0;y<map.size();y++){
            for(int x = 0;x<map[0].size();x++){
                if(map[y][x] == '|' || map[y][x] == '~'){
                    out++;
                }
            }
        }
        return out;
    }

    void writeToFile(){
        ofstream out("out.txt");

        for(auto& v:map){
            for(auto& c:v){
                if(c!='.')
                    out<<c;
                else
                    out<<" ";
            }out<<endl;
        }


        out.close();
    }
};

void qGrid1(){
    qGrid grid;
    grid.printMap();
    grid.play();
    grid.printMap();
    cout<<"Final score of "<<grid.sum()<<endl;
    grid.writeToFile();
}
//Too low 4759, 24058
//30000
//Too high 33728
#endif