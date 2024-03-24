#include "Solver.h"


Solver::Solver() {};

Solver::Solver(unsigned int threads) {
    this->threads = threads;
    if ((countTrieFiles() != this->threads) || !deserializeTries()) {
        // clearBin();
        initDictionary();

        vector<thread> threads;
        for (unsigned int i = 0; i < this->threads; i++) { 
            cout << "Creating trie " << i << endl;
            threads.push_back(thread(&Solver::loadTrie, this, i));
        }

        for (auto& thread : threads) { 
            thread.join();
        }

        cout << "Created " << this->threads << " tries." << endl;
    }
}


void Solver::clearBin() {
    /*
    DIR *dir;
    dir = opendir(TRIE_BIN);
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

    }
    */
}

unsigned int Solver::countTrieFiles() {
    unsigned int count = 0;
    DIR *dir;
    
    dir = opendir(TRIE_BIN);
    struct dirent *entry;

    if (dir != NULL) {
        while ((entry = readdir(dir))) {
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
                continue;
            }
            count++;
        }
        closedir(dir);
    }

    return count;
}

// return false if deseralizing fails or if no files initialized 
bool Solver::deserializeTries() {
    vector<future<Trie>> futures;
    for (unsigned int i = 0; i < this->threads; i++) {
        string filename = TRIE_BIN_PATH + to_string(i);
        futures.push_back(async(launch::async, &Trie::loadTrieFromFile, filename));
    }

    for (auto& future : futures) {
        tries.push_back(future.get());
    }

    for (auto& trie : tries) {
        if (!trie.getRoot()) {
            return false;
        }
    }

    cout << "Successfully deserialized " << this->threads << " tries." << endl;
    return true;
}

void Solver::loadTrie(int index) {
    Trie trie;

    triesMutex.lock();
    vector<string> trieDict = dictChunks[index];
    triesMutex.unlock();

    for (string word : trieDict) {
        trie.insert(word);
    }

    string filename = TRIE_BIN_PATH + to_string(index);
    // mkdir(TRIE_BIN, S_IRWXU | S_IRWXG);
    triesMutex.lock();
    Trie::saveTrieToFile(trie, filename);
    tries[index] = trie;
    triesMutex.unlock();
}

void Solver::initDictionary() {
    ifstream DictFile(DICT_PATH);
    string text;
    while (getline(DictFile, text)) {
        dict.push_back(text);
    }

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
    cout << tries.size() << endl;
    vector<future<vector<string>>> futures;
    for (unsigned int i = 0; i < this->threads; i++) {
        futures.push_back(async(launch::async, &Trie::solve, tries[i], optionalChars, requiredChars));
    }
 
    vector<string> results;
    for (auto& future : futures) {
        vector<string> result = future.get();
        results.insert(results.end(), result.begin(), result.end());
    }

    return results;
}