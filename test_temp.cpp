#include <iostream>
#include <array>
#include <assert.h>
#include "include/matrix.hpp"

lal::matrix<int, 3, 3> foo() {
    return lal::matrix<int, 3, 3> {2};
}

int main()
{
    lal::matrix<int, 3, 3, false> mat1 {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    lal::matrix<int, 3, 3, false> mat2 {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    mat1 += mat2;
    return 0;
}
