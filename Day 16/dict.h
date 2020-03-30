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


vector<int> addr(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] + reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> addi(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] + cmd[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> mulr(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] * reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> muli(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] * cmd[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> banr(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] & reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> bani(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] & cmd[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> borr(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] | reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> bori(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] | cmd[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> setr(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> seti(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = cmd[1];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> gtir(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = cmd[1] > reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> gtri(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] > cmd[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> gtrr(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] > reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> eqir(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = cmd[1] == reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> eqri(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] == cmd[2];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}

vector<int> eqrr(vector<int> reg, vector<int> cmd){
    reg[cmd[3]] = reg[cmd[1]] == reg[cmd[2]];
    return vector<int>{reg[0],reg[1],reg[2],reg[3]};
}


vector<int> eval(vector<int> reg, vector<int> cmd, int opCode){
    string opInstr = dict[cmd[0]];
    switch(opCode){
        case 0: return addr(reg, cmd);
        case 1: return addi(reg, cmd);
        case 2: return mulr(reg, cmd);
        case 3: return muli(reg, cmd);
        case 4: return banr(reg, cmd);
        case 5: return bani(reg, cmd);
        case 6: return borr(reg, cmd);
        case 7: return bori(reg, cmd);
        case 8: return setr(reg, cmd);
        case 9: return seti(reg, cmd);
        case 10:return gtir(reg, cmd);
        case 11:return gtri(reg, cmd);
        case 12:return gtrr(reg, cmd);
        case 13:return eqir(reg, cmd);
        case 14:return eqri(reg, cmd);
        case 15:return eqrr(reg, cmd);
    }
}

bool workingOpCode(vector<int> reg, vector<int> cmd, vector<int> exp, int opC){
    // cout<<"Evaluating for "<<dict[opC]<<endl;
    vector<int> out = eval(reg,cmd, opC);
    for(int i = 0;i<4;i++){
        if(out[i] != exp[i]){
            return false;
        }
    }
    // cout<<dict[opC]<<" is valid!"<<endl;
    return true;
}


#endif