#include "sbsolve.h"
#include "Trie.h"
#include "Checker.h"

using namespace std;

static mutex mtx;

/*
 * TODO: 
 * create THREAD_CNT number of Trie objects with each being a subset of the dictionary words (dict.size() / THREAD_CNT)
 * create binary files from those objects if they don't already exist
 * create Trie objects from those binary files
 * use async to call to both create Trie objects from binary files and call solve for those Trie objects
 * 
 * Start with just saving and using one Trie and see what the increase in speed is
 */

vector<string> solve(Checker checker, ifstream &dict) {
    string word;
    mtx.lock();
    while (getline(dict, word)) {
        mtx.unlock();
        checker.check(word);
        mtx.lock();
    }

    mtx.unlock();
    return checker.getValidWords();
}

vector<string> solve2(Checker checker, vector<string> dict) {
    for (auto& word : dict) {
        checker.check(word);
    }
    return checker.getValidWords();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 1;
    }

    chrono::time_point<chrono::_V2::system_clock> start, end;
    chrono::duration<float> duration;
    float ms;

    start = chrono::high_resolution_clock::now();

    ifstream DictFile(argv[1]);
    // vector<string> dict;
    vector<string> results;
    Trie trie;
    string text;
    while (getline(DictFile, text)) {
        trie.insert(text);
    }

    
    string optionalChars = string(argv[2]);
    string requiredChars = string(argv[3]);
    cout << "Optional characters: " << optionalChars << "\n";
    cout << "Required characters: " << requiredChars << "\n";

    results = trie.solve(optionalChars, requiredChars);

    /*
    vector<future<vector<string>>> futures;
    for (int i = 0; i < THREAD_CNT; i++) {
        Checker checker = Checker(requiredChars, optionalChars);
        futures.push_back(async(launch::async, solve, checker, ref(DictFile)));
    }
    */

    /*   
    vector<future<vector<string>>> futures;
    int chunkSize = dict.size() / CHUNKS;
    cout << "Dict size: " << dict.size() << "\n";
    for (int i = 0; i < CHUNKS; i++) {
        int start = i * chunkSize;
        int end = (i * chunkSize) + (chunkSize - 1);

        if (end >= dict.size()) {
            end = dict.size() - 1;
        }

        vector<string> dictChunk(chunkSize);
        copy(dict.begin() + start, dict.begin() + end, dictChunk.begin());
        Checker checker = Checker(requiredChars, optionalChars);
        futures.push_back(async(launch::async, solve2, checker, dictChunk));
    }


    vector<string> results;
    for (auto& future : futures) {
        vector<string> result = future.get();
        results.insert(results.end(), result.begin(), result.end());
    }
    */

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    ms = duration.count() * 1000.0f;
    cout << "Duration (ms): " << ms << "\n";


    sort(results.begin(), results.end());

    for (auto& result : results) {
        cout << result << "\n";
    }

    return 0;
}
