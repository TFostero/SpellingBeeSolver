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
    Node* root;
    Trie();

    void insert(string word);
    bool search(string word);
    vector<string> solve(string optionalChars, string requiriedChars);
    static void saveTrieToFile(Trie trie, const string& filename);
    static Trie loadTrieFromFile(const string& filename);

    private:
    void serializeTrie(Node* node, ofstream& outfile);
    Node* deserializeTrie(ifstream& infile);
    void solveHelper(Node* node, vector<string>& validWords, string optionalChars, string requiriedChars, string wordSoFar);
};

#endif 
