#include <iostream>
#include <cassert>
#include "include/matrix.hpp"
#include "include/vector.hpp"
#include "include/dmatrix.hpp"

void test_matrix_on_stack()
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
    static_assert(*mat_on_stack.begin() + 1 == 2);
    constexpr int num = *mat_on_stack.begin();
    assert(num == 1);
    auto it0 = mat_on_stack.begin(1);
    assert(*it0 == 4);
    it0 += 2;
    assert(*it0 == 6);
    it0--;
    assert(*it0 == 5);
    it0 -= 2;
    assert(*it0 == 3);
    it0++;
    assert(*it0 == 4);
    it0 = mat_on_stack.end(1);
    assert(*it0 == 7);
    
    i = 1;
    for (auto it = mat_on_stack.cbegin(); it < mat_on_stack.cend(); it++){
        assert(*it == i);
        i++;
    }
    static_assert(*mat_on_stack.cbegin() == 1);
    static_assert(*(mat_on_stack.cbegin() + 1) == 2);

    auto it1 = mat_on_stack.cbegin(1);
    assert(*it1 == 4);
    it1 += 2;
    assert(*it1 == 6);
    it1--;
    assert(*it1 == 5);
    it1 -= 2;
    assert(*it1 == 3);
    it1++;
    assert(*it1 == 4);
    it1 = mat_on_stack.cend(1);
    assert(*it1 == 7);
 
    i = 9;
    for (auto it = mat_on_stack.rbegin(); it < mat_on_stack.rend(); it++){
        assert(*it == i);
        i--;
    }
    static_assert(*mat_on_stack.rbegin() == 9);
    static_assert(*(mat_on_stack.rbegin() + 2) == 7);
    auto it2 = mat_on_stack.rbegin(1);
    assert(*it2 == 6);
    it2 += 2;
    assert(*it2 == 4);
    it2--;
    assert(*it2 == 5);
    it2 -= 2;
    assert(*it2 == 7);
    it2++;
    assert(*it2 == 6);
    it2 = mat_on_stack.rend(1);
    assert(*it2 == 3);

    i = 9;
    for (auto it = mat_on_stack.crbegin(); it < mat_on_stack.crend(); it++){
        assert(*it == i);
        i--;
    }
    static_assert(*mat_on_stack.crbegin() == 9);
    static_assert(*(mat_on_stack.crbegin() + 1) == 8);
    
    auto it3 = mat_on_stack.crbegin(1);
    assert(*it3 == 6);
    it3 += 2;
    assert(*it3 == 4);
    it3--;
    assert(*it3 == 5);
    it3 -= 2;
    assert(*it3 == 7);
    it3++;
    assert(*it3 == 6);
    it3 = mat_on_stack.rend(1);
    assert(*it3 == 3);


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
    it_col1 = mat_on_stack.col_begin(1);
    assert(*it_col1 == 2);
    it_col1 += 2;
    assert(*it_col1 == 8);
    it_col1--;
    assert(*it_col1 == 5);
    it_col1 -= 2;
    assert(*it_col1 == 7);
    it_col1++;
    assert(*it_col1 == 2);
    it_col1 = mat_on_stack.col_end(1);
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
    it_col2 = mat_on_stack.col_cend() - 3;
    assert(*it_col2 == 3);
    it_col2 = mat_on_stack.col_cbegin(1);
    assert(*it_col2 == 2);
    it_col2 += 2;
    assert(*it_col2 == 8);
    it_col2--;
    assert(*it_col2 == 5);
    it_col2 -= 2;
    assert(*it_col2 == 7);
    it_col2++;
    assert(*it_col2 == 2);
    it_col2 = mat_on_stack.col_cend(1);
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
    it_col3 = mat_on_stack.col_rbegin(1);
    assert(*it_col3 == 8);
    it_col3 += 2;
    assert(*it_col3 == 2);
    it_col3--;
    assert(*it_col3 == 5);
    it_col3 -= 2;
    assert(*it_col3 == 3);
    it_col3++;
    assert(*it_col3 == 8);
    it_col3 = mat_on_stack.col_rend(1);
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
    it_col4 = mat_on_stack.col_crbegin(1);
    assert(*it_col4 == 8);
    it_col4 += 2;
    assert(*it_col4 == 2);
    it_col4--;
    assert(*it_col4 == 5);
    it_col4 -= 2;
    assert(*it_col4 == 3);
    it_col4++;
    assert(*it_col4 == 8);
    it_col4 = mat_on_stack.col_crend(1);
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
}

void test_matrix_on_heap()
{
    lal::matrix<int, 3, 3, false> mat_on_heap {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    std::cout << mat_on_heap;
    lal::matrix<int, 3, 3> mat_on_heap2(mat_on_heap);
    assert(mat_on_heap2 == mat_on_heap);
    
    //convertion between matrices on heap and metrices on heap
    lal::matrix<int, 3, 3, true> mat(mat_on_heap);
    assert(mat == mat_on_heap);
    mat[0][0] = 10;
    assert(mat[0][0] == 10);
    assert(mat != mat_on_heap);
    mat = mat_on_heap;
    assert(mat == mat_on_heap);

    lal::matrix<int, 3, 3, false> mat_on_heap3(mat);
    mat_on_heap3[0][0] = 10;
    assert(mat_on_heap3[0][0] == 10);
    assert(mat_on_heap != mat_on_heap3);

    assert(mat_on_heap[0][0] == 1);
    assert(mat_on_heap[0][1] == 2);
    assert(mat_on_heap.at(0, 0) == 1);
    assert(mat_on_heap.at(0, 1) == 2);
   
    // iterator 
    int i = 1;
    for (auto it = mat_on_heap.begin(); it < mat_on_heap.end(); it++){
        assert(*it == i);
        i++;
    }
    assert(*mat_on_heap.begin() == 1);
    assert(*mat_on_heap.begin()+1 == 2);
    int num = *mat_on_heap.begin();
    assert(num == 1);
    auto it0 = mat_on_heap.begin(1);
    assert(*it0 == 4);
    it0 += 2;
    assert(*it0 == 6);
    it0--;
    assert(*it0 == 5);
    it0 -= 2;
    assert(*it0 == 3);
    it0++;
    assert(*it0 == 4);
    it0 = mat_on_heap.end(1);
    assert(*it0 == 7);
    

    i = 1;
    for (auto it = mat_on_heap.cbegin(); it < mat_on_heap.cend(); it++){
        assert(*it == i);
        i++;
    }
    assert(*mat_on_heap.cbegin() == 1);
    assert(*(mat_on_heap.cbegin() + 1) == 2);
    auto it1 = mat_on_heap.cbegin(1);
    assert(*it1 == 4);
    it1 += 2;
    assert(*it1 == 6);
    it1--;
    assert(*it1 == 5);
    it1 -= 2;
    assert(*it1 == 3);
    it1++;
    assert(*it1 == 4);
    it1 = mat_on_heap.cend(1);
    assert(*it1 == 7);
 

    i = 9;
    for (auto it = mat_on_heap.rbegin(); it < mat_on_heap.rend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*mat_on_heap.rbegin() == 9);
    assert(*(mat_on_heap.rbegin() + 2) == 7);
    auto it2 = mat_on_heap.rbegin(1);
    assert(*it2 == 6);
    it2 += 2;
    assert(*it2 == 4);
    it2--;
    assert(*it2 == 5);
    it2 -= 2;
    assert(*it2 == 7);
    it2++;
    assert(*it2 == 6);
    it2 = mat_on_heap.rend(1);
    assert(*it2 == 3);


    i = 9;
    for (auto it = mat_on_heap.crbegin(); it < mat_on_heap.crend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*mat_on_heap.crbegin() == 9);
    assert(*(mat_on_heap.crbegin() + 1) == 8);
    auto it3 = mat_on_heap.crbegin(1);
    assert(*it3 == 6);
    it3 += 2;
    assert(*it3 == 4);
    it3--;
    assert(*it3 == 5);
    it3 -= 2;
    assert(*it3 == 7);
    it3++;
    assert(*it3 == 6);
    it3 = mat_on_heap.rend(1);
    assert(*it3 == 3);


    //column iterator
    i = 0;
    for (auto it = mat_on_heap.col_begin(); it < mat_on_heap.col_end(); it++){
        assert(*it == mat_on_heap[i%3][i/3]);
        i++;
    }
    assert(*mat_on_heap.col_begin() == 1);
    assert(*(mat_on_heap.col_begin() + 1) == 4);
    auto it_col1 = mat_on_heap.col_begin() + 8;
    assert(*it_col1 == 9);
    it_col1 -= 1;
    assert(*it_col1 == 6);
    it_col1 = mat_on_heap.col_end() - 3;
    assert(*it_col1 == 3);
    it_col1 = mat_on_heap.col_begin(1);
    assert(*it_col1 == 2);
    it_col1 += 2;
    assert(*it_col1 == 8);
    it_col1--;
    assert(*it_col1 == 5);
    it_col1 -= 2;
    assert(*it_col1 == 7);
    it_col1++;
    assert(*it_col1 == 2);
    it_col1 = mat_on_heap.col_end(1);
    assert(*it_col1 == 3);
    

    i = 0;
    for (auto it = mat_on_heap.col_cbegin(); it < mat_on_heap.col_cend(); it++){
        assert(*it == mat_on_heap[i%3][i/3]);
        i++;
    }
    assert(*mat_on_heap.col_cbegin() == 1);
    assert(*(mat_on_heap.col_cbegin() + 1) == 4);
    auto it_col2 = mat_on_heap.col_cbegin() + 8;
    assert(*it_col2 == 9);
    it_col2 --;
    assert(*it_col2 == 6);
    it_col2 = mat_on_heap.col_cend() - 3;
    assert(*it_col2 == 3);
    it_col2 = mat_on_heap.col_cbegin(1);
    assert(*it_col2 == 2);
    it_col2 += 2;
    assert(*it_col2 == 8);
    it_col2--;
    assert(*it_col2 == 5);
    it_col2 -= 2;
    assert(*it_col2 == 7);
    it_col2++;
    assert(*it_col2 == 2);
    it_col2 = mat_on_heap.col_cend(1);
    assert(*it_col2 == 3);
    


    i = 8;
    auto it_col = mat_on_heap.col_rbegin();
    it_col++;
    assert(*it_col == 6);
    for (auto it = mat_on_heap.col_rbegin(); it < mat_on_heap.col_rend(); it++){
        assert(*it == mat_on_heap[i%3][i/3]);
        i--;
    }
    assert(*mat_on_heap.col_rbegin() == 9);
    assert(*(mat_on_heap.col_rbegin() + 2) == 3);
    auto it_col3 = mat_on_heap.col_rbegin() + 8;
    assert(*it_col3 == 1);
    it_col3 --;
    assert(*it_col3 == 4);
    it_col3 = mat_on_heap.col_rend() - 3;
    assert(*it_col3 == 7);
    it_col3 = mat_on_heap.col_rbegin(1);
    assert(*it_col3 == 8);
    it_col3 += 2;
    assert(*it_col3 == 2);
    it_col3--;
    assert(*it_col3 == 5);
    it_col3 -= 2;
    assert(*it_col3 == 3);
    it_col3++;
    assert(*it_col3 == 8);
    it_col3 = mat_on_heap.col_rend(1);
    assert(*it_col3 == 7);
    


    i = 8;
    for (auto it = mat_on_heap.col_crbegin(); it < mat_on_heap.col_crend(); it++){
        assert(*it == mat_on_heap[i%3][i/3]);
        i--;
    }
    assert(*mat_on_heap.col_crbegin() == 9);
    assert(*(mat_on_heap.col_crbegin() + 1) == 6);
    auto it_col4 = mat_on_heap.col_crbegin() + 8;
    assert(*it_col4 == 1);
    it_col4 --;
    assert(*it_col4 == 4);
    it_col4 = mat_on_heap.col_crend() - 3;
    assert(*it_col4 == 7);
    it_col4 = mat_on_heap.col_crbegin(1);
    assert(*it_col4 == 8);
    it_col4 += 2;
    assert(*it_col4 == 2);
    it_col4--;
    assert(*it_col4 == 5);
    it_col4 -= 2;
    assert(*it_col4 == 3);
    it_col4++;
    assert(*it_col4 == 8);
    it_col4 = mat_on_heap.col_crend(1);
    assert(*it_col4 == 7);
    

    assert(mat_on_heap3 != mat_on_heap);
    lal::matrix<int, 3, 3, false> mat_on_heap4(mat_on_heap);
    mat_on_heap4.swap(mat_on_heap3);
    assert(mat_on_heap3 == mat_on_heap);
    assert(mat_on_heap.size() == 9);
    assert(mat_on_heap.max_size() == 9);
    assert(!mat_on_heap.empty());
    
    lal::matrix<int, 3, 3, false> mat_on_heap5;
    lal::matrix<int, 3, 3, false> mat_on_heap6 {{1}};
    lal::matrix<int, 3, 3, false> mat_on_heap7 {{1,2,3}};
    lal::matrix<int, 3, 3, false> mat_on_heap8 {{0,1,2,3,4,5,6,7,8}};
    lal::matrix<int, 3, 3, false> mat_on_heap9 {{6,6,6,15,15,15,24,24,24}};
    assert(mat_on_heap5[2][2] == 0);
    assert(mat_on_heap6[2][2] == 1);
    assert(mat_on_heap7[0][1] == 2);
    assert(mat_on_heap7[2][2] == 0);
    mat_on_heap8 += mat_on_heap6;
    assert(mat_on_heap8 == mat_on_heap); 
    mat_on_heap8 -= mat_on_heap5;
    assert(mat_on_heap8 == mat_on_heap);
    mat_on_heap8 += mat_on_heap6;
    mat_on_heap8 -= mat_on_heap6; 
    assert(mat_on_heap8 == mat_on_heap);
    mat_on_heap8 *= mat_on_heap6;
    assert(mat_on_heap8 == mat_on_heap9);
    mat_on_heap7 *= 2;
    assert(mat_on_heap7[0][1] == 4);
    mat_on_heap7 /= 2;
    assert(mat_on_heap7[0][1] == 2);
    mat_on_heap5 = mat_on_heap.transpose();
    assert(mat_on_heap5[0][1] == 4);
    mat_on_heap5 = mat_on_heap5.transpose();
    assert(mat_on_heap5 == mat_on_heap);

    lal::matrix<int, 32, 32, false>::col_iterator ci;
    lal::matrix<int, 32, 32, false>::const_col_iterator cci;
    assert(ci == cci);
    assert(cci == ci);

    lal::matrix<int, 2, 2> mat_1 {0};
    lal::matrix<double, 2, 2> mat_2 {0};
    assert(mat_1 == mat_2);
    assert(!(mat_1 != mat_2));
    auto ci2 = 3332 + ci;
    assert(ci2 - ci == 3332);
    auto cci2 = cci;
    cci2 += 2;
    assert(cci2 - cci == 2);
    auto ident = lal::make_identity<3>();
    assert(ident[0][0] == 1);
    assert(ident[0][1] == 0);
    assert(ident[2][2] == 1);
    
    lal::square_matrix<int, 3, false> square {{1, 2, 3}};
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
    lal::square_matrix<double, 3, false> sq_double {1.3};
    lal::square_matrix<int, 3, false> sq_int {5};
    assert(sq_double.size() == 9);
    assert(sq_int.size() == 9);
    assert(sq_double[2][2] == 1.3);
    assert(sq_int[2][2] == 5);
    
    lal::matrix<int, 2, 3, false> test {{1, 2, 3, 4, 5, 6}};
    lal::matrix<int, 3, 2, false> test_t {{1, 4, 2, 5, 3, 6}};
    lal::matrix<int, 2, 3, false> add_result {{2, 4, 6, 8, 10, 12}};
    lal::matrix<int, 2, 2, false> mult_result {{14, 32, 32, 77}};
    lal::matrix<int, 2, 3, false> zeros;
    assert(test.transpose() == test_t);
    assert(test + test == add_result);
    assert(test - test == zeros);
    assert(test * 2 == add_result);
    assert(test / 1 == test);
    assert(test * test_t == mult_result);
    assert(2 * test == add_result);

    lal::matrix<int, 3, 3, false> mat_a {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    lal::matrix<int, 3, 3, false> mat_b {{9, 8, 7, 6, 5, 4, 3, 2, 1}};
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
}

void test_vector(){
    constexpr lal::vector<int, 5> vec;
    static_assert(vec[0] == 0);
    static_assert(vec[4] == 0);
    constexpr lal::vector<double, 5> vec1 {1.0} ;
    static_assert(vec1.at(0) == 1);
    static_assert(vec1.at(4) == 1);
    constexpr lal::vector<int, 5> vec2 {{1,2}};
    static_assert(vec2[1] == 2);
    static_assert(vec2[4] == 0);
    constexpr lal::vector<int, 5> vec3 {{1,2,3,4,5}};
    std::cout << vec3 <<"\n";
    static_assert(vec3.at(0) == 1);
    static_assert(vec3.at(3) == 4);
    constexpr lal::matrix<int, 1, 3, true> mat {{1}};
    constexpr lal::vector<int, 3> vec4 (mat);
    static_assert(vec4[0] == 1);
    static_assert(vec4[2] == 1);
    lal::matrix<int, 1, 5, false> mat1 {{1}};
    lal::vector<int, 5> vec5 (mat1);
    assert(vec5[0] == 1);
    assert(vec5[2] == 1);
    assert(vec1 == vec5);
    assert(vec3 != vec5);
    static_assert(vec4.size() == 3);
    static_assert(vec4.max_size() == 3);
    static_assert(!vec4.empty());
    static_assert(vec5.size() == 5);
    static_assert(vec5.max_size() == 5);
    static_assert(!vec5.empty());
    
    int i = 1;
    for (auto it = vec3.begin(); it < vec3.end(); it++){
        assert(*it == i);
        i++;
    }
    static_assert(*(vec3.begin() + 3) == 4);
    static_assert(*(vec3.end() - 2) == 4);
    auto it1 = vec3.begin();
    it1 += 3;
    assert(*it1 == 4);
    it1--;
    assert(*it1 == 3);
    it1 = vec3.end();
    it1 -= 3;
    assert(*it1 == 3);
    it1++;
    assert(*it1 == 4);

    i = 1;
    for (auto it = vec3.cbegin(); it < vec3.cend(); it++){
        assert(*it == i);
        i++;
    }
    static_assert(*(vec3.cbegin() + 3) == 4);
    static_assert(*(vec3.cend() - 2) == 4);
    auto it2 = vec3.cbegin();
    it2 += 3;
    assert(*it2 == 4);
    it2--;
    assert(*it2 == 3);
    it2 = vec3.cend();
    it2 -= 3;
    assert(*it2 == 3);
    it2++;
    assert(*it2 == 4);
    

    i = 5;
    for (auto it = vec3.rbegin(); it < vec3.rend(); it++){
        assert(*it == i);
        i--;
    }
    static_assert(*(vec3.rbegin() + 3) == 2);
    static_assert(*(vec3.rend() - 2) == 2);
    auto it3 = vec3.rbegin();
    it3 += 3;
    assert(*it3 == 2);
    it3--;
    assert(*it3 == 3);
    it3 = vec3.rend();
    it3 -= 3;
    assert(*it3 == 3);
    it3++;
    assert(*it3 == 2);
    
    i = 5;
    for (auto it = vec3.crbegin(); it < vec3.crend(); it++){
        assert(*it == i);
        i--;
    }
    static_assert(*(vec3.crbegin() + 3) == 2);
    static_assert(*(vec3.crend() - 2) == 2);
    auto it4 = vec3.crbegin();
    it4 += 3;
    assert(*it4 == 2);
    it4--;
    assert(*it4 == 3);
    it4 = vec3.crend();
    it4 -= 3;
    assert(*it4 == 3);
    it4++;
    assert(*it4 == 2);

    lal::vector<int, 5> vec6 {{2,3,4,5,6}};
    lal::vector<int, 5> vec7 (vec6);
    vec6 -= vec5;
    assert(vec6 == vec3);
    assert(vec7[0] == 2);
    vec6 += vec5;
    assert(vec6 == vec7);
    vec6 *= 2;
    lal::vector<int, 5> vec8 {{4,6,8,10,12}};
    assert(vec6 == vec8);
    vec6 /= 2;
    assert(vec6 == vec7);
    
    assert(mat1 == vec5.to_matrix());
    auto mat2 = vec6.transpose();
    constexpr lal::matrix<int, 5, 1, true> mat3 {{2,3,4,5,6}};
    assert(mat2 == mat3);

    auto vec9 = vec6 + vec7;
    assert(vec9 == vec8);
    vec9 = vec6 - vec7;
    assert(vec9 == vec);
    vec9 = 2 * vec6;
    assert(vec9 == vec8);
    vec9 = vec8 / 2;
    assert(vec9 == vec7);
    assert(vec6 * vec7 == 90);
    auto mat4 = vector_cross_product(vec3, vec7);
    assert(mat4[4][1] == 15);
    assert(mat4[3][4] == 24);

    lal::vector<int, 5> vec12 {{1,2,3,4,5}};
    lal::vector<int, 5> vec10;
    vec10 = vec12;
    vec12[0] = 10;
    assert(vec12[0] == 10);
    assert(vec10[0] == 1);
    auto vec11 = vec10;
    vec10[0] = 100;
    assert(vec12[0] == 10);
    assert(vec10[0] == 100);
    assert(vec11[0] == 1);
    assert(vec11.size() == 5);

    constexpr lal::matrix<int, 5, 5, true> mat5 {{1}};
    constexpr lal::vector<int, 1> vec13 {88};
    constexpr lal::vector<int, 5> vec14 {24};
    assert(vec12 * mat3 == vec13);
    assert(mat5 * vec12 == vec14);
}

lal::dynamic_matrix<int> foo() {
    return lal::dynamic_matrix<int> (3, 3);
}

void test_dynamic_matrix()
{
    lal::dynamic_matrix<int> dmat(3, 3);
    std::cout << dmat;
    assert(dmat[0][0] == 0);
    assert(dmat[2][2] == 0);
    lal::dynamic_matrix<double> dmat1(3, 3, 1);
    assert(dmat1.at(0, 0) == 1);
    assert(dmat1.at(2, 2) == 1);
    lal::dynamic_matrix<int> dmat2(3, 3, 1);
    assert(dmat2.at(0, 0) == 1);
    assert(dmat2.at(2, 2) == 1);
    assert(dmat2 == dmat1);
    assert(!(dmat1 != dmat2));
    
    dmat2 = foo();
    assert(dmat2[0][0] == 0);
    assert(dmat2[2][2] == 0);
    assert(dmat2.rows() == 3);
    assert(dmat2.cols() == 3);
    assert(dmat == dmat2);
    
    lal::dynamic_matrix<int> dmat3(dmat);
    assert(dmat == dmat3);
    dmat[0][0] = 10;
    assert(dmat[0][0] == 10);
    assert(dmat3 != dmat);
    dmat3 = dmat;
    assert(dmat3 == dmat);
    
    lal::matrix<int, 3, 3> mat {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    lal::dynamic_matrix<int> dmat4(mat);
    dmat = dmat4;
    assert(dmat[0][0] == 1);
    assert(dmat[2][2] == 9);
    
    // iterator 
    int i = 1;
    for (auto it = dmat.begin(); it < dmat.end(); it++){
        assert(*it == i);
        i++;
    }
    assert(*dmat.begin() == 1);
    assert(*dmat.begin()+1 == 2);
    int num = *dmat.begin();
    assert(num == 1);
    auto it1 = dmat.begin() + 8;
    assert(*it1 == 9);
    it1 -= 5;
    assert(*it1 == 4);
    it1++;
    assert(*it1 == 5);
    it1 += 2;
    assert(*it1 == 7);
    it1--;
    assert(*it1 == 6);
    it1 = dmat.end() - 3;
    assert(*it1 == 7);
    it1 = dmat.begin(1);
    assert(*it1 == 4);
    it1 = dmat.end(1);
    assert(*it1 == 7);


    i = 1;
    for (auto it = dmat.cbegin(); it < dmat.cend(); it++){
        assert(*it == i);
        i++;
    }
    assert(*dmat.cbegin() == 1);
    assert(*(dmat.cbegin() + 1) == 2);
    auto it2 = dmat.cbegin() + 8;
    assert(*it2 == 9);
    it2 -= 5;
    assert(*it2 == 4);
    it2++;
    assert(*it2 == 5);
    it2 += 2;
    assert(*it2 == 7);
    it2--;
    assert(*it2 == 6);
    it2 = dmat.cend() - 3;
    assert(*it2 == 7);
    it2 = dmat.cbegin(1);
    assert(*it2 == 4);
    it2 = dmat.cend(1);
    assert(*it2 == 7);


    i = 9;
    for (auto it = dmat.rbegin(); it < dmat.rend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*dmat.rbegin() == 9);
    assert(*(dmat.rbegin() + 2) == 7);
    auto it3 = dmat.rbegin() + 8;
    assert(*it3 == 1);
    it3 -= 5;
    assert(*it3 == 6);
    it3++;
    assert(*it3 == 5);
    it3 += 2;
    assert(*it3 == 3);
    it3--;
    assert(*it3 == 4);
    it3 = dmat.rend() - 3;
    assert(*it3 == 3);
    it3 = dmat.rbegin(1);
    assert(*it3 == 6);
    it3 = dmat.rend(1);
    assert(*it3 == 3);


    i = 9;
    for (auto it = dmat.crbegin(); it < dmat.crend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*dmat.crbegin() == 9);
    assert(*(dmat.crbegin() + 1) == 8);
    auto it4 = dmat.crbegin() + 8;
    assert(*it4 == 1);
    it4 -= 5;
    assert(*it4 == 6);
    it4++;
    assert(*it4 == 5);
    it4 += 2;
    assert(*it4 == 3);
    it4--;
    assert(*it4 == 4);
    it4 = dmat.crend() - 3;
    assert(*it4 == 3);
    it4 = dmat.crbegin(1);
    assert(*it4 == 6);
    it4 = dmat.crend(1);
    assert(*it4 == 3);



    //column iterator
    i = 0;
    for (auto it = dmat.col_begin(); it < dmat.col_end(); it++){
        assert(*it == dmat[i%3][i/3]);
        i++;
    }
    assert(*dmat.col_begin() == 1);
    assert(*(dmat.col_begin() + 1) == 4);
    auto it_col1 = dmat.col_begin() + 8;
    assert(*it_col1 == 9);
    it_col1 -= 5;
    assert(*it_col1 == 2);
    it_col1++;
    assert(*it_col1 == 5);
    it_col1 += 2;
    assert(*it_col1 == 3);
    it_col1--;
    assert(*it_col1 == 8);
    it_col1 = dmat.col_end() - 3;
    assert(*it_col1 == 3);
    it_col1 = dmat.col_begin(1);
    assert(*it_col1 == 2);
    it_col1 = dmat.col_end(1);
    assert(*it_col1 == 3);

    i = 0;
    for (auto it = dmat.col_cbegin(); it < dmat.col_cend(); it++){
        assert(*it == dmat[i%3][i/3]);
        i++;
    }
    assert(*dmat.col_cbegin() == 1);
    assert(*(dmat.col_cbegin() + 1) == 4);
    auto it_col2 = dmat.col_cbegin() + 8;
    assert(*it_col2 == 9);
    it_col2 --;
    assert(*it_col2 == 6);
    it_col2 = dmat.col_cend() - 3;
    assert(*it_col2 == 3);
    it_col2 = dmat.col_cbegin(1);
    assert(*it_col2 == 2);
    it_col2 = dmat.col_cend(1);
    assert(*it_col2 == 3);



    i = 8;
    auto it_col = dmat.col_rbegin();
    it_col++;
    assert(*it_col == 6);
    for (auto it = dmat.col_rbegin(); it < dmat.col_rend(); it++){
        assert(*it == dmat[i%3][i/3]);
        i--;
    }
    assert(*dmat.col_rbegin() == 9);
    assert(*(dmat.col_rbegin() + 2) == 3);
    auto it_col3 = dmat.col_rbegin() + 8;
    assert(*it_col3 == 1);
    it_col3 --;
    assert(*it_col3 == 4);
    it_col3 = dmat.col_rend() - 3;
    assert(*it_col3 == 7);
    it_col3 = dmat.col_rbegin(1);
    assert(*it_col3 == 8);
    it_col3 = dmat.col_rend(1);
    assert(*it_col3 == 7);



    i = 8;
    for (auto it = dmat.col_crbegin(); it < dmat.col_crend(); it++){
        assert(*it == dmat[i%3][i/3]);
        i--;
    }
    assert(*dmat.col_crbegin() == 9);
    assert(*(dmat.col_crbegin() + 1) == 6);
    auto it_col4 = dmat.col_crbegin() + 8;
    assert(*it_col4 == 1);
    it_col4 --;
    assert(*it_col4 == 4);
    it_col4 = dmat.col_crend() - 3;
    assert(*it_col4 == 7);
    assert(dmat3 != dmat);
    it_col4 = dmat.col_crbegin(1);
    assert(*it_col4 == 8);
    it_col4 = dmat.col_crend(1);
    assert(*it_col4 == 7);

    dmat4.swap(dmat3);
    assert(dmat3 == dmat);
    assert(dmat.size() == 9);
    assert(dmat.max_size() >= dmat.size());
    assert(!dmat.empty());
   
    dmat3.insert_row(0, std::vector<int>(3,0));
    assert(dmat3.size() == 12);
    assert(dmat3[0][0] == 0);
    assert(dmat3[0][2] == 0);
    assert(dmat3[1][2] == 3);
    assert(dmat3[3][1] == 8);
    dmat3.insert_column(1, std::vector<int>(4,1));
    lal::matrix<int, 4, 4> mat1 {{0, 1, 0, 0, 1, 1, 2, 3, 4, 1, 5, 6, 7, 1, 8, 9}};
    dmat4 = lal::dynamic_matrix<int>(mat1);
    assert(dmat3 == dmat4);
    dmat3.erase_column(2);
    dmat3.erase_row(2);
    lal::matrix<int, 3, 3, false> mat2 {{0, 1, 0, 1, 1, 3, 7, 1, 9}};
    assert(dmat3 == lal::dynamic_matrix<int>(mat2));
    
    lal::matrix<int, 3, 3> mat3 {{2, 3, 4, 5, 6, 7, 8, 9, 10}};
    lal::matrix<int, 3, 3> mat4 {{0, 2, 0, 2, 2, 6, 14, 2, 18}};
    lal::dynamic_matrix<int> dmat5(mat3);
    lal::dynamic_matrix<int> dmat6(dmat);
    lal::dynamic_matrix<int> dmat7(mat4);
    lal::dynamic_matrix<int> dmat8(dmat3);
    assert(dmat5 == dmat + dmat1);
    dmat += dmat1;
    assert(dmat5 == dmat);
    assert(dmat != dmat6);
    dmat -= dmat1;
    assert(dmat == dmat6);
    assert(dmat7 == 2 * dmat3);
    dmat3 *= 2;
    assert(dmat3 != dmat8);
    assert(dmat7 == dmat3);
    assert(dmat7 / 2 == dmat8);
    dmat3 /= 2;
    assert(dmat3 == dmat8);
    assert(dmat * dmat2 == dmat2);
    auto dmat9 = dmat * dmat1;
    dmat *= dmat1;
    lal::matrix<int, 3, 3> mat5 {{6, 6, 6, 15, 15, 15, 24, 24, 24}};
    assert(dmat9 == lal::dynamic_matrix<int> (mat5));
    assert(dmat == lal::dynamic_matrix<int> (mat5));
    
    auto ident = lal::make_dynamic_identity<int>(3);
    assert(ident[0][0] == 1);
    assert(ident[0][1] == 0);
    assert(ident[2][2] == 1);
    
    lal::dynamic_matrix<int> mat_a (3, 3, 1);
    lal::dynamic_matrix<int> mat_b (2, 2, 0);
    mat_b = mat_a; // assignment
    auto mat_c = mat_a; // copy constructor
    mat_a[0][0] = 100;
    mat_b[1][1] = 200;
    mat_c[2][2] = 300;
    assert(mat_a[0][0] == 100);
    assert(mat_a[1][1] == 1);
    assert(mat_a[2][2] == 1);
    assert(mat_b[0][0] == 1);
    assert(mat_b[1][1] == 200);
    assert(mat_b[2][2] == 1);
    assert(mat_c[0][0] == 1);
    assert(mat_c[1][1] == 1);
    assert(mat_c[2][2] == 300);
    auto mat_d = std::move(mat_a); // move constructor (implicit)
    assert(mat_d[0][0] == 100);
    assert(mat_d[1][1] == 1);
    assert(mat_d[2][2] == 1);
}
int main(){
    test_matrix_on_stack();
    test_matrix_on_heap();
    test_vector();
    test_dynamic_matrix();
    return 0;
}
