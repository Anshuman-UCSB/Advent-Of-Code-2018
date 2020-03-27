#include <iostream>
#include <vector>

using namespace std;

bool includes(vector<int>& vect, int val){
    int l(0), r(vect.size()-1), m;
    while(true){
        m = (l+r)/2;
        if(l>r){return false;}
        if(vect[m] == val){return true;}
        if(vect[m]>val){r = m-1;}
        else{l = m+1;}
    }
}

void print(const vector<int>& vect){
    cout<<"[ ";
    for(int i = 0;i<vect.size();i++){
        cout<<vect[i]<<" ";
    }cout<<"]"<<endl;
}

void insert(vector<int>& vect, int val){
    if(vect.empty()){
        vect.push_back(val);
        return;
    }
    int l(0), r(vect.size()-1),m;
    if(val<vect[l]){
        vect.insert(vect.begin(), val);
        return;
    }
    if(val>=vect[r]){
        vect.push_back(val);
        return;
    }
    for(int i = 0;i<=r-1;i++){
        if(vect[i]<=val && val<=vect[i+1]){
            vect.insert(vect.begin()+1+i,val);
            return;
        }
    }
}

struct Rule{
    vector<int> pre;
    Rule(){
        pre.empty();
    }
    Rule(string line){
        for(int i = 0;i<5;i++){
            if(line[i] ==  '#'){
                pre.push_back(i-2);
            }
        }
    }
};

vector<int> iter(vector<int>& vect, vector<Rule>& rules){
    vector<int> gen;
    gen.clear();
    int l = vect[0]-2;
    int r = vect.back()+2;
    Rule rule;
    for(int i = l; i<=r;i++){
        for(int j = 0;j<rules.size();j++){
            rule = rules[j];
            bool plant = true;
            for(int k = -2;k<3;k++){
                if(includes(rules[k].pre,k)){
                    if(!includes(vect,i+k)){
                        plant = false;
                    }
                } else{
                    if(includes(vect,i+k)){
                        plant = false;
                    }
                }
            }
            if (plant){
                insert(gen,i);
                break;
            }
        }
    }
    return gen;
}


int main(){
    vector<int> vect;
    string start = "##..##..#.##.###....###.###.#.#.######.#.#.#.#.##.###.####..#.###...#######.####.##...#######.##..#";
    for(int i = 0;i<start.size();i++){
        if(start[i] == '#'){
            vect.push_back(i);
        }
    }
    vector<string> raw = {"#####","###.#","##.#.","#.#.#","#.#..","#..#.","#...#",".####",".###.",".##..",".#.##",".#..#",".#...", "..#.#","...##"};
    vector<Rule> rules;
    for(int i = 0;i<raw.size();i++){
        rules.push_back(Rule(raw[i]));
    }

    for(int i = 0;i<18;i++){
        print(vect);
        vect = (iter(vect,rules));
    }
    print(vect);
    int sum = 0;
    for(int val: vect){
        sum+=val;
    }
    cout<<sum<<endl;

}