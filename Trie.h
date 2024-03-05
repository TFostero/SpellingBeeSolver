#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include <string>
#include <vector>

using namespace std;

class Trie {
    public:
    Node* root;
    Trie();
    void insert(string word);
    bool search(string word);
    vector<string> solve(string optionalChars, string requiriedChars);

    private:
    void insertHelper(Node* node, string word, int i);
    void solveHelper(Node* node, vector<string>& validWords, string optionalChars, string requiriedChars, string wordSoFar);
    bool searchHelper(Node* node, string word, int i);
};

#endif 
