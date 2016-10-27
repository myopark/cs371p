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

using RMSEListSignature = function<double (list<double>::const_iterator, list<double>::const_iterator, vector<double>::const_iterator, double)>;

struct RMSEListFixture : TestWithParam<RMSEListSignature>
    {};

INSTANTIATE_TEST_CASE_P(
    RMSEListInstantiation,
    RMSEListFixture,
    Values(
        rmse_while<list<double>::const_iterator, vector<double>::const_iterator, double>,
        rmse_transform_accumulate<list<double>::const_iterator, vector<double>::const_iterator, double>,
        rmse_back_inserter<list<double>::const_iterator, vector<double>::const_iterator, double>));

TEST_P(RMSEListFixture, test_1) {
    const list<double>   x = {2, 3, 4};
    const vector<double> y = {2, 3, 4};
	ASSERT_FLOAT_EQ(0, GetParam()(begin(x), end(x), begin(y), 0.0));}

TEST_P(RMSEListFixture, test_2) {
    const list<double>   x = {2, 3, 4};
    const vector<double> y = {3, 2, 5};
	ASSERT_FLOAT_EQ(1, GetParam()(begin(x), end(x), begin(y), 0.0));}

TEST_P(RMSEListFixture, test_3) {
    const list<double>   x = {2, 3, 4};
    const vector<double> y = {4, 1, 6};
	ASSERT_FLOAT_EQ(2, GetParam()(begin(x), end(x), begin(y), 0.0));}

TEST_P(RMSEListFixture, test_4) {
    const list<double>   x = {2, 3, 4};
    const vector<double> y = {4, 3, 2};
	ASSERT_FLOAT_EQ(1.6329932, GetParam()(begin(x), end(x), begin(y), 0.0));}
