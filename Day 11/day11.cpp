#include <iostream>
#include <string>
using namespace std;

#define INPUT 18
//6042

int getPower(int x, int y){
    int rackId = x+10;
    int power = rackId * y;
    power += INPUT;
    power *= rackId;
    power /= 100;
    power %= 10;
    power -= 5;
    return power;
}

int main(){
    int grid[300][300];
    for(int i = 0;i<300;i++){
        for(int j = 0;j<300;j++){
            grid[i][j] = getPower(j,i);
        }
    }
    //part 2
    string ans;
    int max = -1;
    int sum;
    for(int size = 1;size<=300;size++){
        cout<<"Working on size: "<<size<<endl;
        for(int y = 0;y<300-size;y++){
            for(int x = 0;x<300-size;x++){
                sum = 0;
                for(int xMod = 0;xMod<size;xMod++){
                    for(int yMod = 0;yMod<size;yMod++){
                        sum+=grid[y+yMod][x+xMod];
                    }
                }
                if(sum>max){
                    max = sum;
                    ans = to_string(x)+','+to_string(y)+','+to_string(size);
                    cout<<"New answer: "<<ans<<endl;
                }
            }
        }
    }
    cout<<"answer "<<ans<<" has the largest power of "<<max<<endl;


    /*part 1
    return 0;
    string ans;
    int max = -1;
    int sum;
    for(int y = 0;y<300-3;y++){
        for(int x = 0;x<300-3;x++){
            sum = 0;
            for(int xMod = 0;xMod<3;xMod++){
                for(int yMod = 0;yMod<3;yMod++){
                    sum+=grid[y+yMod][x+xMod];
                }
            }
            if(sum>max){
                max = sum;
                ans = to_string(x)+','+to_string(y);
            }
        }
    }
    cout<<"coord "<<ans<<" has the largest power of "<<max<<endl;
    */
}