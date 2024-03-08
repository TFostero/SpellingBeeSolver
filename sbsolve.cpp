#include "sbsolve.h"
#include "Trie.h"
#include "Checker.h"

using namespace std;

mutex mtx;

// globals for multithreading
int lineNum = 0;
vector<string> words;
vector<string> results;

void solveThread(Checker checker) {
    int idx;
    int size;
    mtx.lock();
    idx = lineNum;
    size = words.size();
    mtx.unlock();

    while (idx <= size - 1) {
        mtx.lock();
        string word = words[idx];
        mtx.unlock();

        checker.check(word);

        mtx.lock();
        lineNum++;
        idx = lineNum;
        mtx.unlock();
    }

    vector<string> validWords = checker.getValidWords();
    mtx.lock();
    results.insert(results.end(), validWords.begin(), validWords.end());
    mtx.unlock();

}

int main(int argc, char* argv[]) {
    // Trie trie;
    if (argc >= 2) {
        ifstream DictFile(argv[1]);
        string text;
        while (getline(DictFile, text)) {
            // cout << "Inserting word: " << text << "\n";
            // trie.insert(text);
            words.emplace_back(text);
        }
    }

    string optionalChars = string(argv[2]);
    string requiredChars = string(argv[3]);
    cout << "Optional characters: " << optionalChars << "\n";
    cout << "Required characters: " << requiredChars << "\n";

    vector<Checker> checkers;
    for (int i = 0; i < THREAD_CNT; i++) {
        Checker checker = Checker(requiredChars, optionalChars);
        checkers.emplace_back(checker);
    }

    int line = 0;
    thread threads[THREAD_CNT];
    for (int i = 0; i < THREAD_CNT; i++) {
        threads[i] = thread(solveThread, checkers[i]);
    }

    for (int i = 0; i < THREAD_CNT; i++) {
        threads[i].join();
    }

    for (auto& result : results) {
        cout << result << "\n";
    }

    /*
    vector<string> words = trie.solve(optionalChars, requiredChars);
    cout << "Found " << words.size() << " matching words.\n";
    for (auto& word : words) {
        cout << word << "\n";
    }
    */

    return 0;
}
