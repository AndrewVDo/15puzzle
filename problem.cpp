#include "fifteenPuzzle.h"
#include <string.h>

std::pair<int, int> getLoc(int index){
    return std::pair<int, int>(index % 4, int(index / 4));
}

using namespace std;

Problem::Problem(uint8_t initState[16]){
    memcpy(this->initState, initState, 16 * sizeof(uint8_t));
}

int Problem::findBlankSquare(const uint8_t state[16]) const {
    if(!state){
        throw "state ptr null";
    }
    for(int i=15; i>=0; i--){
        if(!state[i]) return i;
    }
    throw "blank not found";
}

unique_ptr<bool[]> Problem::actions(const uint8_t state[16]) const {
    unique_ptr<bool[]> result(new bool(4));
    switch (this->findBlankSquare(state)){
        case 0:
            result[0] = false; 
            result[1] = true;
            result[2] = true;
            result[3] = false;
            break;
        case 1: case 2:
            result[0] = false; 
            result[1] = true;
            result[2] = true;
            result[3] = true;
            break;
        case 3:
            result[0] = false; 
            result[1] = false;
            result[2] = true;
            result[3] = true;
            break;
        case 4: case 8:
            result[0] = true; 
            result[1] = true;
            result[2] = true;
            result[3] = false;
            break;
        case 7: case 11:
            result[0] = true; 
            result[1] = false;
            result[2] = true;
            result[3] = true;
            break;
        case 12:
            result[0] = true; 
            result[1] = true;
            result[2] = false;
            result[3] = false;
            break;
        case 13: case 14:
            result[0] = true; 
            result[1] = true;
            result[2] = false;
            result[3] = true;
            break;
        case 15:
            result[0] = true; 
            result[1] = false;
            result[2] = false;
            result[3] = true;
            break;
        default:
            result[0] = true; 
            result[1] = true;
            result[2] = true;
            result[3] = true;
            break;
    }
    return result;
}

unique_ptr<uint8_t[]> Problem::result(const uint8_t state[16], int action) const {
    auto blank = this->findBlankSquare(state);
    unique_ptr<uint8_t[]> newState(new uint8_t(16));
    memcpy(newState.get(), state, 16 * sizeof(uint8_t));

    auto neighbor = blank + this->delta[action];
    swap(newState[blank], newState[neighbor]);

    return newState;
}

bool Problem::goalTest(const uint8_t state[16]){
    for(int i=0; i<16; i++){
        if(this->goalState[i] != state[i]){
            return false;
        }
    }
    return true;
}

bool Problem::checkSolvable(const uint8_t state[16]){
    int inversions = 0;
    for(int i=0; i<16; i++){
        for(int j=i+1; j <16; j++){
            if(state[i] && state[j] && state[i] > state[j]){
                inversions++;
            }
        }
    }
    if(getLoc(this->findBlankSquare(state)).second % 2 && !(inversions % 2)){
        return true;
    }
    else if(!getLoc(this->findBlankSquare(state)).second % 2 && (inversions % 2)){//even row && even inversion
        return true;
    }
    return false;
}

size_t Problem::getHash(const uint8_t state[16]){
    char shiftedState[17];
    for(int i=15; i>=0; i--){
        shiftedState[i] = 65 + state[i];
    }
    shiftedState[16] = '\0';
    string str = shiftedState;
    return this->hash_fn(str);
}

int Problem::h(Node* node, Database* db){
    return db->checkRow(node->state, 0) + db->checkRow(node->state, 1) + db->checkRow(node->state, 2);
}

Node* Problem::depth_limited_search(Node* node, int limit, Database *db, stack<unique_ptr<Node>>& history){
    if(this->goalTest(node->state)){
        return node;
    }
    else if(!limit){
        return NULL;
    }

    vector<unique_ptr<Node>> children;
    node->expand(this, children);


    for(int i=0; i<children.size(); i++){
        if( this->h(children[i].get(), db) > limit){
            continue;
        }
        history.push(move(children[i]));
        auto result = depth_limited_search(history.top().get(), limit-1, db, history);
        if(result){
            return result;
        }
        history.pop();
    }
    return NULL;
}

Node* Problem::iterative_deepening_search(int limit, Database* db, std::stack<std::unique_ptr<Node>>& history){
    for(int i=0; i<limit; i++){
        history.push(unique_ptr<Node>(new Node(this->initState)));
        auto result = depth_limited_search(history.top().get(), i, db, history);
        if(result){
            return history.top().get();
        }
        history.pop();
        if(!history.empty()){
            throw "Stack not empty at end!";
        }
    }
    return NULL;
}