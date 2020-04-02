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
    uint8_t initState[16] = { 1, 2, 3, 4, 5, 6, 7, 0, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8_t initStat2[16] = { 1, 2, 3, 4, 5, 6, 7, 0, 8, 9, 10, 11, 12, 13, 14, 15};
    Problem *problem = new Problem(initState);
    // cout << problem->findBlankSquare(initState) << '\n';
    // auto up = problem->actions(initState);
    // cout << up[0] << ' ' << up[1] << ' ' << up[2] << ' ' << up[3] << '\n';
    // printState(initState);
    // printState(problem->result(initState, 0).get());
    // cout << problem->goalTest(initState) << ' ' << problem->goalTest(problem->goalState) << '\n';

    printState(initState);
    auto node = new Node(initState);
    auto node2 = new Node(initStat2);
    
    cout << "Hash: " << node->getHash(problem) << '\n';
    cout << "Hash2: " << node2->getHash(problem) << '\n';
    // auto children = node->expand(problem);
    // for(int i=0; i<4; i++){
    //     if(children[i]){
    //         cout << "\nMatrix: " << children[i]->action << '\n';
    //         printState(children[i]->state);
    //         auto solution = children[i]->solution();

    //         cout << "Solution: ";
    //         for(int i=0; i<solution.get()->size(); i++){
    //             cout << (*solution.get())[i] << ' ';
    //         }
    //         cout << '\n';
    //     }
    // }
}