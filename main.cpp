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


void IDA(Database * db, int limit=50){
    auto comp = [&](Node* a, Node* b){
        return a->depth + db->problem->h(a, db) < b->depth + db->problem->h(b, db);
    };
    bool done = false;

    for(int i=1; i<limit; i++){
        priority_queue<
            Node*,
            vector<Node*>,
            decltype(comp)
        > frontier(comp);
        vector<Node*> reserve;

        frontier.push(new Node(db->problem->initState));

        while(!frontier.empty()){
            auto current = frontier.top();
            reserve.push_back(current);
            frontier.pop();

            if(current->depth > i){
                continue;
            }

            printf("f(n):%d\n", current->depth + db->problem->h(current, db));

            if(db->problem->getHash(current->state) == db->problem->getHash(db->problem->goalState)){
                
                cout << "CONGRATS FOUND A SOLUTION!\n";
                printState(current->state);
                auto sol = current->solution();
                for(int i=0; i<sol->size(); i++){
                    cout << (*sol)[i] << ' ';
                }
                cout << '\n';
                done = true;
                break;
            }

            auto children = current->expand(db->problem);
            for(int i=0; i<4; i++){
                if(children[i]){
                    frontier.push(children[i]);
                }
            }
        }

        for(int j=0; j<reserve.size(); j++){
            delete reserve[j];
        }

        if(done) break;
    }

    if(!done){
        cout << "no solution found w/ limit 50\n";
    }
}


int main(){
    uint8_t state1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

    Problem *problem = new Problem(state1);
    cout << "loading db ...";
    Database *database = new Database(problem);

    database->breadthFirstSearch();
    database->saveDB("database.txt");
    
    // database->loadDB("database.txt");


    // cout << "done!\n Starting IDA\n";

    // for(int i=0; i< 20; i++){
    //     randomState(problem->initState, problem);
    //     std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
    //     IDA(database);
    //     std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    //     cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "us.\n";
    // }

    

    









    delete problem;
    delete database;
}