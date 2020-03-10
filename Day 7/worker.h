#define BASETIME 60
#include <vector>

using namespace std;
int getTime(char let){
    return BASETIME + let - 'A' + 1;
}



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

void updateTime(int &time, vector<Worker> vect, vector<char> done){
    time++;
    for(Worker wrk: vect){
        if(wrk.working)
            wrk.remainingTime--;
    }
}

void getFinished(vector<Worker>& workers, vector<char>& done){
    for(Worker wrk: workers){
        if(wrk.working==true && wrk.remainingTime==0){
            wrk.working=false;
            done.push_back(wrk.letter);
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

void updateAble(vector<char>& done, vector<char>& inProgress, vector<char>& able, const vector<char>& elems){
    able.clear();
    for(char elem: elems){
        able.push_back(elem);
        if(find(done, elem) != -1 && find(inProgress, elem) != -1){
            //if done or in progress
            able.pop_back();
        }
        
    }
}