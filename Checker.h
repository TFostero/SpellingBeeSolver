#ifndef CHECKER_H
#define CHECKER_H

#include <string>
#include <unordered_set>
#include <vector>

#define MIN_WORD_LENGTH 4

using namespace std;

class Checker {
    public:
    Checker(string reqChars, string optChars);
    bool check(string word);
    vector<string> getValidWords(void);

    private:
    vector<string> validWords;
    unordered_set<char> reqChars;
    unordered_set<char> usableChars;
};

#endif