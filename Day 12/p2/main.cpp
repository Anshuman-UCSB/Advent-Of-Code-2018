#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> parse(){
    string line;
    fstream file("inp.txt");
    vector<string> out;
    getline(file,line);
    out.push_back(line.substr(15));
    getline(file,line);
    while(getline(file,line)){
        if(line[9] == '#'){
            out.push_back(line.substr(0,5));
        }
    }
    return out;
}

void print(vector<string> vect){
    for(int i = 0;i<vect.size();i++){
        cout<<vect[i]<<endl;
    }
}

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

vector<int> iter(vector<int> vect, vector<string> rules){
    bool plant;
    string rule;
    vector<int> gen;
    for(int i = vect.front()-4;i<=vect.back()+4;i++){
        for(int j = 0;j<rules.size();j++){
            rule = rules[j];
            plant = true;
            for(int l = -2;l<=2;l++){
                if(rule[l+2] == '#'){
                    if(!includes(vect,i+l)){
                        plant = false;
                        break;
                    }
                } else{
                    if(includes(vect,i+l)){
                        plant = false;
                        break;
                    }
                }
            }
            if(plant){
                gen.push_back(i);
                break;
            }
        }
    }
    return gen;
}

int main(){
    vector<string> rule = parse();
    string start = rule[0];
    vector<int> gen;
    rule.erase(rule.begin());
    cout<<"Begin: "<<start<<endl;
    for(int i = 0;i<start.size();i++){
        if(start[i] == '#'){
            gen.push_back(i);
        }
    }
    for(long j = 0;j<=50000000000;j++){
        int sum = 0;
        for(int i = 0;i<gen.size();i++){
            sum+=gen[i];
            //cout<<gen[i]<<" ";
        }
        if(j%10000==0){
            cout<<"Gen "<<j<<": ";
            cout<<"     sum: "<<sum<<endl;
        }
        vector<int> next = iter(gen,rule);
        gen.clear();
        gen = next;
    }
}

/*
Gen 620000:      sum: 4959957			Gen	Sum	Difference		Difference * gen	Delta		
Gen 630000:      sum: 5039957			620000	4959957			4960000	43		8*gen - 43
Gen 640000:      sum: 5119957			630000	5039957	80000		5040000	43		5039957
Gen 650000:      sum: 5199957			640000	5119957	80000		5120000	43		
Gen 660000:      sum: 5279957			650000	5199957	80000		52000000000	51994800043		
Gen 670000:      sum: 5359957			660000	5279957	80000		52800000000	52794720043		
Gen 680000:      sum: 5439957			670000	5359957	80000		53600000000	53594640043		
			680000	5439957	80000		54400000000	54394560043		

How I ended up solving it by hand
*/
