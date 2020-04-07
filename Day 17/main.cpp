#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "qGrid.h"
using namespace std;
using vector2d = vector<vector<char>>;

void part1();
void part1queue();
int main(){
    //part1();
    qGrid1();
}

void print(vector<char> v){
    for(char& c:v){
        cout<<c;
    }
}
void print(vector2d map){
    int l = map.size();
    int w = map[0].size()-500;
    cout<<"  ";
    for(int i = -w/2+501;i<w/2+500;i++){
        cout<<i%10;
    }cout<<endl;

    for(int i = 0;i<l;i++){
        cout<<i%10<<" ";
        for(int j = -w/2+501;j<w/2+500;j++){
            cout<<map[i][j];
        }cout<<endl;
    }

}

int inputBounds(){
    string line;
    fstream file("input.txt");
    int maxY = -1;
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
        maxY = max(maxY, yr);
    }
    file.close();
    cout<<maxY+1<<endl;
    return maxY+1;
}

void parse(vector2d& map){
    string line;
    fstream file("input.txt");
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
        for(int y = yl;y<=yr;y++){
            for(int x = xl;x<=xr;x++){
                map[y][x] = '#';
            }
        }
    }
    file.close();

}

bool isStable(vector2d& map, int x, int y){
    if(y == map.size()){
        return false;
    }
    if(map[y][x] == '|' && (map[y+1][x]=='~' || map[y+1][x]=='#') && (map[y][x+1]=='~' || map[y][x+1]=='#') &&(map[y][x-1]=='~' || map[y][x-1]=='#')){

    }
    if(map[y][x] == '~'){
        return true;
    }
    if(map[y][x] !='|'){
        return false;
    }
    bool ret = false;
    for(int px = x;map[y+1][px]=='~'||map[y+1][px]=='#';px++){
        if(map[y][px] == '~' || map[y][px] == '#'){
            ret = true;
            break;
        }
        if(map[y][px] == '.'){
            return false;
        }
    }
    if(!ret){
        return false;
    }
    for(int px = x;map[y+1][px]=='~'||map[y+1][px]=='#';px--){
        if(map[y][px] == '~' || map[y][px] == '#'){
            return true;
        }
        if(map[y][px] == '.'){
            return false;
        }
    }
    return false;

}

int score(vector2d& map){
    int val = 0;
    for(int y = 0;y<map.size();y++){
        for(int x = 0;x<map[0].size();x++){
            if(map[y][x] == '|' || map[y][x] == '~'){
                val++;
            }
        }
    }
    return val;
}

void iter(vector2d& map){
    for(int y = map.size()-2;y>=0;y--){
        for(int x = 0;x<map[0].size();x++){
            if(map[y][x] == '#' || map[y][x] == '.'){
                continue;
            }
            try{
                
                if((map[y][x] == '|' || map[y][x] == '+') && map[y+1][x] == '.'){
                    map[y+1][x] = '|';
                }
                if(map[y][x] == '|' && map[y+1][x]!='.' && map[y+1][x]!='|'){
                    if(map[y][x-1] == '.'){
                        map[y][x-1] = '|';
                    }
                    if(map[y][x+1] == '.'){
                        map[y][x+1] = '|';
                    }
                }
                if(isStable(map,x,y)){
                    map[y][x] = '~';
                }
            }catch(...){
                //Index out of bounds err
            }
        }
    }
}


void part1(){
    int l = inputBounds();
    int w(2000);

    vector2d map(l, vector<char>(w+500,'.'));
    map[0][500]= '+';
    parse(map);
    int last = -1;
    int val;
    for(int i = 0;;i++){
        //print(map);
        cout<<"On iteration "<<i<<endl;
        iter(map);
        val = score(map);
        if(val==last){
            break;
        }
        last = val;
    }
    cout<<"Final score is "<<val<<endl;
}

void update(vector2d& map, pair<int, int> coord){
    
}

void part1queue(){
    queue<pair<int, int>> q;
    int l = inputBounds();
    int w(2000);
    vector2d map(l, vector<char>(w+500,'.'));
    map[0][500]= '+';
    parse(map);
    map[1][500]='|';

}


