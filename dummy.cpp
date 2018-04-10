#include <iostream>
#include <array>
#include "include/matrix.hpp"

lal::matrix<int, 3, 3> foo() {
    return lal::matrix<double, 3, 3> {2.5};
}

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
    std::cout << mat3;
    mat3[0][0] = 1;
    std::cout << mat3;
    //std::cin >> mat3;
    std::cout << mat3;
    lal::matrix<int, 32, 32>::col_iterator ci;
    lal::matrix<int, 32, 32>::const_col_iterator cci;
    if (ci == cci && cci == ci)
        std::cout << "Equal again!\n";
    lal::matrix<int, 2, 2> mat_1 {0};
    lal::matrix<double, 2, 2> mat_2 {0};
    if (mat_1 == mat_2 && !(mat_1 != mat_2))
        std::cout << "hahahahaha\n";
    auto ci2 = 3332 + ci;
    std::cout << ci2 - ci << '\n';
    auto cci2 = cci;
    cci2 += 2;
    cci2 + 5;
    std::cout << cci2 - cci << '\n';
    constexpr auto ident = lal::make_identity<3>();
    static_assert(ident[0][0] == 1);
    static_assert(ident[0][1] == 0);
    lal::matrix<int, 10, 10, false> aa {{1, 2, 3, 4, 5, 6, 7, 8}};
    std::cout << aa << '\n';
    lal::matrix<int, 10, 10, true> bb {aa};
    std::cout << bb << '\n';
    auto aaaaa = foo();
    aaaaa *= aaaaa;
    lal::matrix<int, 3, 2> bbb {2};
    bbb += bbb;
    std::cout << aaaaa << '\n';
    std::cout << bbb << '\n';
    return 0;
}