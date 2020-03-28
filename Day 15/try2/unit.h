#ifndef UNIT_H
#define UNIT_H

#include <string>

struct Coord{
    int x, y;
    Coord():x(-1),y(-1){}
    Coord(int i, int j): x(i),y(j){}
};

class Unit{
    public:
    int uniqueId;
    char id;
    int hp, dmg;
    Unit(){
        uniqueId = -1;
        id = ' ';
        hp = dmg = -1;
    }
    Unit(char quick, int id){
        uniqueId = id;
        switch(quick){
            case 'E':
                id = 'E';
                hp = 200;
                dmg = 3;
                break;
            case 'G':
                id = 'G';
                hp = 200;
                dmg = 3;
                break;
            case '#':
                id = '#';
                hp = dmg = -1;
                break;
            case '.':
                id = '.';
                hp = dmg = -1;
                break;
        }
    }
};


#endif