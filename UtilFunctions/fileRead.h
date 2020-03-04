#ifndef FILEREAD_H
#define FILEREAD_H

#include <string>
#include <fstream>
#include <vector>
using namespace std;

class FileReader{
    public:
    FileReader(string filename);
    vector<string> read();
    ~FileReader();

    fstream file;
    
};


#endif