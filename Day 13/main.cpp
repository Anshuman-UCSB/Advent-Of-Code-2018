#include <iostream>
#include "grid.h"
using namespace std;

int main(){
    Grid g = Grid();
    //g.print();
    cout<<endl;
    string line;
    while(true){
        g.iter();
        //g.print();
    }
}