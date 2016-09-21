// ----------------------
// BoostSerialization.c++
// ----------------------

// http://www.boost.org/doc/libs/1_61_0/libs/serialization/doc/index.html

#include <cassert>  // assert
#include <fstream>  // ifstream, ofstream
#include <iostream> // cout, endl

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

int main () {
    using namespace std;
    using namespace boost::archive;

    cout << "BoostSerialization.c++" << endl;

    {
    ofstream ofs("BoostSerialization.bin");
    binary_oarchive boa(ofs);

    int i = 2;
    boa << i;
    }

    {
    ifstream ifs("BoostSerialization.bin");
    binary_iarchive bia(ifs);

    int j;
    bia >> j;
    assert(j == 2);
    }

    cout << "Done." << endl;
    return 0;}
