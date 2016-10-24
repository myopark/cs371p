// --------
// Move.c++
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl

using namespace std;

template <typename T>
struct A {
    explicit A(int) {
        cout << "A(int) ";}

    A (const A& rhs) {
        cout << "A(const A&) ";}

    A (A&&) {
        cout << "A(A&&) ";}

    A& operator = (const A&) {
        cout << "=(const A&) ";
        return *this;}

    A& operator = (A&&) {
        cout << "=(A&&) ";
        return *this;}

    ~A() {
        cout << "~A() ";}};

#include "Move.h"

template <typename T>
struct B {
    A<T> _x;

    explicit B (int s) :
            _x (s) {
        cout << "B(int) ";}

    B (const B& rhs) :
            _x (rhs._x) {
        cout << "B(const B&) ";}

    B& operator = (const B& rhs) {
        if (this == &rhs)
            return *this;
        _x = rhs._x;
        cout << "=(const B&) ";
        return *this;}

    ~B() {
        cout << "~B() ";}};

B<int> f () {
    B<int> z(4);
    return z;}

C<int> g () {
    C<int> z(4);
    return z;}

int main() {
    {
    cout << "ctor: ";
    B<int> x(2);          // ctor: A(int) B(int)
    cout << endl;

    cout << "ctor: ";
    B<int> y(3);          // ctor: A(int) B(int)
    cout << endl;

    cout << "copy: ";
    x = y;                // copy: =(const A&) =(const B&)
    cout << endl;

    cout << "copy: ";
    x = f();              // copy: A(int) B(int) =(const A&) =(const B&) ~B() ~A()
    cout << endl;

    cout << "dtor: ";
    }                     // dtor: ~B() ~A()
    cout << endl << endl;



    {
    cout << "ctor: ";
    C<int> x(2);          // ctor: A(int) C(int)
    cout << endl;

    cout << "ctor: ";
    C<int> y(3);          // ctor: A(int) C(int)
    cout << endl;

    cout << "copy: ";
    x = y;                // copy: =(const A&) =(const C&)
    cout << endl;

    cout << "move: ";
    x = g();              // move: A(int) C(int) A(A&&) C(C&&) ~C() ~A()
    cout << endl;

    cout << "dtor: ";
    }                     // dtor: ~C() ~A()
    cout << endl;

    return 0;}

/*
ctor: A(int) B(int)
ctor: A(int) B(int)
copy: =(const A&) =(const B&)
copy: A(int) B(int) =(const A&) =(const B&) ~B() ~A()
dtor: ~B() ~A() ~B() ~A()

ctor: A(int) C(int)
ctor: A(int) C(int)
copy: =(const A&) =(const C&)
move: A(int) C(int) =(A&&) =(C&&) ~C() ~A()
dtor: ~C() ~A() ~C() ~A()
*/
