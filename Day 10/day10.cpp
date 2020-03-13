#include <iostream>
#include <fstream>
#include <string>
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
        cout<<coord.y<<endl;
        temp = temp.substr(temp.find("=<")+2);
        xVel = stoi(temp.substr(0,temp.find(",")));

        temp = temp.substr(temp.find(",")+1);
        yVel = stoi(temp.substr(0,temp.find(">")));
    }

};

int main(){
    Particle p("position=< 9,-1> velocity=< 0,  2>");
}