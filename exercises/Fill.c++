// --------
// Fill.c++
// --------

// http://en.cppreference.com/w/cpp/algorithm/fill

#include <algorithm>  // equal, fill
#include <cassert>    // assert
#include <functional> // function
#include <iostream>   // cout, endl
#include <vector>     // vector

#include "gtest/gtest.h"

#include "Fill.h"

using namespace std;
using namespace testing;

using FillListSignature = function<void (vector<int>::iterator, vector<int>::iterator, int)>;

struct FillListFixture : TestWithParam<FillListSignature>
    {};

INSTANTIATE_TEST_CASE_P(
    FillListInstantiation,
    FillListFixture,
    Values(
           fill<vector<int>::iterator, int>,
        my_fill<vector<int>::iterator, int>));

TEST_P(FillListFixture, test_1) {
    const int         v = 2;
          vector<int> x(5);
    GetParam()(begin(x) + 1, end(x) - 1, v);
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 2, 2, 2, 0})));}

TEST_P(FillListFixture, test_2) {
    const int         v = 3;
          vector<int> x(6);
    GetParam()(begin(x) + 1, end(x) - 1, v);
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 3, 3, 3, 3, 0})));}

/*
% Fill
Running main() from gtest_main.cc
[==========] Running 4 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 4 tests from FillListInstantiation/FillListFixture
[ RUN      ] FillListInstantiation/FillListFixture.test_1/0
[       OK ] FillListInstantiation/FillListFixture.test_1/0 (0 ms)
[ RUN      ] FillListInstantiation/FillListFixture.test_1/1
[       OK ] FillListInstantiation/FillListFixture.test_1/1 (0 ms)
[ RUN      ] FillListInstantiation/FillListFixture.test_2/0
[       OK ] FillListInstantiation/FillListFixture.test_2/0 (0 ms)
[ RUN      ] FillListInstantiation/FillListFixture.test_2/1
[       OK ] FillListInstantiation/FillListFixture.test_2/1 (0 ms)
[----------] 4 tests from FillListInstantiation/FillListFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 4 tests.
*/
