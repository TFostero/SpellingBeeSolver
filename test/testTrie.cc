#include <gtest/gtest.h>
#include "Trie.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(TestTrie, InsertWordAndSearch) {
  // Expect two strings not to be equal.
  string testWord = "test";
  Trie trie;
  EXPECT_FALSE(trie.search(testWord));
  trie.insert(testWord);
  EXPECT_TRUE(trie.search(testWord));
}