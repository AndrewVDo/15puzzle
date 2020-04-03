#include"fifteenPuzzle.h"

using namespace std;

const uint8_t Database::quadrantSymbol[4][4] = {
    { 1, 2 }, //type 1
    { 4, 3 },
    { 13, 14 },
    { 5, 6 }, //type 2
    { 8, 7 },
    { 9, 10 },
    { 12, 11 },
    { 0, 15 } //type 3
};

Database::Database(Problem* problem){
    this->problem = problem;
}

std::unique_ptr<uint8_t[]> Database::encodeState(const uint8_t state[16], int quadrant){
    auto symbols = this->quadrantSymbol[quadrant];
    unique_ptr<uint8_t[]> translatedState( new uint8_t[16] );
    memcpy(translatedState.get(), state, 16 * sizeof(uint8_t));
    for(int i=0; i<16; i++){
        if (translatedState[i] == 0) translatedState[i] = 0;
        else if(translatedState[i] == symbols[0]) translatedState[i] = 'A';
        else if(translatedState[i] == symbols[1]) translatedState[i] = 'B';
        else translatedState[i] = '*';
    }
    switch(quadrant){
        case 1:
            this->transformX(translatedState.get());
            break;
        case 2:
            this->transformY(translatedState.get());
            break;
        case 4:
            this->transformX(translatedState.get());
            break;
        case 5:
            this->transformY(translatedState.get());
            break;
        case 6:
            this->transformX(translatedState.get());
            this->transformY(translatedState.get());
            break;
    }
    return translatedState;
}

void Database::transformX(uint8_t state[16]){
    for(int i=0; i<4; i++){
        swap(state[i*4+0], state[i*4+3]);
        swap(state[i*4+1], state[i*4+2]);
    }
}

void Database::transformY(uint8_t state[16]){
    for(int i=0; i<4; i++){
        swap(state[0*4+i], state[3*4+i]);
        swap(state[1*4+i], state[2*4+i]);
    }
}

int Database::addRow(size_t key, int value){
    auto found = this->table.find(key);
    if(found != this->table.end()){
        this->table[key] = (this->table[key] > value) ? value : this->table[key];
        return 0;
    }
    this->table[key] = value;
    return 1;
}

int Database::checkRow(const uint8_t state[16], int quadrant){
    auto symbolState = this->encodeState(state, quadrant);
    auto key = this->problem->getHash(symbolState.get());
    return this->table[key];
}

void Database::expand(const uint8_t state[16], int currentDepth, std::queue<std::pair<std::unique_ptr<uint8_t[]>, int>> &frontier){
    auto actions = this->problem->actions(state);
    for(int j=3; j>=0; j--){
        if(!actions[j]) continue;
        frontier.push(make_pair(this->problem->result(state, j), currentDepth+1));
    }
}

#include<iostream>
void Database::breadthFirstSearch(){
    queue<pair<unique_ptr<uint8_t[]>, int>> frontier;
    frontier.push(make_pair(this->encodeState(this->problem->goalState, 0), 0));
    int databaseSize = 0;
    while(!frontier.empty() && databaseSize < 43680){ 
        auto hash = this->problem->getHash(frontier.front().first.get());
        auto depth = frontier.front().second;
        databaseSize += this->addRow(hash, depth);
        this->expand(frontier.front().first.get(), depth, frontier);
        frontier.pop();
        printf("%d\n", databaseSize);
    }
}

//hash ignore 0