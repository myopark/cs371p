// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// ----
// test
// ----

TEST(DarwinFixture, test) {
    Darwin x;
    ASSERT_TRUE(x.dummy());}
