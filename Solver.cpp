#include "Solver.h"

Solver::Solver(string dictfile) {
    // if binaries exist -> create Tries from existing binaries
    // if not, then create new Tries then save as binaries

    // TODO: figure out how to multithread this
    vector<future<Trie>> futures;
    for (int i = 0; i < THREAD_COUNT; i++) {
        string filename = "Bin/trie" + to_string(i) + ".bin";
        futures.push_back(async(launch::async, &Trie::loadTrieFromFile, filename));
    }

    for (auto& future : futures) {
        tries.push_back(future.get());
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        if (!tries[i].root) {
            loadTrie(dictfile, i);
        }
    }
}

void Solver::loadTrie(string dictfile, int index) {
    if (dict.size() == 0) {
        initDictionary(dictfile);
    }
    
    Trie trie;
    for (string word : dictChunks[index]) {
        trie.insert(word);
    }
    string filename = "Bin/trie" + to_string(index) + ".bin";
    Trie::saveTrieToFile(trie, filename);
    tries[index] = trie;
}

void Solver::initDictionary(string dictfile) {
    ifstream DictFile(dictfile);
    string text;
    while (getline(DictFile, text)) {
        dict.push_back(text);
    }

    int chunkSize = dict.size() / THREAD_COUNT;
    for (int i = 0; i < THREAD_COUNT; i++) {
        vector<string> dictChunk;
        dictChunks.push_back(dictChunk);
        for (int j = 0; j < chunkSize; j++) {
            dictChunks[i].push_back(dict[i*chunkSize + j]);
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