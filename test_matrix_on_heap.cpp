#include <iostream>
#include <array>
#include <assert.h>
#include "include/matrix.hpp"

lal::matrix<int, 3, 3> foo() {
    return lal::matrix<int, 3, 3> {2};
}

int main()
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

    i = 1;
    for (auto it = mat_on_heap.cbegin(); it < mat_on_heap.cend(); it++){
        assert(*it == i);
        i++;
    }
    assert(*mat_on_heap.cbegin() == 1);
    assert(*(mat_on_heap.cbegin() + 1) == 2);

    i = 9;
    auto it1 = mat_on_heap.rbegin();
    it1++;
    assert(*it1 == 8);
    for (auto it = mat_on_heap.rbegin(); it < mat_on_heap.rend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*mat_on_heap.rbegin() == 9);
    assert(*(mat_on_heap.rbegin() + 2) == 7);
    
    i = 9;
    for (auto it = mat_on_heap.crbegin(); it < mat_on_heap.crend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*mat_on_heap.crbegin() == 9);
    assert(*(mat_on_heap.crbegin() + 1) == 8);

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
    return 0;
}
