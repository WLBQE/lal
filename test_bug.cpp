#include <iostream>
#include <array>
#include <assert.h>
#include "include/dmatrix.hpp"

int main()
{
    lal::dynamic_matrix<double> dmat1(3, 3, 1);
    assert(dmat1.at(0, 0) == 1);
    assert(dmat1.at(2, 2) == 1);
    lal::dynamic_matrix<int> dmat2(3, 3, 1);
    assert(dmat2.at(0, 0) == 1);
    assert(dmat2.at(2, 2) == 1);
    std::cout << dmat2 << "\n";
    assert(dmat2 == dmat1);
    return 0;
}
