#ifndef LAL_MATRIX_HPP
#define LAL_MATRIX_HPP

#include <array>
#include <iterator>
#include <algorithm>

namespace lal {
    typedef std::size_t index_t;

    template<typename NumericType, index_t Rows, index_t Cols>
    class matrix {
        typedef std::array<NumericType, Rows * Cols> base_type;
        base_type _base;

    public:
        typedef typename base_type::value_type value_type;
        typedef typename base_type::pointer pointer;
        typedef typename base_type::const_pointer const_pointer;
        typedef typename base_type::reference reference;
        typedef typename base_type::const_reference const_reference;
        typedef typename base_type::iterator iterator;
        typedef typename base_type::const_iterator const_iterator;
        typedef typename base_type::reverse_iterator reverse_iterator;
        typedef typename base_type::const_reverse_iterator const_reverse_iterator;
        typedef typename base_type::difference_type difference_type;
        typedef typename base_type::size_type size_type;


        constexpr matrix() noexcept : _base{} {}

        constexpr explicit matrix(base_type init) noexcept : _base{init} {}

        explicit matrix(const value_type &val) {
            _base.fill(val);
        }

        constexpr pointer operator[](index_t idx) {
            return _base.data() + idx * Cols;
        }

        constexpr const_pointer operator[](index_t idx) const {
            return _base.data() + idx * Cols;
        }

        constexpr reference at(index_t row, index_t col) {
            if (row >= Rows || col >= Cols)
                throw std::out_of_range("index out of range");
            return _base[row * Cols + col];
        }

        constexpr const_reference &at(index_t row, index_t col) const {
            if (row >= Rows || col >= Cols)
                throw std::out_of_range("index out of range");
            return _base[row * Cols + col];
        }

        constexpr iterator begin() noexcept {
            return _base.begin();
        }

        constexpr const_iterator begin() const noexcept {
            return _base.begin();
        }

        constexpr const_iterator cbegin() const noexcept {
            return _base.cbegin();
        }

        constexpr iterator end() noexcept {
            return _base.end();
        }

        constexpr const_iterator end() const noexcept {
            return _base.end();
        }

        constexpr const_iterator cend() const noexcept {
            return _base.cend();
        }

        constexpr reverse_iterator rbegin() noexcept {
            return _base.rbegin();
        }

        constexpr const_reverse_iterator rbegin() const noexcept {
            return _base.rbegin();
        }

        constexpr const_reverse_iterator crbegin() const noexcept {
            return _base.crbegin();
        }

        constexpr reverse_iterator rend() noexcept {
            return _base.rend();
        }

        constexpr const_reverse_iterator rend() const noexcept {
            return _base.rend();
        }

        constexpr const_reverse_iterator crend() const noexcept {
            return _base.crend();
        }

        void swap(matrix<NumericType, Rows, Cols> &other) noexcept {
            this->_base.swap(other._base);
        }

        constexpr size_type size() const noexcept {
            return Rows * Cols;
        }

        constexpr size_type max_size() const noexcept {
            return Rows * Cols;
        }

        constexpr bool empty() const noexcept {
            return Rows * Cols == 0;
        }

        class column_iterator;
    };

    template<typename NumericType, index_t Rows, index_t Cols>
    inline bool operator==(const matrix<NumericType, Rows, Cols> &lhs, const matrix<NumericType, Rows, Cols> &rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<typename NumericType, index_t Rows, index_t Cols>
    inline bool operator!=(const matrix<NumericType, Rows, Cols> &lhs, const matrix<NumericType, Rows, Cols> &rhs) {
        return !(lhs == rhs);
    }

    template<typename NumericType, index_t _Rows, index_t _Cols>
    std::ostream &operator<<(std::ostream &os, const matrix<NumericType, _Rows, _Cols> &m) {
        for (index_t i = 0; i < _Rows; ++i) {
            for (index_t j = 0; j < _Cols; ++j) {
                os << " " << m[i][j];
            }
            os << std::endl;
        }
        return os;
    }

    template<typename NumericType, index_t _Rows, index_t _Cols>
    std::istream &operator>>(std::istream &is, const matrix<NumericType, _Rows, _Cols> &m) {
        for (index_t i = 0; i < _Rows; ++i) {
            for (index_t j = 0; j < _Cols; ++j) {
                is >> m[i][j];
            }
        }
        return is;
    }

}

#endif // LAL_MATRIX_HPP