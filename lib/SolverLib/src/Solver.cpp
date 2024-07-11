#include "Solver.h"


Solver::Solver() {};

// initialize the solve 
Solver::Solver(unsigned int threads) {
    this->threads = threads;
    tries.resize(this->threads);
    initDictionary();

    vector<thread> trieLoadThreads;
    for (unsigned int i = 0; i < this->threads; i++) { 
        trieLoadThreads.emplace_back(thread(&Solver::loadTrie, this, i));
    }

    for (auto& thread : trieLoadThreads) { 
        thread.join();
    }
}

void Solver::loadTrie(int index) {
    Trie trie;

    dictChunksMutex.lock();
    vector<string> trieDict = dictChunks[index];
    dictChunksMutex.unlock();

    for (string word : trieDict) {
        trie.insert(word);
    }

    triesMutex.lock();
    tries[index] = trie;
    triesMutex.unlock();
}

void Solver::initDictionary() {
    ifstream DictFile;
    DictFile.open(DICT_PATH_PRIMARY, ifstream::in);
    if (DictFile.fail()) {
        DictFile.open(DICT_PATH_SECONDARY, ifstream::in);
        if (DictFile.fail()) {
            cout << "Failed to find dictionary file." << endl;
        }
    }
    string text;
    while (getline(DictFile, text)) {
        dict.push_back(text);
    }
    DictFile.close();

    dictChunks.resize(this->threads);
    size_t count = 0;
    while (count < dict.size()) {
        for (unsigned int i = 0; i < this->threads; i++) {
            dictChunks[i].push_back(dict[count]);
            count++;
        }
    }
}

vector<string> Solver::solve(string optionalChars, string requiredChars) {
    solveMutex.lock(); 
    vector<future<vector<string>>> futures;
    for (unsigned int i = 0; i < this->threads; i++) {
        futures.push_back(async(launch::async, &Trie::solve, tries[i], optionalChars, requiredChars));
    }
 
    vector<string> results;
    for (auto& future : futures) {
        vector<string> result = future.get();
        results.insert(results.end(), result.begin(), result.end());
    }

    solveMutex.unlock();
    return results;
}