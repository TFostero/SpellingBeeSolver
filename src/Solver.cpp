#include "Solver.h"


Solver::Solver() {
    vector<future<Trie>> futures;
    for (int i = 0; i < THREAD_COUNT; i++) {
        string filename = TRIE_BIN_PATH + to_string(i);
        futures.push_back(async(launch::async, &Trie::loadTrieFromFile, filename));
    }

    for (auto& future : futures) {
        tries.push_back(future.get());
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        if (!tries[i].getRoot()) {
            if (dict.size() == 0) {
                initDictionary();
            }
            loadTrie(i);
        }
    }
}

void Solver::loadTrie(int index) {
    Trie trie;
    for (string word : dictChunks[index]) {
        trie.insert(word);
    }
    string filename = TRIE_BIN_PATH + to_string(index);
    mkdir(TRIE_BIN, S_IRWXU | S_IRWXG);
    Trie::saveTrieToFile(trie, filename);
    tries[index] = trie;
}

void Solver::initDictionary() {
    ifstream DictFile(DICT_PATH);
    string text;
    while (getline(DictFile, text)) {
        dict.push_back(text);
    }

    dictChunks.resize(THREAD_COUNT);
    size_t count = 0;
    while (count < dict.size()) {
        for (int i = 0; i < THREAD_COUNT; i++) {
            dictChunks[i].push_back(dict[count]);
            count++;
        }
    }
}

vector<string> Solver::solve(string optionalChars, string requiredChars) {
    vector<future<vector<string>>> futures;
    for (int i = 0; i < THREAD_COUNT; i++) {
        futures.push_back(async(launch::async, &Trie::solve, tries[i], optionalChars, requiredChars));
    }
 
    vector<string> results;
    for (auto& future : futures) {
        vector<string> result = future.get();
        results.insert(results.end(), result.begin(), result.end());
    }

    return results;
}