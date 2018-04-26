#include <iostream>
#include <array>
#include <assert.h>
#include "include/matrix.hpp"
#include "include/vector.hpp"
#include "include/dmatrix.hpp"

int main(){
    constexpr lal::matrix<int, 3, 3, true> mat {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    auto it1 = mat.end(1);
    auto it2 = mat.cend(1);
    std::cout << *it1 << "\n";
    std::cout << *it2 << "\n";
    return 0;
}
