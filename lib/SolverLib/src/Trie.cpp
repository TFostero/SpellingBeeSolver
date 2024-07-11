#include "Trie.h"


Trie::Trie() {
    root = new Node();
}

void Trie::insert(string word) {
    Node* current = root;
    for (char c : word) {
        if (c < 'a' || c > 'z') {
            return;
        }
        int index = c - 'a';
    
        if (current->children[index] == nullptr) {
            current->children[index] = new Node();
        }
        current = current->children[index];
    }
    current->isWord = true;
}

bool Trie::search(string word) {
    Node* current = root;
    for (char c : word) {
        int index = c - 'a';
        if (!current->children[index]) {
            return false; // Word not found
        }
        current = current->children[index];
    }
    return current != nullptr && current->isWord;
}

// TODO: his function needs some work. 
vector<string> Trie::solve(string optionalChars, string requiriedChars) {
    vector<string> words;
    string wordSoFar = "";
    solveHelper(root, words, optionalChars, requiriedChars, wordSoFar);
    return words;
}

void Trie::solveHelper(Node* node, vector<string>& validWords, string optionalChars, string requiriedChars, string wordSoFar) {
    // check if the word so far is a word and contains the required characters
    if (node->isWord) {
        bool valid = true;
        if (wordSoFar.size() < MIN_WORD_LENGTH) {
            valid = false;
        } else {
            for (char c : requiriedChars) {
                if (wordSoFar.find(c) == string::npos) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) {
            if (find(validWords.begin(), validWords.end(), wordSoFar) == validWords.end()) {
                validWords.push_back(wordSoFar);
            }
        }
    }

    string loopChars = optionalChars + requiriedChars;

    for (char c : loopChars) {
        int index = c - 'a';
        if (node->children[index]) {
            solveHelper(node->children[index], validWords, optionalChars, requiriedChars, wordSoFar + c);
        }
    }
}

Node* Trie::getRoot() {
    return root;
}
