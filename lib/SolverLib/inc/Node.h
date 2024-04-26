#ifndef NODE_H
#define NODE_H

#define ALPHAS 26

using namespace std;

class Node {
    public:
    Node* children[ALPHAS];
    bool isWord;

    Node();
};

#endif
