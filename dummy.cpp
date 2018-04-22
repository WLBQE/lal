#include <iostream>
#include <array>
#include <cassert>
#include "include/matrix.hpp"
#include "include/vector.hpp"

lal::matrix<int, 3, 3> foo() {
    return lal::matrix<int, 3, 3> {2};
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
    lal::square_matrix<int, 10, false> aa {{1, 2, 3, 4, 5, 6, 7, 8}};
    std::cout << aa << '\n';
    lal::square_matrix<int, 10, true> bb = aa;
    std::cout << bb << '\n';
    auto aaaaa = foo();
    aaaaa *= aaaaa;
    lal::matrix<int, 3, 2> bbb {2};
    bbb += bbb;
    std::cout << aaaaa << '\n';
    std::cout << bbb << '\n';
    for (auto it = bbb.col_begin(); it != bbb.col_end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
    for (auto it = bbb.col_begin(); it != bbb.col_end(); it++)
        std::cout << *it << ' ';
    std::cout << "\n\n";
    lal::square_matrix<double, 3, true> sq_double {1.3};
    lal::square_matrix<int, 3, true> sq_int {5};
    std::cout << sq_int + sq_double << '\n';
    std::cout << sq_double + sq_int << '\n';
    constexpr lal::matrix<int, 2, 3> test {{1, 2, 3, 4, 5, 6}};
    constexpr lal::matrix<int, 3, 2> test_t {{1, 4, 2, 5, 3, 6}};
    constexpr lal::matrix<int, 2, 3> add_result {{2, 4, 6, 8, 10, 12}};
    constexpr lal::matrix<int, 2, 2> mult_result {{14, 32, 32, 77}};
    constexpr lal::matrix<int, 2, 3> zeros;
    static_assert(test.transpose() == test_t);
    static_assert(test + test == add_result);
    static_assert(test - test == zeros);
    static_assert((lal::make_identity<2, int>() *= 2) == lal::square_matrix<int, 2> {{2, 0, 0, 2}});
    static_assert(test * 2 == add_result);
    static_assert(test / 1 == test);
    static_assert(test * test_t == mult_result);
    static_assert(2 * test == add_result);
    for (auto val : test)
        std::cout << val << ' ';
    std::cout << '\n';

    constexpr lal::vector<int, 5> vec1 {{1, 1, 1, 1, 1}};
    constexpr lal::vector<int, 5> vec2 {1};
    constexpr lal::matrix<int, 5, 5> cross_product {1};
    constexpr lal::matrix<int, 1, 5> mat_vec {1};
    constexpr lal::matrix<int, 5, 1> mat_vec_t {1};
    static_assert(vec1 == vec2);
    static_assert(vec1 * vec2 == 5);
    static_assert(vec1 + vec2 == 2 * vec1);
    static_assert(lal::vector_cross_product<true>(vec1, vec2) == cross_product);
    static_assert(lal::vector_cross_product(vec1, vec2) == cross_product);
    assert(lal::vector_cross_product<false>(vec1, vec2) == cross_product);
    assert(lal::vector_cross_product(vec1, vec2) == cross_product);
    static_assert(vec1.to_matrix() == mat_vec);
    static_assert(vec2.transpose() == mat_vec_t);
    assert(vec1.to_matrix<false>() == mat_vec);
    assert(vec1.transpose<false>() == mat_vec_t);
    std::cout << vec1 << '\n';

    return 0;
}