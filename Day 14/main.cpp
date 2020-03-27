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

int check(vector<int>& v, string find);
void part2(){
    string INPUT = "681901";
    int ANSSIZE = INPUT.size();
    vector<int> recip = {3,7};
    int e1(0), e2(1);
    int checkVal = 32;
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
        if(recip.size()>checkVal){
            int val = check(recip,INPUT);
            if(val==-1){
                cout<<"Didn't find answer in size "<<checkVal<<endl;
            }else{
                cout<<"Answer is "<<val<<endl;
                return;
            }
            checkVal*=2;
        }
    }
}

int check(vector<int>& v, string find){
    for(int i = 0;i<v.size()-find.size();i++){
        bool found = true;
        for(int c = 0;c<find.size();c++){
            if(v[c+i]!= find[c]-'0'){
                found = false;
                break;
            }
        }
        if(found){
            return i;
        }        
    }

    return -1;
}