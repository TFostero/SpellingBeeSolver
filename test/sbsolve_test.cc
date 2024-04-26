#include <gtest/gtest.h>
#include "Solver.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    unsigned int threads = thread::hardware_concurrency();
    Solver solver(threads);
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
