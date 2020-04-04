#include "fifteenPuzzle.h"

using namespace std;


Node::Node(const uint8_t state[16], Node* parent, int action){
    memcpy(this->state, state, 16 * sizeof(uint8_t));
    this->parent = parent;
    this->action = action;
    this->depth = parent ? parent->depth + 1 : 0;
}

std::unique_ptr<Node*[]> Node::expand(const Problem* problem){
    unique_ptr<Node*[]> result(new Node*[4]);
    auto actions = problem->actions(this->state);
    switch (this->action){
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
        result[i] = actions[i] ? child_node(problem, i) : NULL;
    }
    return result;
}

Node* Node::child_node(const Problem* problem, int action){
    auto next_state = problem->result(this->state, action);
    auto next_node = new Node(next_state.get(), this, action);
    return next_node;
}

unique_ptr<vector<int>> Node::solution(){
    auto path = this->path();
    unique_ptr<vector<int>> solution(new vector<int>());
    for(int i=0; i<path.get()->size(); i++){
        (solution.get())->push_back((*path)[i]->action);
    }
    return solution;
}

unique_ptr<vector<Node*>> Node::path(){
    auto node = this;
    unique_ptr<vector<Node*>> path_back(new vector<Node*>());
    while(node){
        (path_back.get())->push_back(node);
        node = node->parent;
    }
    reverse(path_back.get()->begin(), path_back.get()->end());
    return path_back;
}