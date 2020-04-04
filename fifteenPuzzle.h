#include<utility>
#include<vector>
#include<functional>
#include<tuple>
#include<bitset>
#include<algorithm>
#include<unordered_map>
#include<queue>
#include<fstream>


struct Problem;
struct Node;
struct Database;

struct Problem {

    uint8_t initState[16];
    static const uint8_t goalState[16];
    static const int delta[4];
    const std::hash<std::string> hash_fn;
    
    Problem(uint8_t initState[16]);
    int findBlankSquare(const uint8_t state[16]) const;
    std::unique_ptr<bool[]> actions(const uint8_t state[16]) const;
    std::unique_ptr<uint8_t[]> result(const uint8_t state[16], int action) const;
    bool goalTest(const uint8_t state[16]);
    bool checkSolvable(const uint8_t state[16]);
    size_t getHash(const uint8_t state[16]);
    int h(Node* node, Database* database);
    
};



struct Node {

    uint8_t state[16];
    int depth;
    int action;
    Node* parent;
        
    Node(const uint8_t state[16], Node* parent=NULL, int action=-1);
    std::unique_ptr<Node*[]> expand(const Problem* problem); //take all actions
    Node* child_node(const Problem* problem, int action); //create child as a result of an action
    std::unique_ptr<std::vector<int>> solution();
    std::unique_ptr<std::vector<Node*>> path();

};

struct Database {

    std::unordered_map<size_t, int> table;
    Problem* problem;

    Database(Problem* problem);
    std::unique_ptr<uint8_t[]> encodeState(const uint8_t state[16], int quadrant=0);
    void transformX(uint8_t state[16]);
    void transformY(uint8_t state[16]);
    int addRow(size_t key, int value);
    int checkRow(const uint8_t state[16], int quadrant);
    int expand(Node* node, std::queue<std::unique_ptr<Node>>* frontier);
    void breadthFirstSearch();

    void saveDB(char filename[128]);
    void loadDB(char filename[128]);
};


//void IDA(Database* db, int limit);