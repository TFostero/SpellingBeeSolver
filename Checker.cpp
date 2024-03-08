#include "Checker.h"

Checker::Checker(string reqChars, string optChars) {
    for (int i = 0; i < reqChars.size(); i++) {
        this->reqChars.insert(reqChars[i]);
        this->usableChars.insert(reqChars[i]);
    }
    for (int i = 0; i < optChars.size(); i++) {
        this->usableChars.insert(optChars[i]);
    }
}

vector<string> Checker::getValidWords() {
    return this->validWords;
}

bool Checker::check(string word) {
    bool containsReq = false;
    if (word.length() < MIN_WORD_LENGTH) {
        return false;
    }

    for (int i = 0; i < word.size(); i++) {
        if (this->usableChars.find(word[i]) == this->usableChars.end()) {
            return false;
        }
        if (this->reqChars.find(word[i]) == this->reqChars.end()) {
            containsReq = true;
        }
    }

    if (containsReq) {
        this->validWords.emplace_back(word);
    }

    return containsReq;
}