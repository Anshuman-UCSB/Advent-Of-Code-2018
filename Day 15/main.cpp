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
    for(char num = '2';num<'0'+CALC;num++){
        for(int y = 0;y<m.size();y++){
            for(int x = 0;x<m[0].size();x++){
                if(m[y][x] == num-1){
                    for(int i = 0;i<4;i++){
                        try{
                            if(m[y+dy[i]][x+dx[i]] == '.'){
                                m[y+dy[i]][x+dx[i]] = num;
                            }
                        }
                        catch(...){}
                    }
                }
            }
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

void print(vector<Character>& c){
    for(int i = 0;i<c.size();i++){
        cout<<c[i].type<<"["<<c[i].hp<<"] at ("<<c[i].x<<", "<<c[i].y<<")"<<endl;
    }
}

void part1(){
    grid raw = parseRaw();
    grid map = parseMap(raw);
    charGrid g(parseGoblin(raw)), e(parseElf(raw));

    printVector(raw);
    printVector(map);
    print(g);
    print(e);
    printVector(distGrid(map, 2,2));
}
