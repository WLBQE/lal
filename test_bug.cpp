#include <iostream>
#include <vector>>
#include <assert.h>
#include "include/dmatrix.hpp"

int main()
{
    lal::dynamic_matrix<double> dmat1(3, 3, 1);
    std::cout << dmat1 << "\n";
    dmat1.insert_column(0, std::vector<double>(3,0));
    std::cout << dmat1 << "\n";
    
    return 0;
}
