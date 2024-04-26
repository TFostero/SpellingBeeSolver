#include <gtest/gtest.h>
#include "Trie.h"

using namespace std;


TEST(TrieTest, trivialInsert) {
    Trie trie;
    string word = "word";
    string wordTwo = "wordtwo";

    EXPECT_FALSE(trie.search(""));
    EXPECT_FALSE(trie.search(word));
    EXPECT_FALSE(trie.search(wordTwo));

    trie.insert(word);
    EXPECT_TRUE(trie.search(word));
    EXPECT_FALSE(trie.search(wordTwo));

    trie.insert(wordTwo);
    EXPECT_TRUE(trie.search(word));
    EXPECT_TRUE(trie.search(wordTwo));
    EXPECT_FALSE(trie.search(""));
}

TEST(TrieTest, manyInsert) {
    ifstream DictFile;
    DictFile.open("../dicts/testDictionary.txt", ifstream::in);
    Trie trie;
    string text;
    vector<string> dict;
    while (getline(DictFile, text)) {
        dict.push_back(text);
        trie.insert(text);
    }
    DictFile.close();

    for (string word : dict) {
        EXPECT_TRUE(trie.search(word));
    }
    EXPECT_FALSE(trie.search("wordnotindict"));
}

TEST(TrieTest, trivialSolve) {
    ifstream DictFile;
    DictFile.open("../dicts/testDictionary.txt", ifstream::in);
    Trie trie;
    string text;
    vector<string> dict;
    while (getline(DictFile, text)) {
        dict.push_back(text);
        trie.insert(text);
    }
    DictFile.close();

    for (string word : dict) {
        EXPECT_TRUE(trie.search(word));
    }

    vector<string> results = trie.solve("abcdefghijklmnopqrstuvqxyz", "");
    for (string word : results) {
        // should find every word in dictionary
        EXPECT_TRUE(find(dict.begin(), dict.end(), word) != dict.end());
    }
}

TEST(TrieTest, complexSolve) {
    ifstream DictFile;
    DictFile.open("../dicts/testDictionary.txt", ifstream::in);
    Trie trie;
    string text;
    vector<string> dict;
    while (getline(DictFile, text)) {
        dict.push_back(text);
        trie.insert(text);
    }
    DictFile.close();

    vector<string> results = trie.solve("plem", "a");
    EXPECT_EQ(1, results.size());
    EXPECT_EQ(results[0], "apple"); // should find apple, but not map or ape (too short)
}