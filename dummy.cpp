#include <iostream>
#include <array>
#include "include/matrix.hpp"

int main()
{
    constexpr lal::matrix<int, 3, 3> mat {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    std::cout << mat;
    static_assert(mat[0][1] == 2);
    static_assert(mat.at(0, 1) == 2);
    lal::matrix<int, 3, 3> mat2(mat);
    if (mat2 == mat)
        std::cout << "equal!\n";
    lal::matrix<int, 3, 3> mat3(222);
    //std::cin >> mat3;
    std::cout << mat3;
    mat3[0][0] = 1;
    std::cout << mat3;
    std::cin >> mat3;
    std::cout << mat3;
    return 0;
}