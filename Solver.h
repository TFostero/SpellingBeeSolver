#ifndef SOLVER_H
#define SOLVER_H

#include <sys/stat.h>
#include <errno.h>
#include <future>
#include "Trie.h"

#define THREAD_COUNT 8
#define TRIE_BIN "bin"
#define TRIE_BIN_PATH "bin/trie"
#define DICT_PATH "dicts/bigdict.txt"

using namespace std;

class Solver {
    public:
    Solver();
    vector<string> solve(string, string);

    private:
    vector<Trie> tries;
    vector<string> dict;
    vector<vector<string>> dictChunks;
    void loadTrie(int);
    void initDictionary(void);
};

#endif