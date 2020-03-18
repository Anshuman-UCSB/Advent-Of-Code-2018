#include <iostream>
#include <vector>

using namespace std;

int sum(const vector<vector<int> >& sumTable, int x, int y, int size){
    return (sumTable[y+size][x+size] + sumTable[y][x] - sumTable[y+size][x] - sumTable[y][x+size]);
}

int main(){
    const int input = 18;
    vector<vector<int> > grid(300, vector<int>(300,0));
    for(int x = 0; x<300;x++){
        for(int y = 0;y<300;y++){
            grid[y][x] = ((((((x+10)*y)+input)*(x+10)/100)%10)-5);
        }
    }

    vector<vector<int> > sumTable(300, vector<int>(300,0));
    sumTable[0][0] = grid[0][0];
    for(int i = 1;i<300;i++){
        sumTable[0][i] = sumTable[0][i-1]+grid[0][i];
        sumTable[i][0] = sumTable[i-1][0]+grid[i][0];        
    }
    for(int x = 1;x<300;x++){
        for(int y = 1;y<300;y++){
            sumTable[y][x] = sumTable[y-1][x] + sumTable[y][x-1] + grid[y][x] - sumTable[y-1][x-1]; 
        }
    }

    int max = -1;
    int aX, aY, aSize;
    for(int size = 1;size<=300;size++){
        for(int x = 0;x<300-size;x++){
            for(int y = 0;y<300-size;y++){
                if(sum(sumTable, x, y, size)>max){
                    max = sum(sumTable, x, y, size);
                    aX = x;
                    aY = y;
                    aSize = size;
                    cout<<"New max "<<x<<","<<y<<","<<size<<endl;
                    cout<<"  >sum: "<<sum(sumTable, x, y, size)<<endl;
                }
            }
        }
    }

    
    cout<<"New max "<<aX<<","<<aY<<","<<aSize<<endl;
}