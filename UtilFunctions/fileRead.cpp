#include "fileRead.h"

FileReader::FileReader(string filename){
    file = fstream(filename);
}

vector<string> FileReader::read(){
    vector<string> data;
    string line;
    if(file.is_open()){
        while(getline(file,line)){
            data.push_back(line);
        }
    }
    return data;
}

FileReader::~FileReader(){
    file.close();
}