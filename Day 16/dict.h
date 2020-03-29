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

vector<int> mulr(int reg[4]){
    reg[reg[3]] = reg[reg[1]] * reg[reg[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> muli(int reg[4]){
    reg[reg[3]] = reg[reg[1]] * reg[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> banr(int reg[4]){
    reg[reg[3]] = reg[reg[1]] & reg[reg[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> bani(int reg[4]){
    reg[reg[3]] = reg[reg[1]] & reg[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> borr(int reg[4]){
    reg[reg[3]] = reg[reg[1]] | reg[reg[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> bori(int reg[4]){
    reg[reg[3]] = reg[reg[1]] | reg[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> setr(int reg[4]){
    reg[reg[3]] = reg[reg[1]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> seti(int reg[4]){
    reg[reg[3]] = reg[1];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> eval(int reg[4], int opId){
    string opInstr = dict[opId];
    switch(opId){
        case 0: return addr(reg);
        case 1: return addi(reg);
        case 2: return mulr(reg);
        case 3: return muli(reg);
        case 4: return banr(reg);
        case 5: return bani(reg);
        case 6: return borr(reg);
        case 7: return bori(reg);
        case 8: return setr(reg);
        case 9: return seti(reg);
    }
}




#endif