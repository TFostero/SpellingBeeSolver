#ifndef SOLVER_H
#define SOLVER_H

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <future>
#include "Trie.h"

#define TRIE_BIN "bin"
#define TRIE_BIN_PATH "bin/trie"
#define DICT_PATH_PRIMARY "dicts/bigdict.txt"
#define DICT_PATH_SECONDARY "../dicts/bigdict.txt"

using namespace std;

class Solver {
    public:
    Solver();
    Solver(unsigned int);
    vector<string> solve(string, string);

    private:
    mutex triesMutex;
    mutex dictChunksMutex;
    unsigned int threads;
    vector<Trie> tries;
    vector<string> dict;
    vector<vector<string>> dictChunks;
    unsigned int countTrieFiles();
    void clearBin();
    bool deserializeTries();
    void loadTrie(int);
    void initDictionary();
};

#endif