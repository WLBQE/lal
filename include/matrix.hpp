#ifndef LAL_MATRIX_HPP
#define LAL_MATRIX_HPP

#include <array>
#include <iterator>

namespace lal {
    typedef int index_t;

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix {
    public:
        constexpr matrix() noexcept : _base {} {}

        constexpr explicit matrix(std::array<NumericType, Rows * Cols> init) noexcept : _base {init} {}

        constexpr NumericType* operator[](index_t idx) {
            return _base.data() + idx * Cols;
        }

        constexpr const NumericType* operator[](index_t idx) const {
            return _base.data() + idx * Cols;
        }

        constexpr NumericType& at(index_t row, index_t col) {
            if (row >= Rows || col >= Cols)
                throw std::out_of_range("index out of range");
            return _base[row * Cols + col];
        }

        constexpr const NumericType& at(index_t row, index_t col) const {
            if (row >= Rows || col >= Cols)
                throw std::out_of_range("index out of range");
            return _base[row * Cols + col];
        }

    private:
        std::array<NumericType, Rows * Cols> _base;
    };
}

#endif // LAL_MATRIX_HPP