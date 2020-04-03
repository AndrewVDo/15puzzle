#include"fifteenPuzzle.h"

using namespace std;

Database::Database(Problem* problem){
    this->problem = problem;
}

std::unique_ptr<uint8_t[]> Database::encodeState(const uint8_t state[16], int quadrant){
    unique_ptr<uint8_t[]> encodedState( new uint8_t[16] );
    memcpy(encodedState.get(), state, 16 * sizeof(uint8_t));
    switch(quadrant){
        case 0:
            for(int i=0; i<16; i++){
                if(encodedState[i] != 1 && encodedState[i] != 5 && encodedState[i] != 6 && encodedState[i] != 9 && encodedState[i] != 10 && encodedState[i] != 13  && encodedState[i] != 0)
                    encodedState[i] = '*';
            };
            break;
        case 1:
            for(int i=0; i<16; i++){
                if(encodedState[i] != 7 && encodedState[i] != 8 && encodedState[i] != 11 && encodedState[i] != 12 && encodedState[i] != 14 && encodedState[i] != 15 && encodedState[i] != 0)
                    encodedState[i] = '*';
            };
            break;
        case 2:
            for(int i=0; i<16; i++){
                if(encodedState[i] != 2 && encodedState[i] != 3 && encodedState[i] != 4 && encodedState[i] != 0)
                    encodedState[i] = '*';
            };
            break;
    }
    return encodedState;
}

int Database::addRow(size_t key, int value){
    auto found = this->table.find(key);
    if(found == this->table.end()){
        this->table[key] = value;
        return 1; //new
    }
    if(this->table[key] > value){
        this->table[key] = value;
        return 0; //replace
    }
    return -1; //none
}

int Database::checkRow(const uint8_t state[16], int quadrant){
    auto encodedState = this->encodeState(state, quadrant);
    auto key = this->problem->getHash(encodedState.get());
    return this->table[key];
}

int Database::expand(Node* node, std::queue<std::unique_ptr<Node>>* frontier){
    auto result = this->addRow(this->problem->getHash(node->state), node->depth);
    if(result < 0) return 0;

    auto actions = problem->actions(node->state);
    switch (node->action){
        case 0:
            actions[2] = false;
            break;
        case 1:
            actions[3] = false;
            break;
        case 2:
            actions[0] = false;
            break;
        case 3:
            actions[1] = false;
            break;
    }
    for(int i=0; i<4; i++){
        if(actions[i]){
            frontier->push(unique_ptr<Node>(node->child_node(this->problem, i)));
        }
    }
    return result;
}

void Database::breadthFirstSearch(){
    queue<unique_ptr<Node>> frontier;
    frontier.push(unique_ptr<Node>(new Node(this->encodeState(this->problem->goalState, 0).get())));
    frontier.push(unique_ptr<Node>(new Node(this->encodeState(this->problem->goalState, 1).get())));
    frontier.push(unique_ptr<Node>(new Node(this->encodeState(this->problem->goalState, 2).get())));

    int databaseSize = 0;
    while(!frontier.empty() && databaseSize < 100000/*115,358,880*/){ 
        databaseSize += this->expand(frontier.front().get(), &frontier);
        frontier.pop();
        if(!(databaseSize % 10000)) printf("%d%\n", databaseSize/115358880);
    }
}

void Database::saveDB(char filename[128]){
    ofstream myfile;
    myfile.open(filename);
    for(pair<size_t. int> element : this->table){
        myfile << element.first << ' ' << element.second << '\n';
    }
    myfile.close();
}

void Database::loadDB(char filename[128]){
    ifstream myfile;
    myfile.open (filename);

    size_t a;
    int b;
    while (infile >> a >> b)
    {
        this->table[a] = b;
    }
}