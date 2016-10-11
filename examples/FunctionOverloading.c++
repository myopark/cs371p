// -----------------------
// FunctionOverloading.c++
// -----------------------

// http://www.cplusplus.com/doc/tutorial/functions2/

// ad-hoc compile-time polymorphism

#include <cassert>  // assert
#include <cstring>  // strcmp
#include <iostream> // cout, endl
#include <string>   // string

using namespace std;

struct A {
    friend bool operator < (const A& lhs, const A& rhs) {
        return lhs._n < rhs._n;}

    int _n;

    A (int n) :
            _n (n)
        {}};

struct B : A {
    B (int n) :
            A (n)
        {}};



int my_max (int x, int y) {
    if (x < y)
        return y;
    return x;}

const int* my_max (const int* x, const int* y) {
    if (*x < *y)
        return y;
    return x;}

const char* my_max (const char* x, const char* y) {
    if (strcmp(x, y) < 0)
        return y;
    return x;}

const A& my_max (const A& x, const A& y) {
    if (x < y)
        return y;
    return x;}



string f (int) {              // l-value or r-value
    return "f(int)";}

//string f (const int) {      // error: redefinition of "string f(int)"
//    return "f(const int)";}



string g (int&) {            // non-const l-value
    return "g(int&)";}



string h (const int&) {      // l-value or r-value
    return "h(const int&)";}



string p (int&) {            // non-const l-value
    return "p(int&)";}

string p (const int&) {      // const l-value or r-value
    return "p(const int&)";}



string q (int&) {            // non-const l-value
    return "q(int&)";}

string q (int&&) {           // r-value
    return "q(int&&)";}



string r (const int&) {      // l-value
    return "r(const int&)";}

string r (int&&) {           // r-value
    return "r(int&&)";}



string s (int&) {            // non-const l-value
    return "s(int&)";}

string s (const int&) {      // const l-value
    return "s(const int&)";}

string s (int&&) {           // r-value
    return "s(int&&)";}



int main () {
    cout << "FunctionOverloading.c++" << endl;

    assert(my_max(2,   3)   == 3);
//  assert(my_max(2,   3.4) == 3); // warning: implicit conversion from 'double' to 'int' changes value from 3.4 to 3
//  assert(my_max(2.3, 4)   == 4); // warning: implicit conversion from 'double' to 'int' changes value from 2.3 to 2
//  assert(my_max(2.3, 4.5) == 4); // warning: implicit conversion from 'double' to 'int' changes value from 2.3 to 2
                                   // warning: implicit conversion from 'double' to 'int' changes value from 4.5 to 4

    {
    int i = 2;
    int j = 3;
    assert(my_max(&i, &j) == &j);
    }

    assert(strcmp(my_max("abc", "def"), "def") == 0);

    {
    A x = 2;
    A y = 3;
    assert(&my_max(x, y) == &y);
    }

    {
    B x = 2;
    B y = 3;
    assert(&my_max(x, y) == &y);
    }

    {
          int i  = 2;
    const int ci = 3;

    assert(f(i)  == "f(int)");
    assert(f(ci) == "f(int)");
    assert(f(4)  == "f(int)");

    assert(g(i)  == "g(int&)");
//  g(ci);                            // error: no matching function for call to 'g'
//  g(4);                             // error: no matching function for call to 'g'

    assert(h(i)  == "h(const int&)");
    assert(h(ci) == "h(const int&)");
    assert(h(4)  == "h(const int&)");

    assert(p(i)  == "p(int&)");
    assert(p(ci) == "p(const int&)");
    assert(p(4)  == "p(const int&)");

    assert(q(i)  == "q(int&)");
//  q(ci);                            // error: no matching function for call to 'q'
    assert(q(4)  == "q(int&&)");

    assert(r(i)  == "r(const int&)");
    assert(r(ci) == "r(const int&)");
    assert(r(4)  == "r(int&&)");

    assert(s(i)  == "s(int&)");
    assert(s(ci) == "s(const int&)");
    assert(s(4)  == "s(int&&)");
    }

    cout << "Done." << endl;
    return 0;}
