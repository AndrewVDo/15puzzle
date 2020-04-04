#include"fifteenPuzzle.h"
#include<iostream>
#include<stdio.h>
#include<chrono>

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
    cout << "Please wait while the database is setup (17,297,280 rows)\n";
    uint8_t state1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    Problem *problem = new Problem(state1);
    Database *database = new Database(problem);
    database->breadthFirstSearch();
    //database->saveDB("database.txt"); //use this if you want to inspect the db

    cout << "Database Complete, Starting up IDA*\n";

    for(int i=0; i< 10; i++){
        randomState(problem->initState, problem);
        std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
        stack<unique_ptr<Node>> history;
        auto result = problem->iterative_deepening_search(1000000, database, history);
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

        cout<<"Starting State:";
        printState(problem->initState);
        if(result){
            auto solution = result->solution();
            cout << "Solution: ";
            for(int i=1; i<(*solution).size(); i++){
                string moves[4] = { "up", "right", "down", "left"};
                cout << moves[(*solution)[i]] << ", ";
            }
            cout << '\n';
        }
        else{
            cout << "could not find solution to that problem with the given limit on depth\n";
        }
        cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds.\n\n";
    }

    delete problem;
    delete database;
}