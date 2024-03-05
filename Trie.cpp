#include "Trie.h"


Trie::Trie() {
    root = new Node();
}

void Trie::insert(string word) {
    insertHelper(root, word, 0);
}

bool Trie::search(string word) {
    return searchHelper(root, word, 0);
}

vector<string> Trie::solve(string optionalChars, string requiriedChars) {
    vector<string> words;
    string wordSoFar = "";
    solveHelper(root, words, optionalChars, requiriedChars, wordSoFar);
    return words;
}

void Trie::insertHelper(Node* node, string word, int i) {
    if (i == word.size()) {
        node->isWord = true;
        return;
    }

    auto p = node->map.find(word[i]);
    if (p == node->map.end()) {
        Node* n = new Node();
        node->map.insert(make_pair(word[i], n));
        insertHelper(n, word, i + 1);
    } else {
        insertHelper(p->second, word, i + 1);
    }
}

bool Trie::searchHelper(Node* node, string word, int i) {
    if (i == word.size() && node->isWord) {
        return true;
    }
    
    auto p = node->map.find(word[i]);
    if (p == node->map.end()) {
        return false;
    } else {
        return searchHelper(p->second, word, i + 1);
    }
}

void Trie::solveHelper(Node* node, vector<string>& validWords, string optionalChars, string requiriedChars, string wordSoFar) {
    // check if the word so far is a word and contains the required characters
    if (node->isWord) {
        bool valid = true;
        if (wordSoFar.size() < 3) {
            valid = false;
        } else {
            for (int i = 0; i < requiriedChars.size(); i++) {
                if (wordSoFar.find(requiriedChars[i]) == string::npos) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) {
            validWords.emplace_back(wordSoFar);
        }
    }

    string loopChars = optionalChars + requiriedChars;

    for (int i = 0; i < loopChars.size(); i++) {
        auto p = node->map.find(loopChars[i]);
        if (p != node->map.end()) {
            solveHelper(p->second, validWords, optionalChars, requiriedChars, wordSoFar + loopChars[i]);
        }
    }
}
