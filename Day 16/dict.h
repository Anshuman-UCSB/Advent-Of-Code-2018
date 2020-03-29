#ifndef DICT
#define DICT

#include <string>
#include <vector>
using namespace std;


string dict[16] = {
    "addr",
    "addi",
    "mulr",
    "muli",
    "banr",
    "bani",
    "borr",
    "bori",
    "setr",
    "seti",
    "gtir",
    "gtri",
    "gtrr",
    "eqir",
    "eqri",
    "eqrr"
};


vector<int> addr(int reg[4]){
    reg[reg[3]] = reg[reg[1]] + reg[reg[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> addi(int reg[4]){
    reg[reg[3]] = reg[reg[1]] + reg[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> eval(int reg[4], int opId){
    string opInstr = dict[opId];
    switch(opId){
        case 0:
            return addr(reg);
        case 1:
            return addi(reg);
    }
}




#endif