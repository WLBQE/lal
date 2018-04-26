#include <iostream>
#include <array>
#include <assert.h>
#include "include/dmatrix.hpp"

int main()
{
    lal::dynamic_matrix<double> dmat1(3, 3, 1);
    assert(dmat1.at(0, 0) == 1);
    assert(dmat1.at(2, 2) == 1);

    auto it = dmat1.col_end() - 3; //pass
    std::cout << *it << "\n";

    auto it2 = dmat1.col_begin() + 8;
    it2 = dmat1.col_end() - 3; //fail
    std::cout << *it << "\n";
    return 0;
}
