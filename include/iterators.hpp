#ifndef LAL_MATRIX_ITERATOR_HPP
#define LAL_MATRIX_ITERATOR_HPP

#include <iterator>

#include "basics.hpp"

namespace lal {
    template <typename Matrix, bool IsConst>
    class general_matrix_iterator {
        using _other_it = general_matrix_iterator<Matrix, !IsConst>;
        using _ptr_type = std::conditional_t<IsConst, const Matrix* const, Matrix* const>;
        friend class general_matrix_iterator<Matrix, !IsConst>;
        _ptr_type _mat;
        index_t _row;
        index_t _col;

    public:
        typedef typename Matrix::difference_type difference_type;
        typedef typename Matrix::value_type value_type;
        typedef std::conditional_t<IsConst, typename Matrix::const_pointer, typename Matrix::pointer> pointer;
        typedef std::conditional_t<IsConst, typename Matrix::const_reference, typename Matrix::reference> reference;
        typedef std::random_access_iterator_tag iterator_category;

        general_matrix_iterator(_ptr_type mat, index_t row, index_t col) noexcept :
                _mat {mat}, _row {row}, _col {col} {}

        template <typename T, typename = std::enable_if_t<IsConst, T>>
        general_matrix_iterator(const general_matrix_iterator<Matrix, !IsConst>& other) noexcept :
                _mat {other._mat}, _row {other._row}, _col {other._col} {}

        reference operator*() const {
            return (*_mat)[_row][_col];
        }

        pointer operator->() const {
            return &(*_mat)[_row][_col];
        }

        general_matrix_iterator& operator++() {
            if (_col + 1 == _mat->cols()) {
                _col = 0;
                ++_row;
            } else {
                ++_col;
            }
            return *this;
        }

        const general_matrix_iterator operator++(int) {
            general_matrix_iterator tmp {*this};
            ++*this;
            return tmp;
        }

        general_matrix_iterator& operator--() {
            if (_col == 0) {
                _col = _mat->cols() - 1;
                --_row;
            } else {
                --_col;
            }
            return *this;
        }

        const general_matrix_iterator operator--(int) {
            general_matrix_iterator tmp {*this};
            --*this;
            return tmp;
        }

        bool operator==(const general_matrix_iterator& rhs) const noexcept {
            return _mat== rhs._mat && _row == rhs._row && _col == rhs._col;
        }

        bool operator==(const _other_it& rhs) const noexcept {
            return _mat == rhs._mat && _row == rhs._row && _col == rhs._col;
        }

        bool operator!=(const general_matrix_iterator& rhs) const noexcept {
            return !(*this == rhs);
        }

        bool operator!=(const _other_it& rhs) const noexcept {
            return !(*this == rhs);
        }

        general_matrix_iterator& operator+=(difference_type n) {
            auto pos = _mat->cols() * _row + _col + n;
            _row = pos / _mat->cols();
            _col = pos % _mat->cols();
            return *this;
        }

        general_matrix_iterator& operator-=(difference_type n) {
            return *this += -n;
        }

        general_matrix_iterator operator+(difference_type n) const {
            general_matrix_iterator tmp {*this};
            return tmp += n;
        }

        general_matrix_iterator operator-(difference_type n) const {
            general_matrix_iterator tmp {*this};
            return tmp -= n;
        }

        difference_type operator-(const general_matrix_iterator& other) const noexcept {
            return (_row - other._row) * _mat->cols() + _col - other._col;
        }

        difference_type operator-(const _other_it& other) const noexcept {
            return (_row - other._row) * _mat->cols() + _col - other._col;
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

        bool operator<(const general_matrix_iterator& rhs) const noexcept {
            return _row == rhs._row ? _col < rhs._col : _row < rhs._row;
        }

        bool operator<(const _other_it & rhs) const noexcept {
            return _row == rhs._row ? _col < rhs._col : _row < rhs._row;
        }

        bool operator>(const general_matrix_iterator& rhs) const noexcept {
            return rhs < *this;
        }

        bool operator>(const _other_it& rhs) const noexcept {
            return rhs < *this;
        }

        bool operator<=(const general_matrix_iterator& rhs) const noexcept {
            return _row == rhs._row ? _col <= rhs._col : _row < rhs._row;
        }

        bool operator<=(const _other_it & rhs) const noexcept {
            return _row == rhs._row ? _col <= rhs._col : _row < rhs._row;
        }

        bool operator>=(const general_matrix_iterator& rhs) const noexcept {
            return rhs <= *this;
        }

        bool operator>=(const _other_it& rhs) const noexcept {
            return rhs <= *this;
        }
    };

    template <typename Matrix, bool IsConst>
    class general_matrix_col_iterator {
        using _other_it = general_matrix_col_iterator<Matrix, !IsConst>;
        using _ptr_type = std::conditional_t<IsConst, const Matrix* const, Matrix* const>;
        friend class general_matrix_col_iterator<Matrix, !IsConst>;
        _ptr_type _mat;
        index_t _row;
        index_t _col;

    public:
        typedef typename Matrix::difference_type difference_type;
        typedef typename Matrix::value_type value_type;
        typedef std::conditional_t<IsConst, typename Matrix::const_pointer, typename Matrix::pointer> pointer;
        typedef std::conditional_t<IsConst, typename Matrix::const_reference, typename Matrix::reference> reference;
        typedef std::random_access_iterator_tag iterator_category;

        general_matrix_col_iterator(_ptr_type mat, index_t row, index_t col) noexcept :
                _mat {mat}, _row {row}, _col {col} {}

        template <typename T, typename = std::enable_if_t<IsConst, T>>
        constexpr general_matrix_col_iterator(const general_matrix_col_iterator<Matrix, !IsConst>& other) noexcept :
                _mat {other._mat}, _row {other._row}, _col {other._col} {}

        reference operator*() const {
            return (*_mat)[_row][_col];
        }

        pointer operator->() const {
            return &(*_mat)[_row][_col];
        }

        general_matrix_col_iterator& operator++() {
            if (_row + 1 == _mat->rows()) {
                _row = 0;
                ++_col;
            } else {
                ++_row;
            }
            return *this;
        }

        const general_matrix_col_iterator operator++(int) {
            general_matrix_col_iterator tmp {*this};
            ++*this;
            return tmp;
        }

        general_matrix_col_iterator& operator--() {
            if (_row == 0) {
                _row = _mat->rows() - 1;
                --_col;
            } else {
                --_row;
            }
            return *this;
        }

        const general_matrix_col_iterator operator--(int) {
            general_matrix_col_iterator tmp {*this};
            --*this;
            return tmp;
        }

        bool operator==(const general_matrix_col_iterator& rhs) const noexcept {
            return _mat== rhs._mat && _row == rhs._row && _col == rhs._col;
        }

        bool operator==(const _other_it& rhs) const noexcept {
            return _mat == rhs._mat && _row == rhs._row && _col == rhs._col;
        }

        bool operator!=(const general_matrix_col_iterator& rhs) const noexcept {
            return !(*this == rhs);
        }

        bool operator!=(const _other_it& rhs) const noexcept {
            return !(*this == rhs);
        }

        general_matrix_col_iterator& operator+=(difference_type n) {
            auto pos = _mat->rows() * _col + _row + n;
            _row = pos % _mat->cols();
            _col = pos / _mat->cols();
            return *this;
        }

        general_matrix_col_iterator& operator-=(difference_type n) {
            return *this += -n;
        }

        general_matrix_col_iterator operator+(difference_type n) const {
            general_matrix_col_iterator tmp {*this};
            return tmp += n;
        }

        general_matrix_col_iterator operator-(difference_type n) const {
            general_matrix_col_iterator tmp {*this};
            return tmp -= n;
        }

        difference_type operator-(const general_matrix_col_iterator& other) const noexcept {
            return (_col - other._col) * _mat->rows() + _row - other._row;
        }

        difference_type operator-(const _other_it& other) const noexcept {
            return (_col - other._col) * _mat->rows() + _row - other._row;
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

        bool operator<(const general_matrix_col_iterator& rhs) const noexcept {
            return _col == rhs._col ? _row < rhs._row : _col < rhs._col;
        }

        bool operator<(const _other_it & rhs) const noexcept {
            return _col == rhs._col ? _row < rhs._row : _col < rhs._col;
        }

        bool operator>(const general_matrix_col_iterator& rhs) const noexcept {
            return rhs < *this;
        }

        bool operator>(const _other_it& rhs) const noexcept {
            return rhs < *this;
        }

        bool operator<=(const general_matrix_col_iterator& rhs) const noexcept {
            return _col == rhs._col ? _row <= rhs._row : _col < rhs._col;
        }

        bool operator<=(const _other_it & rhs) const noexcept {
            return _col == rhs._col ? _row <= rhs._row : _col < rhs._col;
        }

        bool operator>=(const general_matrix_col_iterator& rhs) const noexcept {
            return rhs <= *this;
        }

        bool operator>=(const _other_it& rhs) const noexcept {
            return rhs <= *this;
        }
    };
}

#endif //LAL_MATRIX_ITERATOR_HPP
