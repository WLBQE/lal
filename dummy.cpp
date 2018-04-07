#include <iostream>
#include <array>
#include "include/matrix.hpp"

int main()
{
    constexpr lal::matrix<int, 3, 3> mat {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    for (auto i = 0; i < 3; ++i)
        for (auto j = 0; j < 3; ++j)
            std::cout << mat[i][j] << ' ';
    std::cout << '\n';
    static_assert(mat[0][1] == 2);
    static_assert(mat.at(0, 1) == 2);
    lal::matrix<int, 3, 3> mat2(mat);
    if (mat2 == mat)
        std::cout << "equal!\n";
    return 0;
}