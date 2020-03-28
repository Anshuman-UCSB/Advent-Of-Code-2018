#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


typedef vector<vector<char> > grid;

struct Character{
    int hp,dmg;
    int x,y;
    char type;
    Character(int h, int d, char t, int xi, int yi):hp(h), dmg(d), type(t), x(xi), y(yi){}
    Character(){}
};
typedef vector<Character> charGrid;

int ctoi(char c){
    return c-'0';
}

grid distGrid(grid& map, int x, int y){
    grid m(map.size(), vector<char>(map[0].size(),'.'));
    int CALC = 10; //Size to calculate up to
    for(int i = 0;i<m.size();i++){
        for(int j = 0;j<m[0].size();j++){
            m[i][j] = map[i][j];
        }
    }
    //m is copy of map
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    m[y][x] = '@';
    for(int i = 0;i<4;i++){
        try{
            if(m[y+dy[i]][x+dx[i]] == '.'){
                m[y+dy[i]][x+dx[i]] = '1';
            }
        }
        catch(...){}
    }
    bool found1;
    for(char num = '2';;num++){
        found1 = false;
        for(int y = 0;y<m.size();y++){
            for(int x = 0;x<m[0].size();x++){
                if(m[y][x] == num-1){
                    for(int i = 0;i<4;i++){
                        try{
                            if(m[y+dy[i]][x+dx[i]] == '.'){
                                found1 = true; //Found a new num
                                m[y+dy[i]][x+dx[i]] = num;
                            }
                        }
                        catch(...){}
                    }
                }
            }
        }
        if(!found1){
            break;
        }
    }
    return m;
}

void part1();
int main(){
    part1();
}

grid parseRaw(){
    string line;
    fstream file("input.txt");
    grid raw;
    while(getline(file,line)){
        raw.push_back(vector<char>());
        for(int i= 0;i<line.size()-1;i++){
            raw[raw.size()-1].push_back(line[i]);
        }
    }
    return raw;
}

grid parseMap(grid& r){
    grid m(r.size(), vector<char>(r[0].size(),'.'));
    for(int y = 0;y<r.size();y++){
        for(int x = 0;x<r[0].size();x++){
            if(r[y][x] == '#'){
                m[y][x] = '#';
            }
        }
    }
    return m;
}

charGrid parseElf(grid& r){
    charGrid e;
    for(int y = 0;y<r.size();y++){
        for(int x = 0;x<r[0].size();x++){
            if(r[y][x] == 'E'){
                e.push_back(Character(200, 3, 'E', x, y));
            }
        }
    }
    return e;
}

charGrid parseGoblin(grid& r){
    charGrid g;
    for(int y = 0;y<r.size();y++){
        for(int x = 0;x<r[0].size();x++){
            if(r[y][x] == 'G'){
                g.push_back(Character(200, 3, 'G', x, y));
            }
        }
    }
    return g;
}

void printVector(grid v){
    cout<<"\n  ";
    for(int x = 0;x<v[0].size();x++){
            cout<<x%10;
    }cout<<endl;
    for(int y = 0;y<v.size();y++){
        cout<<y%10<<" ";
        for(int x = 0;x<v[0].size();x++){
            if(v[y][x] <'8' && v[y][x]>='0'){
                cout << "\033[1;"<<(30+ctoi(v[y][x]))<<"m"<<v[y][x]<<"\033[0m";
            } else
                cout<<v[y][x];
        }cout<<endl;
    }
    cout<<endl;
}

int distance(grid& distMap, Character c1){
    return distMap[c1.y][c1.x];
}

Character getClosest(grid& map, Character c, charGrid e){
    int min = 999999;
    grid dist = distGrid(map, c.x,c.y);
    Character out;
    for(int i = 0;i<e.size();i++){
        if(distance(dist,e[i])<=min){
            if(distance(dist,e[i]) == min){
                if(out.y == e[i].y){
                    if(out.x<e[i].x){
                        continue;
                    }
                }
                if(out.y<e[i].y){
                    continue;
                }
                
            }
            min = distance(dist,e[i]);
            out = e[i];
        }
    }
    return out;
}

grid makeMap(grid map, charGrid& c, charGrid& g){
    for(int i = 0;i<c.size();i++){
        map[c[i].y][c[i].x] = 'E';
    }
    for(int i = 0;i<g.size();i++){
        map[g[i].y][g[i].x] = 'G';
    }
    return map;    
}

bool canAtk(grid& active, Character c){
    char eType = 'E';
    if(c.type == 'E'){
        eType = 'G';
    }
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    for(int i = 0;i<4;i++){
        try{
            if(active[c.y+dy[i]][c.x+dx[i]] == eType){
                return true;
            }
        } catch(...){}
    }
    return false;
}

void print(vector<Character>& c){
    for(int i = 0;i<c.size();i++){
        cout<<c[i].type<<"["<<c[i].hp<<"] at ("<<c[i].x<<", "<<c[i].y<<")"<<endl;
    }
}


/*
Current methods:
    print(vector<Char>) prints out vector of Characters
    printVector(vector<vector<char> >) prints out 2d vector, colors nums 0-9
    int ctoi(char) returns '8' to 8

    grid parseRaw() reads from input to a 2d grid
    grid parseMap(raw) reads from raw to make grid of just the map
    vect parseElf(raw) returns vector of only elf characters
    vect parseGoblin(raw) returns vector of only goblin characters
    
    grid distGrid(map, x, y) returns a grid of distances from some x, y
    int distance(distMap, character) returns the distance on distmap for character
    character getClosest(map, character, enemies) returns closest enemy to character on map

    grid makeMap(map, c, g) compounds all submaps to make one visual map
    
    bool canAtk(active, c) returns true if enemy is able to be attacked for c
*/

void part1(){
    grid raw = parseRaw();
    grid map = parseMap(raw);
    charGrid g(parseGoblin(raw)), e(parseElf(raw));

    print(g);
    print(e);
    // Character min = getClosest(map, g[3],e);
    // cout<<min.x<<", "<<min.y<<endl;
    grid activeMap(makeMap(map,e,g));
    // cout<<canAtk(activeMap,g[3])<<endl;
    printVector(activeMap);
    //printVector(distGrid(map, 2,2));
}
