#include <iostream>
#include <vector>
#include <string>

using namespace std;

void part1();
int main(){
    part1();
}

void print(vector<int> v){
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