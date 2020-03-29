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
    cout<<"  Starting gen: "<<endl;
    grid.print();
    cout<<grid.play()<<endl;
}
//239292 was too high
//234444 too high
//229798 not this