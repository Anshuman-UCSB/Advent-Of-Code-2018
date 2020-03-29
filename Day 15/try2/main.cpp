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
    for(int i = 1;i<50;i++){
        cout<<"\n----Gen "<<i<<": "<<endl;
        grid.iter();
        grid.print();
        grid.printUnits();
        // grid.printDist();
    }
}