#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
#define RULESIZE 5

//##... => .
struct Rule{
    char pre[RULESIZE];
    char post;
    string raw;
    Rule(string line){
        raw = line;
        for(int i = 0;i<5;i++){
            pre[i] = line[i];
        }
        post = line[9];
    }
};

ostream& operator<<(std::ostream& stream, const Rule& yourclass){
    stream<<yourclass.raw;
    return stream;
}

void pad(vector<char>& pots){
    /*while(pots.back()=='.'){
        pots.pop_back();
    }
    while(pots[0] == '.'){
        pots.erase(pots.begin());
    }
    for(int i= 0;i<3;i++){
        pots.insert(pots.begin(),'.');
        pots.push_back('.');
    }*/
}

char match(vector<char>& pots, int ind, vector<Rule>& rules){
    bool found;
    for(int i= 0;i<rules.size();i++){
        found = true;
        for(int j = 0;j<RULESIZE;j++){
            if(pots[j+ind-2] != rules[i].pre[j]){
                found = false;
                break;
            }
        }
        if(found){
            return rules[i].post;
        }
    }
    return '.';
}

vector<char> iter(vector<char>& pots, vector<Rule>& rules){
    pad(pots);
    vector<char> next;
    for(int i = 0;i<pots.size();i++){
        next.push_back(match(pots,i, rules));
    }
    return next;
}

void print(vector<char>& pots, int gen, vector<Rule> rules){
    vector<char> current = pots;
    cout<<0<<": ";
    for(int i = 0;i<current.size();i++){
        cout<<current[i];
    }cout<<endl;
    for(int g = 1;g<=gen;g++){
        current = iter(current, rules);
        cout<<g<<": ";
        for(int i = 0;i<current.size();i++){
            cout<<current[i];
        }cout<<endl;
    }
    int sum = 0;
    int centerInd = 47;
    for(int i = 0;i<current.size();i++){
        if(current[i] == '#'){
            sum+=i-centerInd;
        }
    }
    cout<<"At last gen, sum of indexes is "<<sum<<endl;
}

void part1(){
    string input = "...............................................##..##..#.##.###....###.###.#.#.######.#.#.#.#.##.###.####..#.###...#######.####.##...#######.##..#...............";
    
    // input = "#..#.#..##......###...###";
    vector<char> pots;
    for(int i= 0;i<input.size();i++){
        pots.push_back(input[i]);
    }
    string line;
    fstream file("rules.txt");
    vector<Rule> rules;
    while(getline(file,line)){
        rules.push_back(Rule(line));
    }
    file.close();
    print(pots,20, rules);

}

int main(){
    part1();
}