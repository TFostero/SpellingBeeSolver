#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#define MIN_WORD_LENGTH 4

using namespace std;

class Trie {
    public:
    Trie();

    void insert(string word);
    bool search(string word);
    vector<string> solve(string, string);
    Node* getRoot();

    private:
    Node* root;
    void solveHelper(Node*, vector<string>&, string, string, string);
};

#endif 
