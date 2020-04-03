#include"fifteenPuzzle.h"
#include<iostream>

using namespace std;

void printState(uint8_t state[16]){
    cout << '\n';
    for(int i=0; i<16; i++){
        cout << +state[i] << '\t';
        if(i%4 == 3){
            cout << '\n';
        }
    }
    cout << '\n';
}

void randomState(uint8_t state[16], Problem* problem){
    do{
        random_shuffle(state, &state[16]);
    }while(!problem->checkSolvable(state));
}

int main(){
    //uint8_t state1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    uint8_t state1[16] = { 
        1, 2, 3, 0,
        5, 6, 7, 4,
        9, 10, 11, 8,
        13, 14, 15, 12
    };

    Problem *problem = new Problem(state1);
    Database *database = new Database(problem);
    //database->breadthFirstSearch();
    //database->saveDB("database.txt");
    database->loadDB("database.txt");






    delete problem;
    delete database;
}