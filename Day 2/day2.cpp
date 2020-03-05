#include<iostream>
#include<fstream>
#include<string>

using namespace std;

template <class T>
struct Node{
    T data;
    Node<T>* next;
    Node(T data){
        this->data = data;
    }
};

bool hasOneDiff(string a, string b){
    //assume a&b same size
    bool oneDiff = false;
    for(int i = 0;i<a.size();i++){
        if(a[i] != b[i]){
            if(!oneDiff){
                oneDiff = true;
            } else{
                return false;
            }
        }
    }
    return oneDiff;
}

int main(){
    fstream file("day2.txt");
    string line;
    Node<string> *head (0), *tail;
    while(getline(file,line)){
        if(head == 0){
            head = new Node<string>(line);
            tail = head;
        }  else{
            tail->next = new Node<string>(line);
            tail = tail->next;
        }
    }
    file.close();

    for(Node<string>* h = head;h;h=h->next){
        for(Node<string>*p = head;p;p=p->next){
            if(hasOneDiff(h->data,p->data)){
                cout<<h->data<<endl;
                cout<<p->data<<endl;
                return 0;
            }
        }
    }

    return 0;
    //PART 1 BELOW
    int doubles(0), triples(0);

    string data;
    int alph[26];
    for(Node<string>* p = head;p;p=p->next){
        data = p->data;
        for(int i =0;i<26;i++){
            alph[i] = 0;
        }
        for (char const &c: data){
            alph[c-'a']++;
        }
        cout<<data<<endl;
        bool hasDoubl = false;
        bool hasTripl = false;
        for(int i = 0;i<26;i++){
            cout<<alph[i]<<" ";
            if (alph[i] == 2){
                hasDoubl=true;
            }
            if(alph[i] == 3){
                hasTripl = true;
            }
        }cout<<endl;
        doubles+=hasDoubl;
        triples+=hasTripl;

    }
    cout<<"Doubles: "<<doubles<<endl<<"Triples: "<<triples<<endl;
}