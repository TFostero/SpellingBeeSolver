#ifndef SOLVER_H
#define SOLVER_H

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <future>
#include "Trie.h"

#define DICT_PATH_PRIMARY "../dicts/sbsolvedict.txt"
#define DICT_PATH_SECONDARY "/sbsolvedict.txt"

using namespace std;

class Solver {
    public:
    Solver();
    Solver(unsigned int);
    vector<string> solve(string, string);

    private:
    mutex triesMutex;
    mutex dictChunksMutex;
    mutex solveMutex;
    unsigned int threads;
    vector<Trie> tries;
    vector<string> dict;
    vector<vector<string>> dictChunks;

    void loadTrie(int);
    void initDictionary();
};

#endif