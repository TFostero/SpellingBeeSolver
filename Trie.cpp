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
            validWords.push_back(wordSoFar);
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

void Trie::serializeTrie(Node* node, ofstream& outfile) {
    if (node == nullptr) {
        outfile << "/ "; // Using '/' to represent a null node
        return;
    }
    outfile << node->isWord << " ";
    for (int i = 0; i < ALPHAS; ++i) {
        serializeTrie(node->children[i], outfile);
    }
}

Node* Trie::deserializeTrie(ifstream& infile) {
    string val;
    infile >> val;
    if (val == "/") {
        return nullptr;
    }
    Node* node = new Node();
    node->isWord = stoi(val);
    for (int i = 0; i < ALPHAS; ++i) {
        node->children[i] = deserializeTrie(infile);
    }
    return node;
}

void Trie::saveTrieToFile(const string& filename) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        serializeTrie(root, outfile);
        outfile.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void Trie::loadTrieFromFile(const string& filename) {
    ifstream infile(filename);
    root = nullptr;
    if (infile.is_open()) {
        root = deserializeTrie(infile);
        infile.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}
