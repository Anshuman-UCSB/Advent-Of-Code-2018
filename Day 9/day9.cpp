#include <iostream>
#include "Node.h"

#define PLAYERS 465
#define MARBLE 7194000

using namespace std;

void printList(Node* head){
    cout<<head->number<<" ";
    for(Node* p = head->next;p!= head;p=p->next){
        cout<<p->number<<" ";
    }cout<<endl;
}

int highScore(int players[PLAYERS]){
    int max = -1;
    
    for(int i = 0;i<PLAYERS;i++){
        max = max<players[i] ? players[i] : max;
    }

    return max;
}

void partOne(){
    int players[PLAYERS];
    int currentPlayer = 0;
    for(int i = 0;i<PLAYERS;i++){
        players[i] = 0;
    }

    Node* head = new Node(0);
    head->last = head;
    head->next = head;
    Node* current = head;
    int size = 1;

    cout<<"Current is "<<current->number<<endl;
    cout<<"[-] ";
    print(head, size);

    for(int i = 1;i<=MARBLE;i++){

        if(i%23 == 0){
            for(int j = 0;j<6;j++)
                left(current);
            //cout<<"Removing current "<<current->number<<endl;
            players[currentPlayer]+= remove(current->last, size);
            players[currentPlayer]+=i;
        }
        else{
            right(current);
            insert(current, i, size);
            right(current);
        }
        //cout<<"Current is "<<current->number<<endl;
        //cout<<"High score: "<<highScore(players)<<endl;
        //cout<<"["<<currentPlayer+1<<"] ";
        //print(head, size);
        currentPlayer++;
        currentPlayer%=PLAYERS;
    }
    cout<<highScore(players)<<endl;
    
}

int main(){
    partOne();
}