#include "sbsolve.h"
#include "Trie.h"

using namespace std;

int main(int argc, char* argv[]) {
    Trie trie;

    if (argc >= 2) {
        ifstream DictFile(argv[1]);
        string text;
        while (getline(DictFile, text)) {
            // cout << "Inserting word: " << text << "\n";
            trie.insert(text);
        }
    }

    string optionalChars = string(argv[2]);
    string requiredChars = string(argv[3]);
    cout << "Optional characters: " << optionalChars << "\n";
    cout << "Required characters: " << requiredChars << "\n";

    vector<string> words = trie.solve(optionalChars, requiredChars);
    cout << "Found " << words.size() << " matching words.\n";
    for (auto& word : words) {
        cout << word << "\n";
    }

    return 0;
}
