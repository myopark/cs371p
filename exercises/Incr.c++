// --------
// Incr.c++
// --------

// http://en.cppreference.com/w/cpp/language/operator_incdec

#include "gtest/gtest.h"

#include "Incr.h"

TEST(IncrFixture, test_1) {
    int i = 2;
    int j = pre_incr(i);
    ASSERT_EQ(3, i);
    ASSERT_EQ(3, j);}

TEST(IncrFixture, test_2) {
    int i = 2;
    int j = pre_incr(pre_incr(i));
    ASSERT_EQ(4, i);
    ASSERT_EQ(4, j);}

TEST(IncrFixture, test_3) {
    int i = 2;
    int j = post_incr(i);
    ASSERT_EQ(3, i);
    ASSERT_EQ(2, j);}

TEST(IncrFixture, test_4) {
    int i = 2;
//  post_incr(post_incr(i)); // error: no matching function for call to 'post_incr'
    ASSERT_EQ(2, i);}
