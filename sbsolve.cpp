#include "sbsolve.h"

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

    string dictfile = string(argv[1]);
    string optionalChars = string(argv[2]);
    string requiredChars = string(argv[3]);
    cout << "Optional characters: " << optionalChars << "\n";
    cout << "Required characters: " << requiredChars << "\n";

    chrono::time_point<chrono::_V2::system_clock> start, end;
    chrono::duration<float> duration;
    float ms;

    start = chrono::high_resolution_clock::now();

    Solver solver(dictfile);

    vector<string> results = solver.solve(optionalChars, requiredChars);

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
