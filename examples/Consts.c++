// ----------
// Consts.c++
// ----------

// http://www.cplusplus.com/doc/tutorial/constants/

#include <cassert>  // assert
#include <iostream> // cout, endl

int main () {
    using namespace std;
    cout << "Consts.c++" << endl;

    {
    int i = 2;
    ++i;
    assert(i == 3);
    }

    {
//  const int ci;     // error: uninitialized const 'ci'
    const int ci = 4;
//  ++ci;             // error: increment of read-only variable 'ci'
    assert(ci == 4);
    }

    // read/write, many-location pointer
    // mutable int, mutable pointer
    {
          int  i  = 2;
    const int  ci = 3;
          int* p;
    p = &i;
    ++*p;
    assert(i == 3);
//  p = &ci;        // error: invalid conversion from 'const int*' to 'int*'
    assert(ci);
    }

    // read-only, many-location pointer
    // immutable int, mutable pointer
    {
          int  i  = 2;
    const int  ci = 3;
    const int* pc;
    pc = &ci;
//  ++*pc;                         // error: increment of read-only location
//  int* p = pc;                   // error: invalid conversion from 'const int*' to 'int*'
    int* p = const_cast<int*>(pc);
    assert(p == pc);
//  ++*p;                          // undefined
    pc = &i;                       // ?
    p = const_cast<int*>(pc);
    ++*p;
    assert(i == 3);
    }

    // read/write, one-location pointer
    // mutable int, immutable pointer
    {
          int        i  = 2;
    const int        ci = 3;
//        int* const cp;       // error: uninitialized const 'cp'
//        int* const cp = &ci; // error: invalid conversion from 'const int*' to 'int*'
          int* const cp = &i;
//  cp = &i;                   // error: assignment of read-only variable 'cp'
    ++*cp;
    assert(i == 3);
    assert(ci);
    }

    // read-only, one-location pointer
    // immutable int, immutable pointer
    {
          int        i   = 2;
    const int        ci  = 3;
    const int* const cpc = &ci;
    const int* const cqc = &i;
//  cqc = &ci;                  // error: assignment of read-only variable 'cqc'
//  ++*cqc;                     // error: increment of read-only location
    assert(cpc);
    assert(cqc);
    }

    // read/write reference
    // mutable int
    {
          int  i  = 2;
    const int  ci = 3;
//        int& r;      // error: 'r' declared as reference but not initialized
//        int& r = ci; // error: invalid initialization of reference of type 'int&' from expression of type 'const int'
          int& r = i;
    ++r;
    assert(i == 3);
    assert(ci);
    }

    // read-only reference
    // immutable int
    {
          int  i  = 2;
    const int  ci = 3;
    const int& rc = ci;
    const int& sc = i;
//  ++sc;               // error: increment of read-only reference 'sc'
    assert(rc);
    assert(sc);
    }

    cout << "Done." << endl;
    return 0;}
