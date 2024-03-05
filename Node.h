#ifndef NODE_H
#define NODE_H


#include <unordered_map>

using namespace std;

class Node {
    public:
    unordered_map<char, Node*> map;
    bool isWord;

    Node();
};

#endif
