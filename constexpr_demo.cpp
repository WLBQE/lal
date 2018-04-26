#include <cstdio>
#include "include/matrix.hpp"

int main() {
    lal::matrix<int, 2, 3> m1 {{1, 2, 3, 4, 5, 6}};
    lal::matrix<int, 3, 2> m2 {{6, 5, 4, 3, 2, 1}};
    for (auto& val : m1 * m2)
        printf("%d\n", val);
    return 0;
}
