#include"fifteenPuzzle.h"
#include<iostream>

using namespace std;

void printState(uint8_t state[16]){
    for(int i=0; i<16; i++){
        cout << +state[i] << ' ';
        if(i%4 == 3){
            cout << '\n';
        }
    }
    cout << '\n';
}

int main(){
    uint8_t state1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    Problem *problem = new Problem(state1);
    Database *database = new Database(problem);
    database->breadthFirstSearch();



    while()

    delete problem;
    delete database;
}