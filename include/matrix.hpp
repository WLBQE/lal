#ifndef LAL_MATRIX_HPP
#define LAL_MATRIX_HPP

#include <array>

namespace lal {
    typedef int index_t;

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix {
    public:
        auto operator[](index_t idx) {
            return _base[idx];
        }
    private:
        std::array<std::array<NumericType, Cols>, Rows> _base;
    };
}

#endif // LAL_MATRIX_HPP