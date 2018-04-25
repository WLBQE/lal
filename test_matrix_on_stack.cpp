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
    std::cout << mat_on_stack;
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
    assert(*it_col1 == 9);
    it_col1 -= 1;
    assert(*it_col1 == 6);
    it_col1 = mat_on_stack.col_end() - 3;
    assert(*it_col1 == 3);
    
    i = 0;
    for (auto it = mat_on_stack.col_cbegin(); it < mat_on_stack.col_cend(); it++){
        assert(*it == mat_on_stack[i%3][i/3]);
        i++;
    }
    static_assert(*mat_on_stack.col_cbegin() == 1);
    static_assert(*(mat_on_stack.col_cbegin() + 1) == 4);
    auto it_col2 = mat_on_stack.col_cbegin() + 8;
    assert(*it_col2 == 9);
    it_col2 --;
    assert(*it_col2 == 6);
    it_col2 = mat_on_stack.col_end() - 3;
    assert(*it_col2 == 3);
    

    i = 8;
    auto it_col = mat_on_stack.col_rbegin();
    it_col++;
    assert(*it_col == 6);
    for (auto it = mat_on_stack.col_rbegin(); it < mat_on_stack.col_rend(); it++){
        assert(*it == mat_on_stack[i%3][i/3]);
        i--;
    }
    static_assert(*mat_on_stack.col_rbegin() == 9);
    static_assert(*(mat_on_stack.col_rbegin() + 2) == 3);
    auto it_col3 = mat_on_stack.col_rbegin() + 8;
    assert(*it_col3 == 1);
    it_col3 --;
    assert(*it_col3 == 4);
    it_col3 = mat_on_stack.col_rend() - 3;
    assert(*it_col3 == 7);
    

    i = 8;
    for (auto it = mat_on_stack.col_crbegin(); it < mat_on_stack.col_crend(); it++){
        assert(*it == mat_on_stack[i%3][i/3]);
        i--;
    }
    static_assert(*mat_on_stack.col_crbegin() == 9);
    static_assert(*(mat_on_stack.col_crbegin() + 1) == 6);
    auto it_col4 = mat_on_stack.col_crbegin() + 8;
    assert(*it_col4 == 1);
    it_col4 --;
    assert(*it_col4 == 4);
    it_col4 = mat_on_stack.col_crend() - 3;
    assert(*it_col4 == 7);
    assert(mat_on_stack3 != mat_on_stack);
    lal::matrix<int, 3, 3> mat_on_stack4(mat_on_stack);
    mat_on_stack4.swap(mat_on_stack3);
    assert(mat_on_stack3 == mat_on_stack);
    static_assert(mat_on_stack.size() == 9);
    static_assert(mat_on_stack.max_size() == 9);
    static_assert(!mat_on_stack.empty());
    
    lal::matrix<int, 3, 3, true> mat_on_stack5;
    lal::matrix<int, 3, 3, true> mat_on_stack6 {{1}};
    lal::matrix<int, 3, 3, true> mat_on_stack7 {{1,2,3}};
    lal::matrix<int, 3, 3, true> mat_on_stack8 {{0,1,2,3,4,5,6,7,8}};
    lal::matrix<int, 3, 3, true> mat_on_stack9 {{6,6,6,15,15,15,24,24,24}};
    assert(mat_on_stack5[2][2] == 0);
    assert(mat_on_stack6[2][2] == 1);
    assert(mat_on_stack7[0][1] == 2);
    assert(mat_on_stack7[2][2] == 0);
    mat_on_stack8 += mat_on_stack6;
    assert(mat_on_stack8 == mat_on_stack); 
    mat_on_stack8 -= mat_on_stack5;
    assert(mat_on_stack8 == mat_on_stack);
    mat_on_stack8 += mat_on_stack6;
    mat_on_stack8 -= mat_on_stack6; 
    assert(mat_on_stack8 == mat_on_stack);
    mat_on_stack8 *= mat_on_stack6;
    assert(mat_on_stack8 == mat_on_stack9);
    mat_on_stack7 *= 2;
    assert(mat_on_stack7[0][1] == 4);
    mat_on_stack7 /= 2;
    assert(mat_on_stack7[0][1] == 2);
    mat_on_stack5 = mat_on_stack.transpose();
    assert(mat_on_stack5[0][1] == 4);
    mat_on_stack5 = mat_on_stack5.transpose();
    assert(mat_on_stack5 == mat_on_stack);

    lal::matrix<int, 32, 32, true>::col_iterator ci;
    lal::matrix<int, 32, 32, true>::const_col_iterator cci;
    assert(ci == cci);
    assert(cci == ci);

    constexpr lal::matrix<int, 2, 2> mat_1 {0};
    constexpr lal::matrix<double, 2, 2> mat_2 {0};
    static_assert(mat_1 == mat_2);
    static_assert(!(mat_1 != mat_2));
    auto ci2 = 3332 + ci;
    assert(ci2 - ci == 3332);
    auto cci2 = cci;
    cci2 += 2;
    assert(cci2 - cci == 2);
    constexpr auto ident = lal::make_identity<3>();
    static_assert(ident[0][0] == 1);
    static_assert(ident[0][1] == 0);
    static_assert(ident[2][2] == 1);
    
    lal::square_matrix<int, 3, true> square {{1, 2, 3}};
    assert(square.size() == 9);
    assert(square[0][2] == 3);
    assert(square[2][2] == 0);
    lal::square_matrix<int, 3, false> square2 = square;
    assert(square2.size() == 9);
    assert(square2[0][2] == 3);
    assert(square2[2][2] == 0);
    square2[0][0] = 10;
    assert(square2[0][0] == 10);
    assert(square[0][0] == 1);
    constexpr lal::square_matrix<double, 3, true> sq_double {1.3};
    lal::square_matrix<int, 3, true> sq_int {5};
    static_assert(sq_double.size() == 9);
    assert(sq_int.size() == 9);
    static_assert(sq_double[2][2] == 1.3);
    assert(sq_int[2][2] == 5);
    
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

    lal::matrix<int, 3, 3, true> mat_a {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    lal::matrix<int, 3, 3, true> mat_b {{9, 8, 7, 6, 5, 4, 3, 2, 1}};
    mat_b = mat_a; // assignment
    auto mat_c = mat_a; // copy constructor
    mat_a[0][0] = 100;
    mat_b[1][1] = 200;
    mat_c[2][2] = 300;
    assert(mat_a[0][0] == 100);
    assert(mat_a[1][1] == 5);
    assert(mat_a[2][2] == 9);
    assert(mat_b[0][0] == 1);
    assert(mat_b[1][1] == 200);
    assert(mat_b[2][2] == 9);
    assert(mat_c[0][0] == 1);
    assert(mat_c[1][1] == 5);
    assert(mat_c[2][2] == 300);
    auto mat_d = std::move(mat_a); // move constructor (implicit)
    assert(mat_d[0][0] == 100);
    assert(mat_d[1][1] == 5);
    assert(mat_d[2][2] == 9);
    return 0;
}
