#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Particle{
    int x, y;
    int xVel;
    int yVel;

    Particle(string inp){

        //position=< 9,  1> velocity=< 0,  2>
        string temp = inp;
        temp = temp.substr(temp.find("=<")+2);
        x = stoi(temp.substr(0,temp.find(",")));
        temp = temp.substr(temp.find(",")+1);
        y = stoi(temp.substr(0,temp.find(">")));
        temp = temp.substr(temp.find("=<")+2);
        xVel = stoi(temp.substr(0,temp.find(",")));

        temp = temp.substr(temp.find(",")+1);
        yVel = stoi(temp.substr(0,temp.find(">")));
    }

};

vector<Particle> parse(){
    string line;
    vector<Particle> parts;
    fstream file("day10.txt");
    while(getline(file, line)){
        parts.push_back(Particle(line));
    }
    return parts;
}

//Time is 10124
int main(){
    vector<Particle> coords = parse();
    string line;
    int minArea = 9999999;
    int mins[4];
    int t = -1;
    int minX, minY, maxX, maxY;
    for(int i = 0;i<20000;i++){
        minX = 1000000;
        maxX = 0;
        minY = 1000000;
        maxY = 0;
        for(int j = 0;j<coords.size();j++){
            int x = (coords[j].x + coords[j].xVel*i);
            int y = (coords[j].y + coords[j].yVel*i);
            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y); 
        }
        if(maxX-minX < minArea){
            minArea = maxX - minX;
            mins[0] = minX;
            mins[1] = maxX;
            mins[2] = minY;
            mins[3] = maxY;
            t = i;
        }
    }
    cout<<"Min time found at "<<t<<endl;
    cout<<"minX: "<<mins[0]<<endl;
    cout<<"maxX: "<<mins[1]<<endl;
    cout<<"minY: "<<mins[2]<<endl;
    cout<<"maxY: "<<mins[3]<<endl;

    char grid[100][100];
    for(int i = 0;i<100;i++){
        for(int j = 0;j<100;j++){
            grid[i][j] = ' ';
        }
    }
    for(int i = 0;i<coords.size();i++){
        grid[coords[i].y+coords[i].yVel*t-mins[2]][coords[i].x+coords[i].xVel*t-mins[0]] = '#';
    }

    cout<<"#############"<<endl;
    for(int i = 0;i<100;i++){
        for(int j = 0;j<100;j++){
            cout<<grid[i][j];
        }cout<<endl;
    }
    cout<<"#############"<<endl;

}

/*
#define SIZE 200
#define SCALE 600


int main(){
    int size = SIZE;
    int cen = size/2;
    char grid[SIZE][SIZE];
    vector<Particle> coords = parse();
    cout<<coords[0].x<<endl;;

    for(int i = 0;i<size;i++){
        for(int j= 0;j<size;j++){
            grid[i][j] = ' ';
        }
    }
    string line;
    Particle p = coords[0];
    for(int time = 0;;time++){
        for(int i = 0;i<coords.size();i+=10){
            p = coords[i];
            grid[((p.y+p.yVel*time)/SCALE)+cen][((p.x+p.xVel*time)/SCALE)+cen] = '#';
            //cout<<grid[(p.y/SCALE)+cen][(p.x/SCALE)+cen]<<endl;
            //cout<<"placed at "<<(p.x/SCALE)+cen<<","<<(p.y/SCALE)+cen<<endl;
        }

        for(int i = 0;i<size;i++){
            cout<<"|";
            for(int j= 0;j<size;j++){
                cout<<grid[i][j];
            }cout<<"|"<<endl;
        }
    }

}

*/