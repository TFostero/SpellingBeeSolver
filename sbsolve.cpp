#include "sbsolve.h"
#include "Trie.h"
#include "Checker.h"

using namespace std;

/*
 * TODO: 
 * create THREAD_CNT number of Trie objects with each being a subset of the dictionary words (dict.size() / THREAD_CNT)
 * create binary files from those objects if they don't already exist
 * create Trie objects from those binary files
 * use async to call to both create Trie objects from binary files and call solve for those Trie objects
 * 
 * Start with just saving and using one Trie and see what the increase in speed is
 */

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 1;
    }

    string optionalChars = string(argv[2]);
    string requiredChars = string(argv[3]);
    cout << "Optional characters: " << optionalChars << "\n";
    cout << "Required characters: " << requiredChars << "\n";

    chrono::time_point<chrono::_V2::system_clock> start, end;
    chrono::duration<float> duration;
    float ms;

    start = chrono::high_resolution_clock::now();

    vector<Trie> tries(THREAD_COUNT);
    for (int i = 0; i < THREAD_COUNT; i++) {
        string fileName = "Bin/trie" + to_string(i) + ".bin";
        tries[i].loadTrieFromFile(fileName);
        if (!tries[i].root) {
            ifstream DictFile(argv[1]);
            vector<string> dict;
            string text;
            while (getline(DictFile, text)) {
                dict.push_back(text);
            }

            vector<vector<string>> dictChunks(THREAD_COUNT);
            int count = 0;
            while(count < dict.size()) {
                for (int i = 0; i < THREAD_COUNT; i++) {
                    dictChunks[i].push_back(dict[count]);
                    count++;
                }
            }

            for (int i = 0; i < THREAD_COUNT; i++) {
                Trie trie;
                for (string word : dictChunks[i]) {
                    trie.insert(word);
                }
                tries[i] = trie;
            }

            tries[i].saveTrieToFile(fileName);
        }
    }

    vector<future<vector<string>>> futures;
    for (int i = 0; i < THREAD_COUNT; i++) {
        futures.push_back(async(launch::async, &Trie::solve, tries[i], optionalChars, requiredChars));
    }

    vector<string> results;
    for (auto& future : futures) {
        vector<string> result = future.get();
        results.insert(results.end(), result.begin(), result.end());
    }

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    ms = duration.count() * 1000.0f;
    cout << "Duration (ms): " << ms << "\n";

    sort(results.begin(), results.end());

    for (auto& result : results) {
        cout << result << "\n";
    }

    cout << results.size() << endl;

    return 0;
}
