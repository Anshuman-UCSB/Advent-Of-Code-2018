#include <iostream>
#include <vector>

using namespace std;

int sum(const vector<vector<int> >& sumTable, int x, int y, int size){
    return (sumTable[y+size][x+size] + sumTable[y][x] - sumTable[y+size][x] - sumTable[y][x+size]);
}

int main(){
    const int input = 42;
    vector<vector<int> > grid(300, vector<int>(300,0));
    for(int x = 0; x<300;x++){
        for(int y = 0;y<300;y++){
            grid[y][x] = ((((((x+10)*y)+input)*(x+10)/100)%10)-5);
        }
    }
    vector<vector<int> > sumTable(301, vector<int>(301,0));
    sumTable[1][1] = grid[0][0];
    for(int i = 2;i<301;i++){
        
        sumTable[0][i] = sumTable[0][i-1]+grid[0][i-1];
        sumTable[i][0] = sumTable[i-1][0]+grid[i-1][0];        
    }

    for(int x = 2;x<301;x++){
        for(int y = 2;y<301;y++){
            sumTable[y][x] = sumTable[y-1][x] + sumTable[y][x-1] + grid[y-1][x-1] - sumTable[y-1][x-1]; 
        }
    }

    int max = -1;
    int aX, aY, aSize;
    for(int size = 1;size<=300;size++){
        for(int x = 0;x<300-size;x++){
            for(int y = 0;y<300-size;y++){
                if(sum(sumTable, x, y, size)>=max){
                    max = sum(sumTable, x, y, size);
                    aX = x;
                    aY = y;
                    aSize = size;
                    // cout<<"New max "<<x<<","<<y<<","<<size<<endl;
                    // cout<<"  >sum: "<<sum(sumTable, x, y, size)<<endl;
                    cout<<"New max "<<aX<<","<<aY<<","<<aSize<<" with area "<<sum(sumTable, x, y, size)<<endl;
                }
            }
        }

    }

    
    cout<<"New max "<<aX<<","<<aY<<","<<aSize<<endl;
}