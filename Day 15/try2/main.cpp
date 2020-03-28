#include <iostream>
#include <fstream>
#include "grid.h"
using namespace std;

void p1();
int main(){
    p1();
}

void p1(){
    Grid grid("input.txt");
    grid.print();
    grid.updateDist(2,1);
    Coord c = grid.getClosest(3,4);
    grid.printDist();
    cout<<c.x<<", "<<c.y<<endl;
}