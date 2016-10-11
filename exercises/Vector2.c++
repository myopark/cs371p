// -----------
// Vector2.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <vector> // vector

#include "gtest/gtest.h"

#include "Vector2.h"

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

    const vector_type x(10, 2);
    const vector_type y = x;
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(x, y);}

TYPED_TEST(VectorFixture, test_2) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(20, 3);
          vector_type y(10, 2);
    y = x;
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(x, y);}
