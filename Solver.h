#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <fstream>
#include <future>
#include "Trie.h"

#define THREAD_COUNT 16

class Solver {
    public:
    vector<Trie> tries;
    Solver(string dictfile);
    vector<string> solve(string optionalChars, string requiredChars);


    private:
    vector<string> dict;
    vector<vector<string>> dictChunks;
    void loadTrie(string dictfile, int index);
    void initDictionary(string dictfile);
};

#endif