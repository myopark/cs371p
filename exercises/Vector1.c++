// -----------
// Vector1.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <algorithm> // equal
#include <vector>    // vector

#include "gtest/gtest.h"

#include "Vector1.h"

using namespace std;
using namespace testing;

template <typename T>
struct VectorFixture : Test {
    using vector_type = T;};

using
    vector_types =
    Types<
           vector<int>,
        my_vector<int>>;

TYPED_TEST_CASE(VectorFixture, vector_types);

TYPED_TEST(VectorFixture, test_1) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x;
    ASSERT_EQ(0, x.size());}

TYPED_TEST(VectorFixture, test_2) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x(3);
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 0, 0})));
    ASSERT_EQ(0, x[1]);
    x[1] = 2;
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 2, 0})));
    fill(begin(x), end(x), 4);
    ASSERT_TRUE(equal(begin(x), end(x), begin({4, 4, 4})));}

TYPED_TEST(VectorFixture, test_3) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(3, 2);
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 2, 2})));
    ASSERT_EQ(2, x[1]);
    // x[1] = 3;                                            // error: cannot assign to return value because function 'operator[]' returns a const value
    const vector_type y(6, 2);
    ASSERT_TRUE(equal(begin(x), end(x), begin(y)));}

TYPED_TEST(VectorFixture, test_4) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x{2, 3, 4};
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 3, 4})));}
