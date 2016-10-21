// -----------
// Vector4.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <vector> // vector

#include "gtest/gtest.h"

#include "Vector4.h"

using namespace std;
using namespace testing;

template <typename T>
struct VectorFixture : Test {
    using vector_type    = T;
    using allocator_type = typename vector_type::allocator_type;};

using
    vector_types =
    Types<
           vector<int>,
        my_vector<int>,
           vector<int, allocator<int>>,
        my_vector<int, allocator<int>>>;

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
    ASSERT_EQ(0, x.at(1));
    x.at(1) = 2;
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 2, 0})));
    ASSERT_THROW(x.at(3), out_of_range);}

TYPED_TEST(VectorFixture, test_3) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(3, 2);
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 2, 2})));
    ASSERT_EQ(2, x.at(1));
    // x.at(1) = 3;                                         // error: read-only variable is not assignable
    const vector_type y(6, 2);
    ASSERT_TRUE(equal(begin(x), end(x), begin(y)));}

TYPED_TEST(VectorFixture, test_4) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x{2, 3, 4};
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 3, 4})));}

TYPED_TEST(VectorFixture, test_5) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(10, 2);
    const vector_type y = x;
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(x, y);}

TYPED_TEST(VectorFixture, test_6) {
    using vector_type = typename TestFixture::vector_type;

                   vector_type           x(10, 2);
    typename       vector_type::iterator b = begin(x);
             const vector_type           y = move(x);
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(b,        begin(y));}

TYPED_TEST(VectorFixture, test_7) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(20, 3);
          vector_type y(10, 2);
    y = x;
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(x, y);}

TYPED_TEST(VectorFixture, test_8) {
    using vector_type = typename TestFixture::vector_type;

             vector_type           x(20, 3);
             vector_type           y(10, 2);
    typename vector_type::iterator b = begin(x);
    y = move(x);
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(b,        begin(y));}

TYPED_TEST(VectorFixture, test_9) {
    using vector_type    = typename TestFixture::vector_type;
    using allocator_type = typename TestFixture::allocator_type;

    const vector_type x(3, 2, allocator_type());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 2, 2})));}

TYPED_TEST(VectorFixture, test_10) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(10, 2);
    const vector_type y(10, 2);
    const vector_type z(10, 3);
    ASSERT_EQ(x, y);
    ASSERT_NE(x, z);
    ASSERT_LT(x, z);
    ASSERT_LE(x, y);
    ASSERT_GT(z, x);
    ASSERT_GE(x, y);}
