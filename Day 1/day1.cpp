#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../UtilFunctions/fileRead.h"
using namespace std;

int main(){
    ifstream file("day1.txt");
    FileReader fRead;
    vector<string> data;
    data = fRead.read(file);
    int freq = 0;
    int change;
    for(unsigned int i = 0;i<data.size();i++){
        change = atoi(data[i].c_str());
        freq += change;
        cout<<i<<": "<<" -> "<<freq<<endl;
    }
}