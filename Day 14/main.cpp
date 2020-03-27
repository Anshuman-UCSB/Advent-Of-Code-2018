#include <iostream>
#include <vector>
#include <string>

using namespace std;

void part1();
void part2();
int main(){
    part2();
}

void print(vector<int>& v){
    cout<<"[ ";
    for(int i = 0;i<v.size();i++){
        cout<<v[i]<<" ";
    }cout<<"]\n";
}
void part1(){
    int INPUT = 681901;
    int ANSSIZE = 10;
    vector<int> recip = {3,7};
    int e1(0), e2(1);
    while(recip.size()<=INPUT+ANSSIZE){
        //print(recip);
        string newRecip = to_string(recip[e1]+recip[e2]);
        for(int i = 0;i<newRecip.size();i++){
            recip.push_back(newRecip[i]-'0');
        }
        e1+=recip[e1]+1;
        e1%=recip.size();
        e2+=recip[e2]+1;
        e2%=recip.size();
    }
    cout<<"Answer: ";
    for(int i = INPUT;i<INPUT+ANSSIZE;i++){
        cout<<recip[i];
    }cout<<endl;
}

void part2(){
    string INPUT = "68190";
    int ANSSIZE = INPUT.size();
    vector<int> recip = {3,7};
    int e1(0), e2(1);
    int ans = 1;
    while(true){
        //print(recip);
        string newRecip = to_string(recip[e1]+recip[e2]);
        for(int i = 0;i<newRecip.size();i++){
            recip.push_back(newRecip[i]-'0');
        }
        e1+=recip[e1]+1;
        e1%=recip.size();
        e2+=recip[e2]+1;
        e2%=recip.size();
        ans++;
        bool found = true;
        for(int i = 0;i<ANSSIZE;i++){
            if(recip[recip.size()-1-i] != INPUT[ANSSIZE-1-i]-'0'){
                found = false;
                break;
            }
        }
        if(!found)
            continue;
        cout<<"Found recipie at "<<recip.size()-ANSSIZE<<endl;
        return;
    }
}