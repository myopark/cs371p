// --------
// RMSE.c++
// --------

#include <functional> // function
#include <list>       // list
#include <vector>     // vector

#include "gtest/gtest.h"

#include "RMSE.h"

using namespace std;
using namespace testing;

using RMSEListSignature = function<bool (list<int>::const_iterator, list<int>::const_iterator, vector<int>::const_iterator)>;

struct RMSEListFixture : TestWithParam<RMSEListSignature>
    {};

INSTANTIATE_TEST_CASE_P(
    RMSEListInstantiation,
    RMSEListFixture,
    Values(
        rmse_while<list<int>::const_iterator, vector<int>::const_iterator>,
        rmse_transform_accumulate<list<int>::const_iterator, vector<int>::const_iterator>));

TEST_P(RMSEListFixture, test_1) {
    const list<int>   x = {2, 3, 4};
    const vector<int> y = {2, 3, 4};
	ASSERT_FLOAT_EQ(0, GetParam()(begin(x), end(x), begin(y)));}

TEST_P(RMSEListFixture, test_2) {
    const list<int>   x = {2, 3, 4};
    const vector<int> y = {3, 2, 5};
	ASSERT_FLOAT_EQ(1, GetParam()(begin(x), end(x), begin(y)));}

TEST_P(RMSEListFixture, test_3) {
    const list<int>   x = {2, 3, 4};
    const vector<int> y = {4, 1, 6};
	ASSERT_FLOAT_EQ(2, rmse_transform_accumulate(begin(x), end(x), begin(y)));}

TEST_P(RMSEListFixture, test_4) {
    const list<int>   x = {2, 3, 4};
    const vector<int> y = {4, 3, 2};
	ASSERT_FLOAT_EQ(1.6329932, rmse_transform_accumulate(begin(x), end(x), begin(y)));}
