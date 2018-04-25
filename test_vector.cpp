#include <iostream>
#include <assert.h>
#include "include/vector.hpp"

int main(){
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
    return 0;
}
