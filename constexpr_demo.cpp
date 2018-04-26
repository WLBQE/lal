#include <cstdio>
#include "include/matrix.hpp"

int main() {
    lal::matrix<int, 3, 3> m1 {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    lal::matrix<int, 3, 3> m2 {{9, 8, 7, 6, 5, 4, 3, 2, 1}};
    for (auto& val : m1 * m2)
        printf("%d\n", val);
    return 0;
}