#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;


string react(string data){
    int size = data.length();
    char chars[size];
    const char* cstring = data.c_str();

    for(int i = 0;i<data.length();i++){
        chars[i] = cstring[i];
    }

    bool unchanged = false;
    char last;
    int lastind;
    while(!unchanged){
        last = ' ';
        lastind = -1;
        unchanged = true;
        for(int i = 0;i<size;i++){
            if(chars[i] != ' '){
                if(abs(chars[i] - last) == 32){ //if 'A' - 'a' == const,
                    chars[i] = ' ';             //delete i
                    chars[lastind] = ' ';       //delete last i
                    last = ' ';
                    unchanged = false;
                }
                last = chars[i];
                lastind = i;
            }
        }
    }


    string final = "";

    for(int i = 0;i<size;i++){
        if(chars[i] != ' '){
            final+=chars[i];
        }
    }
    return final;
}

string reactCleaned(string data, char clean){
    for(int i = 0;i<data.length();i++){
        if(tolower(data[i])==clean){
            data.erase(i,1);
            i--;
        }
    }

    return react(data);
}

int main(){
    fstream file("day5.txt");
    string data;
    getline(file,data);
    file.close();
    int min = data.length();
    cout<<"Starting polymer: "<<data<<endl;
    for(char remove = 'a';remove<='z';remove++){
        int size = reactCleaned(data,remove).length();
        cout<<"Polymer with '"<<remove<<"' removed has size "<<size<<endl;
        min = min<size ? min: size;
    }
    cout<<"The smallest polymer had length "<<min<<endl;
}