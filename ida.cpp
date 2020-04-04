#include "fifteenPuzzle.h"
#include <iostream>
using namespace std;

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

            if(db->problem->getHash(current->state) == db->problem->getHash(db->problem->goalState)){
                cout << "CONGRATS FOUND A SOLUTION!\n";
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