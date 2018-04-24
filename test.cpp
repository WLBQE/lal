#include <iostream>
#include <array>
#include <assert.h>
#include "include/matrix.hpp"

lal::matrix<int, 3, 3> foo() {
    return lal::matrix<int, 3, 3> {2};
}

int main()
{
    constexpr lal::matrix<int, 3, 3, true> mat_on_stack {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    std::cout << mat_on_stack <<"\n";
    constexpr lal::matrix<int, 3, 3> mat_on_stack2(mat_on_stack);
    static_assert(mat_on_stack2 == mat_on_stack);
    
    //convertion between matrices on stack and metrices on heap
    lal::matrix<int, 3, 3, false> mat(mat_on_stack);
    assert(mat == mat_on_stack);
    mat[0][0] = 10;
    assert(mat[0][0] == 10);
    assert(mat != mat_on_stack);
    mat = mat_on_stack;
    assert(mat == mat_on_stack);

    lal::matrix<int, 3, 3, true> mat_on_stack3(mat);
    mat_on_stack3[0][0] = 10;
    assert(mat_on_stack3[0][0] == 10);
    assert(mat_on_stack != mat_on_stack3);

    assert(mat_on_stack[0][0] == 1);
    static_assert(mat_on_stack[0][1] == 2);
    assert(mat_on_stack.at(0, 0) == 1);
    static_assert(mat_on_stack.at(0, 1) == 2);
   
    // iterator 
    int i = 1;
    for (auto it = mat_on_stack.begin(); it < mat_on_stack.end(); it++){
        assert(*it == i);
        i++;
    }
    static_assert(*mat_on_stack.begin() == 1);
    static_assert(*mat_on_stack.begin()+1 == 2);
    constexpr int num = *mat_on_stack.begin();
    assert(num == 1);

    i = 1;
    for (auto it = mat_on_stack.cbegin(); it < mat_on_stack.cend(); it++){
        assert(*it == i);
        i++;
    }
    static_assert(*mat_on_stack.cbegin() == 1);
    static_assert(*(mat_on_stack.cbegin() + 1) == 2);

    i = 9;
    auto it1 = mat_on_stack.rbegin();
    it1++;
    assert(*it1 == 8);
    for (auto it = mat_on_stack.rbegin(); it < mat_on_stack.rend(); it++){
        assert(*it == i);
        i--;
    }
    static_assert(*mat_on_stack.rbegin() == 9);
    static_assert(*(mat_on_stack.rbegin() + 2) == 7);
    
    i = 9;
    for (auto it = mat_on_stack.crbegin(); it < mat_on_stack.crend(); it++){
        assert(*it == i);
        i--;
    }
    static_assert(*mat_on_stack.crbegin() == 9);
    static_assert(*(mat_on_stack.crbegin() + 1) == 8);

    //column iterator
    i = 0;
    for (auto it = mat_on_stack.col_begin(); it < mat_on_stack.col_end(); it++){
        assert(*it == mat_on_stack[i%3][i/3]);
        i++;
    }
    static_assert(*mat_on_stack.col_begin() == 1);
    static_assert(*(mat_on_stack.col_begin() + 1) == 4);
    auto it_col1 = mat_on_stack.col_begin() + 8;
    std::cout << *it_col1 << "\n";
    it_col1 -= 1;
    std::cout << *it_col1 << "\n";
    
    i = 0;
    for (auto it = mat_on_stack.col_cbegin(); it < mat_on_stack.col_cend(); it++){
        assert(*it == mat_on_stack[i%3][i/3]);
        i++;
    }
    static_assert(*mat_on_stack.col_cbegin() == 1);
    static_assert(*(mat_on_stack.col_cbegin() + 1) == 4);

    i = 8;
    auto it_col = mat_on_stack.col_rbegin();
    it_col++;
    assert(*it_col == 6);
    for (auto it = mat_on_stack.col_rbegin(); it < mat_on_stack.col_rend(); it++){
        assert(*it == mat_on_stack[i%3][i/3]);
        i--;
    }
    static_assert(*mat_on_stack.col_rbegin() == 9);
    static_assert(*(mat_on_stack.col_rbegin() + 2) == 3); //could not pass now
    
    i = 8;
    for (auto it = mat_on_stack.col_crbegin(); it < mat_on_stack.col_crend(); it++){
        assert(*it == mat_on_stack[i%3][i/3]);
        i--;
    }
    static_assert(*mat_on_stack.col_crbegin() == 9);
    static_assert(*(mat_on_stack.col_crbegin() + 1) == 6);









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
    for (auto it = test.rbegin(); it != test.rend(); ++it)
        std::cout << *it << ' ';
    std::cout << "\n\n";

    lal::matrix<int, 3, 3, false> false_a {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    lal::matrix<int, 3, 3, false> false_b {{9, 8, 7, 6, 5, 4, 3, 2, 1}};
    false_b = false_a; // assignment
    auto false_c = false_a; // copy constructor
    false_a[0][0] = 100;
    false_b[1][1] = 200;
    false_c[2][2] = 300;
    std::cout << false_a << '\n';
    std::cout << false_b << '\n';
    std::cout << false_c << '\n';
    return 0;
}
