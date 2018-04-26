#include <iostream>
#include <assert.h>
#include <vector>
#include "include/dmatrix.hpp"

lal::dynamic_matrix<int> foo() {
    return lal::dynamic_matrix<int> (3, 3);
}

int main()
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


    i = 1;
    for (auto it = dmat.cbegin(); it < dmat.cend(); it++){
        assert(*it == i);
        i++;
    }
    assert(*dmat.cbegin() == 1);
    assert(*(dmat.cbegin() + 1) == 2);
    
    i = 9;
    auto it2 = dmat.rbegin();
    it2++;
    assert(*it2 == 8);
    for (auto it = dmat.rbegin(); it < dmat.rend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*dmat.rbegin() == 9);
    assert(*(dmat.rbegin() + 2) == 7);
    
    i = 9;
    for (auto it = dmat.crbegin(); it < dmat.crend(); it++){
        assert(*it == i);
        i--;
    }
    assert(*dmat.crbegin() == 9);
    assert(*(dmat.crbegin() + 1) == 8);
    
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
    return 0;
}
