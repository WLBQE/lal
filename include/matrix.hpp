#ifndef _INCLUDE_MATRIX_HPP
#define _INCLUDE_MATRIX_HPP

#include <array>

namespace lal {
    typedef int index_t;

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix {
    public:
        matrix();
        ~matrix();
    private:
        std::array<std::array<NumericType, Cols>, Rows> _base;
    };
}

#endif