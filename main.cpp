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
    uint8_t state1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

    Problem *problem = new Problem(state1);
    cout << "loading db ...";
    Database *database = new Database(problem);

    //database->breadthFirstSearch();
    //database->saveDB("database.txt");
    
    database->loadDB("database.txt");


     cout << "done!\n Starting IDA\n";

     for(int i=0; i< 1; i++){
         randomState(problem->initState, problem);
         std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
         IDA(database);
         std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

         cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "us.\n";
     }

    

    









    delete problem;
    delete database;
}