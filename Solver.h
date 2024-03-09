#ifndef SOLVER_H
#define SOLVER_H

#include <sys/stat.h>
#include <errno.h>
#include <future>
#include "Trie.h"

#define THREAD_COUNT 8
#define TRIE_BIN_PATH "bin/trie"
#define TRIE_BIN "bin"

class Solver {
    public:
    vector<Trie> tries;
    Solver(string dictfile);
    vector<string> solve(string optionalChars, string requiredChars);


    private:
    vector<string> dict;
    vector<vector<string>> dictChunks;
    void loadTrie(int index);
    void initDictionary(string dictfile);
};

#endif