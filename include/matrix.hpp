#ifndef LAL_MATRIX_HPP
#define LAL_MATRIX_HPP

#include <algorithm>
#include <array>
#include <iterator>
#include <type_traits>

namespace lal {
    typedef std::size_t index_t;

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix_col_iterator;

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix_const_col_iterator;

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix {
        static_assert(Rows > 0 && Cols > 0, "matrix dimensions must be positive");

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

        typedef std::conditional_t<(Rows > 1 && Cols > 1), matrix_col_iterator<NumericType, Rows, Cols>, iterator>
                col_iterator;
        typedef std::conditional_t<(Rows > 1 && Cols > 1), matrix_const_col_iterator<NumericType, Rows, Cols>,
                const_iterator> const_col_iterator;
        typedef std::reverse_iterator<col_iterator> reverse_col_iterator;
        typedef std::reverse_iterator<const_col_iterator> const_reverse_col_iterator;

        constexpr matrix() : _base{} {}

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
    };

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix_col_iterator {
        static_assert(Rows > 1 && Cols > 1, "invalid dimension");

        typedef matrix<NumericType, Rows, Cols> _base;
        typedef matrix_col_iterator<NumericType, Rows, Cols> _self;
        typedef matrix_const_col_iterator<NumericType, Rows, Cols> _const_it;

    public:
        typedef typename _base::difference_type difference_type;
        typedef typename _base::value_type value_type;
        typedef typename _base::pointer pointer;
        typedef typename _base::reference reference;
        typedef std::random_access_iterator_tag iterator_category;

        constexpr matrix_col_iterator() : _ptr {nullptr}, _row {0}, _col {0} {}

        constexpr matrix_col_iterator(pointer ptr, index_t row, index_t col) noexcept
                : _ptr {ptr}, _row {row}, _col {col} {}

        reference operator*() const {
            return *_ptr;
        }

        pointer operator->() const noexcept {
            return _ptr;
        }

        _self& operator++() noexcept {
            if (_row + 1 == Rows) {
                _row = 0;
                ++_col;
                _ptr -= (Rows - 1) * Cols - 1;
            } else {
                ++_row;
                _ptr += Cols;
            }
            return *this;
        };

        const _self operator++(int) noexcept {
            _self tmp = *this;
            ++*this;
            return tmp;
        }

        _self& operator--() noexcept {
            if (_row == 0) {
                _row = Rows - 1;
                --_col;
                _ptr += (Rows - 1) * Cols - 1;
            }
            return *this;
        };

        const _self operator--(int) noexcept {
            _self tmp = *this;
            --*this;
            return tmp;
        }

        bool operator==(const _self& rhs) const noexcept {
            return _ptr == rhs._ptr && _row == rhs._row && _col == rhs._col;
        }

        bool operator==(const _const_it& rhs) const noexcept {
            // TODO: implement
            return false;
        }

        bool operator!=(const _self& rhs) const noexcept {
            return !(*this == rhs);
        }

        bool operator!=(const _const_it& rhs) const noexcept {
            return !(*this == rhs);
        }

        _self& operator+=(difference_type n) noexcept;

        _self& operator-=(difference_type n) noexcept {
            return *this += -n;
        }

        _self operator+(difference_type n) const noexcept {
            _self tmp {*this};
            return tmp += n;
        }

        _self operator-(difference_type n) const noexcept {
            _self tmp {*this};
            return tmp -= n;
        }

        difference_type operator-(const _self& other) const noexcept {
            return (_col - other._col) * Rows + _row - other._row;
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

        bool operator<(const _self& rhs) const noexcept {
            return _col == rhs._col ? _row < rhs._row : _col < rhs._col;
        }

        bool operator>(const _self& rhs) const noexcept {
            return rhs < *this;
        }

        bool operator<=(const _self& rhs) const noexcept {
            return _col == rhs._col ? _row <= rhs._row : _col < rhs._col;
        }

        bool operator>=(const _self& rhs) const noexcept {
            return rhs <= *this;
        }

    private:
        index_t _row;
        index_t _col;
        pointer _ptr;
    };

    template <typename NumericType, index_t Rows, index_t Cols>
    matrix_col_iterator<NumericType, Rows, Cols>&
    matrix_col_iterator<NumericType, Rows, Cols>::operator+=(
            matrix_col_iterator<NumericType, Rows, Cols>::difference_type n
    ) noexcept {
        _ptr -= _row * Cols + _col;
        auto old_row = _row;
        _row = (_row + n) % Rows;
        _col += (old_row + n) / Rows;
        if (_row < 0) {
            _row += Rows;
            --_col;
        }
        _ptr += _row * Cols + _col;
        return *this;
    };

    template <typename NumericType, index_t Rows, index_t Cols>
    inline matrix_col_iterator<NumericType, Rows, Cols>
    operator+(typename matrix_col_iterator<NumericType, Rows, Cols>::difference_type n,
              matrix_col_iterator<NumericType, Rows, Cols> it) noexcept {
        return it += n;
    };

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix_const_col_iterator {
        static_assert(Rows > 1 && Cols > 1, "invalid dimension");
    };

    template <typename NumericType, index_t Rows, index_t Cols>
    inline bool operator==(const matrix<NumericType, Rows, Cols>& lhs, const matrix<NumericType, Rows, Cols>& rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename NumericType, index_t Rows, index_t Cols>
    inline bool operator!=(const matrix<NumericType, Rows, Cols>& lhs, const matrix<NumericType, Rows, Cols>& rhs) {
        return !(lhs == rhs);
    }

    template <typename NumericType, index_t Rows, index_t Cols>
    std::ostream& operator<<(std::ostream& os, const matrix<NumericType, Rows, Cols>& m) {
        for (index_t i {0}; i < Rows; ++i) {
            for (index_t j {0}; j < Cols; ++j)
                os << " " << m[i][j];
            os << '\n';
        }
        return os;
    }

    template <typename NumericType, index_t Rows, index_t Cols>
    std::istream& operator>>(std::istream& is, matrix<NumericType, Rows, Cols>& m) {
        for (auto& val : m) {
            NumericType tmp;
            is >> tmp;
            if (is.good())
                val = tmp;
            else
                break;
        }
        return is;
    }

}

#endif // LAL_MATRIX_HPP