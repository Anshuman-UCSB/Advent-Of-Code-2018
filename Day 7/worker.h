#define BASETIME 60
#include <vector>

using namespace std;
int getTime(char let){
    return BASETIME + let - 'A' + 1;
}

struct Rule{
    char pre;
    char make;

    Rule(string inp){
        pre = inp[5];
        make = inp[36];
    }

    string to_str(){
        string out = "";
        out+=pre;
        out+=" -> ";
        out+= make;
        return out;
    }
};

struct Worker{
    int id;
    bool working;
    int remainingTime;
    char letter;

    Worker(int id){
        this->id = id;
        working = false;
        remainingTime = -1;
        letter = ' ';
    }

    void assign(char letter){
        remainingTime = getTime(letter);
        working = true;
        this->letter= letter;
    }
};

void updateTime(int &time, vector<Worker>& vect){
    time++;
    for(int i = 0;i<vect.size();i++){
        if(vect[i].working)
            vect[i].remainingTime--;
    }
}

void updateInProgress(vector<Worker>& workers, vector<char>& inprog){
    inprog.clear();
    for(int i =0 ;i<workers.size();i++){
        if(workers[i].working){
            inprog.push_back(workers[i].letter);
        }
    }
}

void giveJobs(vector<Worker>& workers, vector<char>& able){
    for(int i = 0;i<workers.size();i++){
        if(!workers[i].working){
            if(able.size()>0){
                //if worker is not working and something
                //available
                workers[i].assign(able[0]);
                able.erase(able.begin());
            }
        }        
    }
}

void getFinished(vector<Worker>& workers, vector<char>& done){
    for(int i = 0;i<workers.size();i++){
        if(workers[i].working==true && workers[i].remainingTime==0){
            done.push_back(workers[i].letter);
            workers[i].working=false;
            workers[i].letter=' ';
            workers[i].remainingTime=-1;
        }
    }
}

int find(vector<char> vect, char val){
    for(int i = 0;i<vect.size();i++){
        if(vect[i] == val){
            return i;
        }
    }
    return -1;
}

void updateAble(const vector<char>& done, vector<char>& inProgress, vector<char>& able, const vector<char>& elems, const vector<Rule> rules){
    able.clear();
    for(char elem: elems){
        able.push_back(elem);
        if(find(done, elem) != -1 || find(inProgress, elem) != -1){
            //if done or in progress
            able.pop_back();
            continue;
        }
        for(Rule rule: rules){
            if(rule.make == elem){
                if(find(done,rule.pre) == -1){
                    //if a prereq isnt made
                    able.pop_back();
                    break;
                }
            }
        }
        
    }
}