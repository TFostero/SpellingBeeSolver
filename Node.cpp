#include "Node.h"

Node::Node() {
    isWord = false;
    for (int i = 0; i < ALPHAS; i++) {
        children[i] = nullptr;
    }
}
