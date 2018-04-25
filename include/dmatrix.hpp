#ifndef LAL_DMATRIX_HPP
#define LAL_DMATRIX_HPP

#include <algorithm>
#include <limits>
#include <memory>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "basics.hpp"
#include "matrix.hpp"
#include "iterators.hpp"

namespace lal {
    template <typename NumericType>
    class dynamic_matrix;

    template <typename NumericType1, typename NumericType2>
    dynamic_matrix<NumericType1>
    operator*(const dynamic_matrix<NumericType1>& m1, const dynamic_matrix<NumericType2>& m2);

    template <typename NumericType>
    class dynamic_matrix {
        using _row_type = std::vector<NumericType>;
        using _base_type = std::vector<_row_type>;
        _base_type _base;
        index_t _cols;

    public:
        typedef typename _row_type::value_type value_type;
        typedef typename _row_type::pointer pointer;
        typedef typename _row_type::const_pointer const_pointer;
        typedef typename _row_type::reference reference;
        typedef typename _row_type::const_reference const_reference;
        typedef general_matrix_iterator<dynamic_matrix, false> iterator;
        typedef general_matrix_iterator<dynamic_matrix, true> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef general_matrix_col_iterator<dynamic_matrix, false> col_iterator;
        typedef general_matrix_col_iterator<dynamic_matrix, true> const_col_iterator;
        typedef std::reverse_iterator<col_iterator> reverse_col_iterator;
        typedef std::reverse_iterator<const_col_iterator> const_reverse_col_iterator;
        typedef typename _row_type::difference_type difference_type;
        typedef typename _row_type::size_type size_type;

        dynamic_matrix() : _base() , _cols(0) {}

        dynamic_matrix(index_t rows, index_t cols, const NumericType& val = 0) :
                _base(rows, _row_type(cols, val)), _cols(cols) {}

        template <typename NumericType2, index_t Rows, index_t Cols, bool OnStack>
        explicit dynamic_matrix(const matrix<NumericType2, Rows, Cols, OnStack>& other) :
                _base(Rows, _row_type(Cols)), _cols(Cols) {
            std::transform(other.begin(), other.end(), begin(), [](const NumericType2& val) -> NumericType {
                return val;
            });
        }

        template <typename NumericType2>
        explicit dynamic_matrix(const dynamic_matrix<NumericType2>& other) :
                _base(other.rows(), _row_type(other.cols())), _cols(other.cols()) {
            std::transform(other.begin(), other.end(), begin(), [](const NumericType2& val) -> NumericType {
                return val;
            });
        }

        template <typename NumericType2, index_t Rows, index_t Cols, bool OnStack>
        explicit operator matrix<NumericType2, Rows, Cols, OnStack>() const {
            if (rows() != Rows || cols() != Cols)
                throw std::logic_error {"matrix dimensions do not match"};
            matrix<NumericType2, Rows, Cols, OnStack> ret;
            std::transform(begin(), end(), ret.begin(), [](const NumericType& val) -> NumericType2 { return val; });
            return ret;
        }

        pointer operator[](index_t idx) {
            return _base[idx].data();
        }

        const_pointer operator[](index_t idx) const {
            return _base[idx].data();
        }

        reference at(index_t row, index_t col) {
            if (row >= rows() || col >= cols())
                throw std::out_of_range {"index out of range"};
            return _base[row][col];
        }

        const_reference at(index_t row, index_t col) const {
            if (row >= rows() || col >= cols())
                throw std::out_of_range {"index out of range"};
            return _base[row][col];
        }

        index_t rows() const {
            return _base.size();
        }

        index_t cols() const {
            return _cols;
        }

        iterator begin() noexcept {
            return iterator {this, 0, 0};
        }

        const_iterator begin() const noexcept {
            return const_iterator {this, 0, 0};
        }

        const_iterator cbegin() const noexcept {
            return const_iterator {this, 0, 0};
        }

        iterator end() noexcept {
            return iterator {this, rows(), 0};
        }

        const_iterator end() const noexcept {
            return const_iterator {this, rows(), 0};
        }

        const_iterator cend() const noexcept {
            return const_iterator {this, rows(), 0};
        }

        reverse_iterator rbegin() noexcept {
            return reverse_iterator {end()};
        }

        const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator {end()};
        }

        const_reverse_iterator crbegin() const noexcept {
            return const_reverse_iterator {cend()};
        }

        reverse_iterator rend() noexcept {
            return reverse_iterator {begin()};
        }

        const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator {begin()};
        }

        const_reverse_iterator crend() const noexcept {
            return const_reverse_iterator {cbegin()};
        }

        col_iterator col_begin() noexcept {
            return col_iterator {this, 0, 0};
        }

        const_col_iterator col_begin() const noexcept {
            return const_col_iterator {this, 0, 0};
        }

        const_col_iterator col_cbegin() const noexcept {
            return const_col_iterator {this, 0, 0};
        }

        col_iterator col_end() noexcept {
            return col_iterator {this, 0, cols()};
        }

        const_col_iterator col_end() const noexcept {
            return const_col_iterator {this, 0, cols()};
        }

        const_col_iterator col_cend() const noexcept {
            return const_col_iterator {this, 0, cols()};
        }

        reverse_col_iterator col_rbegin() noexcept {
            return reverse_col_iterator {col_end()};
        }

        const_reverse_col_iterator col_rbegin() const noexcept {
            return const_reverse_col_iterator {col_end()};
        }

        const_reverse_col_iterator col_crbegin() const noexcept {
            return const_reverse_col_iterator {col_cend()};
        }

        reverse_col_iterator col_rend() noexcept {
            return reverse_col_iterator {col_begin()};
        }

        const_reverse_col_iterator col_rend() const noexcept {
            return const_reverse_col_iterator {col_begin()};
        }

        const_reverse_col_iterator col_crend() const noexcept {
            return const_reverse_col_iterator {col_cbegin()};
        }

        iterator begin(index_t row) {
            if (row >= rows())
                throw std::out_of_range {"row number out of range"};
            return iterator {this, row, 0};
        }

        const_iterator begin(index_t row) const {
            if (row >= rows())
                throw std::out_of_range {"row number out of range"};
            return const_iterator {this, row, 0};
        }

        const_iterator cbegin(index_t row) const {
            if (row >= rows())
                throw std::out_of_range {"row number out of range"};
            return const_iterator {this, row, 0};
        }

        iterator end(index_t row) {
            if (row >= rows())
                throw std::out_of_range {"row number out of range"};
            return iterator {this, row + 1, 0};
        }

        const_iterator end(index_t row) const {
            if (row >= rows())
                throw std::out_of_range {"row number out of range"};
            return const_iterator {this, row + 1, 0};
        }

        const_iterator cend(index_t row) const {
            if (row >= rows())
                throw std::out_of_range {"row number out of range"};
            return const_iterator {this, row + 1, 0};
        }

        reverse_iterator rbegin(index_t row) {
            return reverse_iterator {end(row)};
        }

        const_reverse_iterator rbegin(index_t row) const {
            return const_reverse_iterator {end(row)};
        }

        const_reverse_iterator crbegin(index_t row) const {
            return const_reverse_iterator {cend(row)};
        }

        reverse_iterator rend(index_t row) {
            return reverse_iterator {begin(row)};
        }

        const_reverse_iterator rend(index_t row) const {
            return const_reverse_iterator {begin(row)};
        }

        const_reverse_iterator crend(index_t row) const {
            return const_reverse_iterator {cbegin(row)};
        }

        col_iterator col_begin(index_t col) {
            if (col >= cols())
                throw std::out_of_range {"column number out of range"};
            return col_iterator {this, 0, col};
        };

        const_col_iterator col_begin(index_t col) const {
            if (col >= cols())
                throw std::out_of_range {"column number out of range"};
            return const_col_iterator {this, 0, col};
        }

        const_col_iterator col_cbegin(index_t col) const {
            if (col >= cols())
                throw std::out_of_range {"column number out of range"};
            return const_col_iterator {this, 0, col};
        }

        col_iterator col_end(index_t col) {
            if (col >= cols())
                throw std::out_of_range {"column number out of range"};
            return col_iterator {this, 0, col + 1};
        }

        const_col_iterator col_end(index_t col) const {
            if (col >= cols())
                throw std::out_of_range {"column number out of range"};
            return const_col_iterator {this, 0, col + 1};
        }

        const_col_iterator col_cend(index_t col) const {
            if (col >= cols())
                throw std::out_of_range {"column number out of range"};
            return const_col_iterator {this, 0, col + 1};
        }

        reverse_col_iterator col_rbegin(index_t col) {
            return reverse_col_iterator {col_end(col)};
        }

        const_reverse_col_iterator col_rbegin(index_t col) const {
            return const_reverse_col_iterator {col_end(col)};
        }

        const_reverse_col_iterator col_crbegin(index_t col) const {
            return const_reverse_col_iterator {col_cend(col)};
        }

        reverse_col_iterator col_rend(index_t col) {
            return reverse_col_iterator {col_begin(col)};
        }

        const_reverse_col_iterator col_rend(index_t col) const {
            return const_reverse_col_iterator {col_begin(col)};
        }

        const_reverse_col_iterator col_crend(index_t col) const {
            return const_reverse_col_iterator {col_cbegin(col)};
        }

        void swap(dynamic_matrix& other) noexcept {
            _base.swap(other._base);
        }

        size_t size() const {
            return rows() * cols();
        }

        constexpr size_t max_size() const {
            return static_cast<size_t>(std::numeric_limits<difference_type>::max());
        }

        bool empty() const {
            return rows() * cols() == 0;
        }

        dynamic_matrix operator-() const {
            dynamic_matrix ret {rows(), cols()};
            algo::transform(begin(), end(), ret.begin(), [](const NumericType& num) -> NumericType { return -num; });
            return ret;
        }

        template <typename NumericType2>
        dynamic_matrix& operator +=(dynamic_matrix<NumericType2>& m) {
            if (rows() != m.rows() || cols() != m.cols())
                throw std::logic_error {"matrix dimensions do not match"};
            std::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType2& b) -> NumericType { return a + b; });
            return *this;
        }

        template <typename NumericType2>
        dynamic_matrix& operator -=(dynamic_matrix<NumericType2>& m) {
            if (rows() != m.rows() || cols() != m.cols())
                throw std::logic_error {"matrix dimensions do not match"};
            std::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType2& b) -> NumericType { return a - b; });
            return *this;
        }

        template <typename NumericType2>
        dynamic_matrix& operator*=(const NumericType2& number) {
            std::transform(begin(), end(), begin(), [number](const NumericType& a) -> NumericType {
                return a * number;
            });
            return *this;
        }

        template <typename NumericType2>
        dynamic_matrix& operator/=(const NumericType2& number) {
            std::transform(begin(), end(), begin(), [number](const NumericType& a) -> NumericType {
                return a / number;
            });
            return *this;
        }

        template <typename NumericType2>
        dynamic_matrix& operator*=(dynamic_matrix<NumericType2>& m) {
            if (rows() != cols())
                throw std::logic_error {"operator *= can only be applied to square matrices"};
            *this = *this * m;
            return *this;
        }

        dynamic_matrix<NumericType> transpose() const {
            dynamic_matrix<NumericType> ret {cols(), rows()};
            std::copy(begin(), end(), ret.col_begin());
            return ret;
        }

        void insert_row(index_t pos, std::vector<NumericType> row) {
            if (pos > rows())
                throw std::out_of_range {"invalid insert position"};
            if (row.size() != cols())
                throw std::length_error {"invalid row length"};
            _base.insert(_base.begin() + pos, row);
        }

        void erase_row(index_t pos) {
            if (pos >= rows())
                throw std::out_of_range {"invalid erase position"};
            _base.erase(_base.begin() + pos);
        }

        void insert_column(index_t pos, std::vector<NumericType> col);
        void erase_column(index_t pos);
    };

    template <typename NumericType1, typename NumericType2>
    inline bool operator==(const dynamic_matrix<NumericType1>& lhs, const dynamic_matrix<NumericType2>& rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename NumericType1, typename NumericType2>
    inline bool operator!=(const dynamic_matrix<NumericType1>& lhs, const dynamic_matrix<NumericType2>& rhs) {
        return !(lhs == rhs);
    }

    template <typename NumericType>
    void dynamic_matrix<NumericType>::insert_column(index_t pos, std::vector<NumericType> col) {
        if (pos > cols())
            throw std::out_of_range {"invalid insert position"};
        if (col.size() != rows())
            throw std::length_error {"invalid column length"};
        for (index_t i {0}; i < rows(); ++i)
            _base[i].insert(_base[i].begin() + pos, col[i]);
    }

    template <typename NumericType>
    void dynamic_matrix<NumericType>::erase_column(index_t pos) {
        if (pos >= cols())
            throw std::out_of_range {"invalid erase position"};
        for (auto& row : _base)
            row.erase(row.begin() + pos);
    }

    template <typename NumericType1, typename NumericType2>
    dynamic_matrix<NumericType1>
    operator+(const dynamic_matrix<NumericType1>& m1, const dynamic_matrix<NumericType2>& m2) {
        if (m1.rows() != m2.rows() || m1.cols() != m2.cols())
            throw std::logic_error {"matrix dimensions do not match"};
        dynamic_matrix<NumericType1> ret {m1.rows(), m1.cols()};
        std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                       [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a + b; });
        return ret;
    };

    template <typename NumericType1, typename NumericType2, index_t Rows, index_t Cols, bool OnStack>
    dynamic_matrix<NumericType1>
    operator+(const dynamic_matrix<NumericType1>& m1, const matrix<NumericType2, Rows, Cols, OnStack>& m2) {
        if (m1.rows() != Rows || m1.cols() != Cols)
            throw std::logic_error {"matrix dimensions do not match"};
        dynamic_matrix<NumericType1> ret {Rows, Cols};
        std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                       [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a + b; });
        return ret;
    };

    template <typename NumericType1, index_t Rows, index_t Cols, bool OnStack, typename NumericType2>
    matrix<NumericType1, Rows, Cols, OnStack>
    operator+(const matrix<NumericType2, Rows, Cols, OnStack>& m1, const dynamic_matrix<NumericType2>& m2) {
        if (m2.rows() != Rows || m2.cols() != Cols)
            throw std::logic_error {"matrix dimensions do not match"};
        matrix<NumericType1, Rows, Cols, OnStack> ret;
        std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                       [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a + b; });
        return ret;
    };

    template <typename NumericType1, typename NumericType2>
    dynamic_matrix<NumericType1>
    operator-(const dynamic_matrix<NumericType1>& m1, const dynamic_matrix<NumericType2>& m2) {
        if (m1.rows() != m2.rows() || m1.cols() != m2.cols())
            throw std::logic_error {"matrix dimensions do not match"};
        dynamic_matrix<NumericType1> ret {m1.rows(), m1.cols()};
        std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                       [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a - b; });
        return ret;
    }

    template <typename NumericType1, typename NumericType2, index_t Rows, index_t Cols, bool OnStack>
    dynamic_matrix<NumericType1>
    operator-(const dynamic_matrix<NumericType1>& m1, const matrix<NumericType2, Rows, Cols, OnStack>& m2) {
        if (m1.rows() != Rows || m1.cols() != Cols)
            throw std::logic_error {"matrix dimensions do not match"};
        dynamic_matrix<NumericType1> ret {Rows, Cols};
        std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                       [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a - b; });
        return ret;
    };

    template <typename NumericType1, index_t Rows, index_t Cols, bool OnStack, typename NumericType2>
    matrix<NumericType1, Rows, Cols, OnStack>
    operator-(const matrix<NumericType2, Rows, Cols, OnStack>& m1, const dynamic_matrix<NumericType2>& m2) {
        if (m2.rows() != Rows || m2.cols() != Cols)
            throw std::logic_error {"matrix dimensions do not match"};
        matrix<NumericType1, Rows, Cols, OnStack> ret;
        std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                       [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a - b; });
        return ret;
    };

    template <typename NumericType1, typename NumericType2>
    dynamic_matrix<NumericType1>
    operator*(const dynamic_matrix<NumericType1>& m1, const dynamic_matrix<NumericType2>& m2) {
        if (m1.cols() != m2.rows())
            throw std::logic_error {"matrix dimensions do not match"};
        dynamic_matrix<NumericType1> ret {m1.rows(), m2.cols(), 0};
        for (index_t i {0}; i < m1.rows(); ++i) {
            for (index_t j {0}; j < m2.cols(); ++j) {
                for (index_t k {0}; k < m1.cols(); ++k)
                    ret[i][j] += m1[i][k] * m2[k][j];
            }
        }
        return ret;
    }

    template <typename NumericType1, typename NumericType2, index_t Rows, index_t Cols, bool OnStack>
    dynamic_matrix<NumericType1>
    operator*(const dynamic_matrix<NumericType1>& m1, const matrix<NumericType2, Rows, Cols, OnStack>& m2) {
        if (m1.cols() != Rows)
            throw std::logic_error {"matrix dimensions do not match"};
        dynamic_matrix<NumericType1> ret {m1.rows(), Cols, 0};
        for (index_t i {0}; i < m1.rows(); ++i) {
            for (index_t j {0}; j < m2.cols(); ++j) {
                for (index_t k {0}; k < m1.cols(); ++k)
                    ret[i][j] += m1[i][k] * m2[k][j];
            }
        }
        return ret;
    };

    template <typename NumericType1, index_t Rows, index_t Cols, bool OnStack, typename NumericType2>
    dynamic_matrix<NumericType1>
    operator*(const matrix<NumericType1, Rows, Cols, OnStack>& m1, const dynamic_matrix<NumericType2>& m2) {
        if (Cols != m2.rows())
            throw std::logic_error {"matrix dimensions do not match"};
        dynamic_matrix<NumericType1> ret {Rows, m2.cols(), 0};
        for (index_t i {0}; i < m1.rows(); ++i) {
            for (index_t j {0}; j < m2.cols(); ++j) {
                for (index_t k {0}; k < m1.cols(); ++k)
                    ret[i][j] += m1[i][k] * m2[k][j];
            }
        }
        return ret;
    };

    template <typename NumericType, typename NumericType2>
    dynamic_matrix<NumericType> operator*(const dynamic_matrix<NumericType>& m, const NumericType2& number) {
        dynamic_matrix<NumericType> ret {m.rows(), m.cols()};
        std::transform(m.begin(), m.end(), ret.begin(), [number](const NumericType& a) -> NumericType {
            return a * number;
        });
        return ret;
    }

    template <typename NumericType, typename NumericType2>
    dynamic_matrix<NumericType> operator*(const NumericType2& number, const dynamic_matrix<NumericType>& m) {
        return m * number;
    }

    template <typename NumericType, typename NumericType2>
    dynamic_matrix<NumericType> operator/(const dynamic_matrix<NumericType>& m, const NumericType2& number) {
        dynamic_matrix<NumericType> ret {m.rows(), m.cols()};
        std::transform(m.begin(), m.end(), ret.begin(), [number](const NumericType& a) -> NumericType {
            return a / number;
        });
        return ret;
    }

    template <typename NumericType>
    dynamic_matrix<NumericType>
    make_dynamic_identity(index_t size, const NumericType& one = 1, const NumericType& zero = 0) {
        dynamic_matrix<NumericType> ret {size, size, zero};
        for (index_t i {0}; i < size; ++i)
            ret[i][i] = one;
        return ret;
    };

    template <typename NumericType>
    std::ostream& operator<<(std::ostream& os, const dynamic_matrix<NumericType>& m) {
        for (index_t i {0}; i < m.rows(); ++i) {
            for (index_t j {0}; j < m.cols(); ++j)
                os << " " << m[i][j];
            os << '\n';
        }
        return os;
    }

    template <typename NumericType>
    std::istream& operator>>(std::istream& is, dynamic_matrix<NumericType>& m) {
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
};

#endif // LAL_DMATRIX_HPP
