#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

template <class T>
class Grid{
    public:
    vector<vector<T>> grid;
    char defChar;
    int xCen;
    int yCen;

    Grid(char chr){
        defChar = chr;
        grid.clear();
        grid.push_back(vector<T>());
        grid[0].push_back(defChar);
        xCen = 0;
        yCen = 0;
    }

    void extend(int x, int y){
        for(int i = 0;i<abs(y);i++){
            grid.push_back(vector<T>());
            for(int x = 0;x<grid[0].size();x++){
                grid[grid.size()-1].push_back(defChar);
            }
        }
        for(int i = 0;i<abs(x);i++){
            for(int j = 0;j<grid.size();j++){
                grid[j].push_back(defChar);
            }
        }
    }

    void setCen(int x, int y){
        xCen = x;
        yCen = y;
    }

    void print(){
        
        for(int i = 0;i<grid[0].size();i++){
            cout<<"#";
        }
        cout<<endl;
        for(int i = 0;i<grid.size();i++){
            for(int j = 0;j<grid[0].size();j++){
                cout<<grid[i][j];
            }cout<<endl;
        }
        for(int i = 0;i<grid[0].size();i++){
            cout<<"#";
        }
        cout<<endl;
    }

    void file(){
        ofstream file("day10frame.txt");

        for(int i = 0;i<grid.size();i++){
            for(int j = 0;j<grid[0].size();j++){
                file<<grid[i][j];
            }file<<endl;
        }

    }

    void add(int x, int y, char val){
        grid[y+yCen][x+xCen] = val;
    }
};

