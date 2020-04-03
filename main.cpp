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
    uint8_t state1[16] = { 1, 2, 3, 4, 5, 6, 7, 0, 9, 10, 11, 8, 13, 14, 15, 12};
    uint8_t state2[16] = { 0, 1, 2, 3, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12};
    Problem *problem = new Problem(state1);
    Database *database = new Database(problem);
    database->breadthFirstSearch();

    cout << "VALUE: " << database->checkRow(state1, 0) << '\n';
    cout << "VALUE: " << database->checkRow(state1, 1) << '\n';
    cout << "VALUE: " << database->checkRow(state1, 2) << '\n';
    cout << '\n';
    cout << "VALUE: " << database->checkRow(state2, 0) << '\n';
    cout << "VALUE: " << database->checkRow(state2, 1) << '\n';
    cout << "VALUE: " << database->checkRow(state2, 2) << '\n';



    delete problem;
    delete database;
}