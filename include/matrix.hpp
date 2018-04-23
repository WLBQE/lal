#ifndef LAL_MATRIX_HPP
#define LAL_MATRIX_HPP

#include <algorithm>
#include <array>
#include <memory>
#include <iostream>
#include <iterator>
#include <type_traits>

#include "constexpr_algorithm.hpp"

namespace lal {
    constexpr std::size_t _stack_threshold {0x100};

    typedef std::size_t index_t;

    template <typename NumericType, index_t Rows, index_t Cols,
            bool OnStack = Rows * Cols * sizeof(NumericType) < _stack_threshold>
    class matrix_col_iterator;

    template <typename NumericType, index_t Rows, index_t Cols,
            bool OnStack = Rows * Cols * sizeof(NumericType) < _stack_threshold>
    class matrix_const_col_iterator;

    template <typename NumericType, index_t Rows, index_t Cols,
            bool OnStack = Rows * Cols * sizeof(NumericType) < _stack_threshold>
    class matrix;

    template <typename NumericType, index_t Size, bool OnStack = Size * Size * sizeof(NumericType) < _stack_threshold>
    using square_matrix = matrix<NumericType, Size, Size, OnStack>;

    template <typename NumericType1, typename NumericType2,
            index_t Rows1, index_t Cols1, index_t Cols2, bool OnStack1, bool OnStack2>
    constexpr matrix<NumericType1, Rows1, Cols2, OnStack1>
    operator*(const matrix<NumericType1, Rows1, Cols1, OnStack1>& m1,
              const matrix<NumericType2, Cols1, Cols2, OnStack2>& m2);

    template <typename NumericType, index_t Rows, index_t Cols>
    class matrix<NumericType, Rows, Cols, true> {
        using _base_type = std::array<NumericType, Rows * Cols>;
        using _self = matrix<NumericType, Rows, Cols, true>;

        _base_type _base;

    public:
        typedef typename _base_type::value_type value_type;
        typedef typename _base_type::pointer pointer;
        typedef typename _base_type::const_pointer const_pointer;
        typedef typename _base_type::reference reference;
        typedef typename _base_type::const_reference const_reference;
        typedef typename _base_type::iterator iterator;
        typedef typename _base_type::const_iterator const_iterator;
        typedef typename _base_type::reverse_iterator reverse_iterator;
        typedef typename _base_type::const_reverse_iterator const_reverse_iterator;
        typedef typename _base_type::difference_type difference_type;
        typedef typename _base_type::size_type size_type;

        typedef std::conditional_t<(Rows > 1 && Cols > 1), matrix_col_iterator<NumericType, Rows, Cols, true>, iterator>
                col_iterator;
        typedef std::conditional_t<(Rows > 1 && Cols > 1), matrix_const_col_iterator<NumericType, Rows, Cols, true>,
                const_iterator> const_col_iterator;
        typedef std::reverse_iterator<col_iterator> reverse_col_iterator;
        typedef std::reverse_iterator<const_col_iterator> const_reverse_col_iterator;

        constexpr matrix() : _base {} {}

        constexpr explicit matrix(_base_type init) noexcept : _base {init} {}

        constexpr explicit matrix(const value_type& val) noexcept;

        operator matrix<NumericType, Rows, Cols, false>() const {
            return matrix<NumericType, Rows, Cols, false> {_base};
        }

        template <typename NumericType2, bool OnStack2>
        operator matrix<NumericType2, Rows, Cols, OnStack2>() const {
            matrix<NumericType2, Rows, Cols, OnStack2> ret;
            std::transform(begin(), end(), ret.begin(), [](const value_type& val) -> NumericType2 {
                return val;
            });
            return ret;
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

        constexpr const_reference at(index_t row, index_t col) const {
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

        constexpr col_iterator col_begin() noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base.data(), 0, 0);
            else
                return begin();
        }

        constexpr const_col_iterator col_begin() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data(), 0, 0);
            else
                return begin();
        }

        constexpr const_col_iterator col_cbegin() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data(), 0, 0);
            else
                return cbegin();
        }

        constexpr col_iterator col_end() noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base.data() + Cols, 0, Cols);
            else
                return end();
        }

        constexpr const_col_iterator col_end() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data() + Cols, 0, Cols);
            else
                return end();
        }

        constexpr const_col_iterator col_cend() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data() + Cols, 0, Cols);
            else
                return cend();
        }

        constexpr reverse_col_iterator col_rbegin() noexcept {
            return reverse_col_iterator(col_end());
        }

        constexpr const_reverse_col_iterator col_rbegin() const noexcept {
            return const_reverse_col_iterator(col_end());
        }

        constexpr const_reverse_col_iterator col_crbegin() const noexcept {
            return const_reverse_col_iterator(col_cend());
        }

        constexpr reverse_col_iterator col_rend() noexcept {
            return reverse_col_iterator(col_begin());
        }

        constexpr const_reverse_col_iterator col_rend() const noexcept {
            return const_reverse_col_iterator(col_begin());
        }

        constexpr const_reverse_col_iterator col_crend() const noexcept {
            return const_reverse_col_iterator(col_cbegin());
        }

        constexpr iterator begin(index_t row) {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base.begin() + row * Cols;
        }

        constexpr const_iterator begin(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base.begin() + row * Cols;
        }

        constexpr const_iterator cbegin(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base.cbegin() + row * Cols;
        }

        constexpr iterator end(index_t row) {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base.begin() + (row + 1) * Cols;
        }

        constexpr const_iterator end(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base.begin() + (row + 1) * Cols;
        }

        constexpr const_iterator cend(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base.cend() + (row + 1) * Cols;
        }

        constexpr reverse_iterator rbegin(index_t row) {
            return reverse_col_iterator(end(row));
        }

        constexpr const_reverse_iterator rbegin(index_t row) const {
            return reverse_col_iterator(end(row));
        }

        constexpr const_reverse_iterator crbegin(index_t row) const {
            return reverse_col_iterator(cend(row));
        }

        constexpr reverse_iterator rend(index_t row) {
            return reverse_col_iterator(begin(row));
        }

        constexpr const_reverse_iterator rend(index_t row) const {
            return reverse_col_iterator(begin(row));
        }

        constexpr const_reverse_iterator crend(index_t row) const {
            return reverse_col_iterator(cbegin(row));
        }

        constexpr col_iterator col_begin(index_t col) {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base.data(), 0, col);
            else
                return begin() + col;
        }

        constexpr const_col_iterator col_begin(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data(), 0, col);
            else
                return begin() + col;
        }

        constexpr const_col_iterator col_cbegin(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data(), 0, col);
            else
                return cbegin() + col;
        }

        constexpr col_iterator col_end(index_t col) {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base.data() + Rows * Cols, 0, col + 1);
            else
                return begin() + col + 1;
        }

        constexpr const_col_iterator col_end(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data() + Rows * Cols, 0, col + 1);
            else
                return begin() + col + 1;
        }

        constexpr const_col_iterator col_cend(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base.data() + Rows * Cols, 0, col + 1);
            else
                return begin() + col + 1;
        }

        constexpr reverse_col_iterator col_rbegin(index_t col) {
            return reverse_col_iterator(col_end(col));
        }

        constexpr const_reverse_col_iterator col_rbegin(index_t col) const {
            return const_reverse_col_iterator(col_end(col));
        }

        constexpr const_reverse_col_iterator col_crbegin(index_t col) const {
            return const_reverse_col_iterator(col_cend(col));
        }

        constexpr reverse_col_iterator col_rend(index_t col) {
            return reverse_col_iterator(col_begin(col));
        }

        constexpr const_reverse_col_iterator col_rend(index_t col) const {
            return const_reverse_col_iterator(col_begin(col));
        }

        constexpr const_reverse_col_iterator col_crend(index_t col) const {
            return const_reverse_col_iterator(col_cbegin(col));
        }

        void swap(_self& other) noexcept {
            _base.swap(other._base);
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

        template <typename NumericType2, bool OnStack2>
        constexpr _self& operator+=(matrix<NumericType2, Rows, Cols, OnStack2>& m) {
            algo::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType2& b) -> NumericType { return a + b; });
            return *this;
        }

        template <typename NumericType2, bool OnStack2>
        constexpr _self& operator-=(matrix<NumericType2, Rows, Cols, OnStack2>& m) {
            algo::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType2& b) -> NumericType { return a - b; });
            return *this;
        }

        template <typename NumericType2>
        constexpr _self& operator*=(const NumericType2& number) {
            algo::transform(begin(), end(), begin(), [number](const NumericType& a) -> NumericType {
                return a * number;
            });
            return *this;
        }

        template <typename NumericType2>
        constexpr _self& operator/=(const NumericType2& number) {
            algo::transform(begin(), end(), begin(), [number](const NumericType& a) -> NumericType {
                return a / number;
            });
            return *this;
        }

        template <typename NumericType2, bool OnStack2, typename = std::enable_if_t<Rows == Cols, NumericType2>>
        constexpr _self& operator*=(matrix<NumericType2, Rows, Cols, OnStack2>& m) {
            *this = *this * m;
            return *this;
        }

        constexpr matrix<NumericType, Cols, Rows, true> transpose() const {
            matrix<NumericType, Cols, Rows, true> ret;
            algo::copy(begin(), end(), ret.col_begin());
            return ret;
        }
    };

    template <typename NumericType, index_t Rows, index_t Cols>
    constexpr matrix<NumericType, Rows, Cols, true>::matrix(const value_type& val) noexcept : _base {} {
        for (auto& v : _base)
            v = val;
    }

    // OnStack = false
    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    class matrix {
        using _base_type = std::array<NumericType, Rows * Cols>;
        using _self = matrix<NumericType, Rows, Cols, OnStack>;

        std::unique_ptr<_base_type> _base;

    public:
        typedef typename _base_type::value_type value_type;
        typedef typename _base_type::pointer pointer;
        typedef typename _base_type::const_pointer const_pointer;
        typedef typename _base_type::reference reference;
        typedef typename _base_type::const_reference const_reference;
        typedef typename _base_type::iterator iterator;
        typedef typename _base_type::const_iterator const_iterator;
        typedef typename _base_type::reverse_iterator reverse_iterator;
        typedef typename _base_type::const_reverse_iterator const_reverse_iterator;
        typedef typename _base_type::difference_type difference_type;
        typedef typename _base_type::size_type size_type;

        typedef std::conditional_t<(Rows > 1 && Cols > 1), matrix_col_iterator<NumericType, Rows, Cols, OnStack>,
                iterator> col_iterator;
        typedef std::conditional_t<(Rows > 1 && Cols > 1), matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>,
                const_iterator> const_col_iterator;
        typedef std::reverse_iterator<col_iterator> reverse_col_iterator;
        typedef std::reverse_iterator<const_col_iterator> const_reverse_col_iterator;

        matrix() : _base {std::make_unique<_base_type>()} {}

        explicit matrix(_base_type init) : _base {std::make_unique<_base_type>(init)} {}

        explicit matrix(const value_type& val) : _base {std::make_unique<_base_type>()} {
            _base->fill(val);
        }

        operator matrix<NumericType, Rows, Cols, !OnStack>() const noexcept {
            return matrix<NumericType, Rows, Cols, !OnStack> {*_base};
        }

        template <typename NumericType2, bool OnStack2>
        operator matrix<NumericType2, Rows, Cols, OnStack2>() const {
            matrix<NumericType2, Rows, Cols, OnStack2> ret;
            std::transform(begin(), end(), ret.begin(), [](const value_type& val) -> NumericType2 {
                return val;
            });
            return ret;
        }

        pointer operator[](index_t idx) {
            return _base->data() + idx * Cols;
        }

        const_pointer operator[](index_t idx) const {
            return _base->data() + idx * Cols;
        }

        reference at(index_t row, index_t col) {
            if (row >= Rows || col >= Cols)
                throw std::out_of_range("index out of range");
            return (*_base)[row * Cols + col];
        }

        const_reference at(index_t row, index_t col) const {
            if (row >= Rows || col >= Cols)
                throw std::out_of_range("index out of range");
            return (*_base)[row * Cols + col];
        }

        iterator begin() noexcept {
            return _base->begin();
        }

        const_iterator begin() const noexcept {
            return _base->begin();
        }

        const_iterator cbegin() const noexcept {
            return _base->cbegin();
        }

        iterator end() noexcept {
            return _base->end();
        }

        const_iterator end() const noexcept {
            return _base->end();
        }

        const_iterator cend() const noexcept {
            return _base->cend();
        }

        reverse_iterator rbegin() noexcept {
            return _base->rbegin();
        }

        const_reverse_iterator rbegin() const noexcept {
            return _base->rbegin();
        }

        const_reverse_iterator crbegin() const noexcept {
            return _base->crbegin();
        }

        reverse_iterator rend() noexcept {
            return _base->rend();
        }

        const_reverse_iterator rend() const noexcept {
            return _base->rend();
        }

        const_reverse_iterator crend() const noexcept {
            return _base->crend();
        }

        col_iterator col_begin() noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base->data(), 0, 0);
            else
                return begin();
        }

        const_col_iterator col_begin() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data(), 0, 0);
            else
                return begin();
        }

        const_col_iterator col_cbegin() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data(), 0, 0);
            else
                return cbegin();
        }

        col_iterator col_end() noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base->data() + Cols, 0, Cols);
            else
                return end();
        }

        const_col_iterator col_end() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data() + Cols, 0, Cols);
            else
                return end();
        }

        const_col_iterator col_cend() const noexcept {
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data() + Cols, 0, Cols);
            else
                return cend();
        }

        reverse_col_iterator col_rbegin() noexcept {
            return reverse_col_iterator(col_end());
        }

        const_reverse_col_iterator col_rbegin() const noexcept {
            return const_reverse_col_iterator(col_end());
        }

        const_reverse_col_iterator col_crbegin() const noexcept {
            return const_reverse_col_iterator(col_cend());
        }

        reverse_col_iterator col_rend() noexcept {
            return reverse_col_iterator(col_begin());
        }

        const_reverse_col_iterator col_rend() const noexcept {
            return const_reverse_col_iterator(col_begin());
        }

        const_reverse_col_iterator col_crend() const noexcept {
            return const_reverse_col_iterator(col_cbegin());
        }

        iterator begin(index_t row) {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base->begin() + row * Cols;
        }

        const_iterator begin(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base->begin() + row * Cols;
        }

        const_iterator cbegin(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base->cbegin() + row * Cols;
        }

        iterator end(index_t row) {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base->begin() + (row + 1) * Cols;
        }

        const_iterator end(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base->begin() + (row + 1) * Cols;
        }

        const_iterator cend(index_t row) const {
            if (row >= Rows)
                throw std::out_of_range("row number out of range");
            return _base->cend() + (row + 1) * Cols;
        }

        reverse_iterator rbegin(index_t row) {
            return reverse_col_iterator(end(row));
        }

        const_reverse_iterator rbegin(index_t row) const {
            return reverse_col_iterator(end(row));
        }

        const_reverse_iterator crbegin(index_t row) const {
            return reverse_col_iterator(cend(row));
        }

        reverse_iterator rend(index_t row) {
            return reverse_col_iterator(begin(row));
        }

        const_reverse_iterator rend(index_t row) const {
            return reverse_col_iterator(begin(row));
        }

        const_reverse_iterator crend(index_t row) const {
            return reverse_col_iterator(cbegin(row));
        }

        col_iterator col_begin(index_t col) {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base->data(), 0, col);
            else
                return begin() + col;
        }

        const_col_iterator col_begin(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data(), 0, col);
            else
                return begin() + col;
        }

        const_col_iterator col_cbegin(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data(), 0, col);
            else
                return cbegin() + col;
        }

        col_iterator col_end(index_t col) {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return col_iterator(_base->data() + Rows * Cols, 0, col + 1);
            else
                return begin() + col + 1;
        }

        const_col_iterator col_end(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data() + Rows * Cols, 0, col + 1);
            else
                return begin() + col + 1;
        }

        const_col_iterator col_cend(index_t col) const {
            if (col >= Cols)
                throw std::out_of_range("column number out of range");
            if constexpr (Rows > 1 && Cols > 1)
                return const_col_iterator(_base->data() + Rows * Cols, 0, col + 1);
            else
                return begin() + col + 1;
        }

        reverse_col_iterator col_rbegin(index_t col) {
            return reverse_col_iterator(col_end(col));
        }

        const_reverse_col_iterator col_rbegin(index_t col) const {
            return const_reverse_col_iterator(col_end(col));
        }

        const_reverse_col_iterator col_crbegin(index_t col) const {
            return const_reverse_col_iterator(col_cend(col));
        }

        reverse_col_iterator col_rend(index_t col) {
            return reverse_col_iterator(col_begin(col));
        }

        const_reverse_col_iterator col_rend(index_t col) const {
            return const_reverse_col_iterator(col_begin(col));
        }

        const_reverse_col_iterator col_crend(index_t col) const {
            return const_reverse_col_iterator(col_cbegin(col));
        }

        void swap(_self& other) noexcept {
            _base.swap(other._base);
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

        template <typename NumericType2, bool OnStack2>
        _self& operator+=(matrix<NumericType, Rows, Cols, OnStack2>& m) {
            std::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType2& b) -> NumericType { return a + b; });
            return *this;
        }

        template <typename NumericType2, bool OnStack2>
        _self& operator-=(matrix<NumericType2, Rows, Cols, OnStack2>& m) {
            std::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType2& b) -> NumericType { return a - b; });
            return *this;
        }

        template <typename NumericType2>
        _self& operator*=(const NumericType& number) {
            std::transform(begin(), end(), begin(), [number](const NumericType& a) -> NumericType {
                return a * number;
            });
            return *this;
        }

        template <typename NumericType2>
        _self& operator/=(const NumericType& number) {
            std::transform(begin(), end(), begin(), [number](const NumericType& a) -> NumericType {
                return a / number;
            });
            return *this;
        }

        template <typename NumericType2, bool OnStack2, typename = std::enable_if_t<Rows == Cols, NumericType2>>
        _self& operator*=(matrix<NumericType2, Rows, Cols, OnStack2>& m) {
            *this = *this * m;
            return *this;
        }

        matrix<NumericType, Cols, Rows, OnStack> transpose() const {
            matrix<NumericType, Cols, Rows, OnStack> ret;
            std::copy(begin(), end(), ret.col_begin());
            return ret;
        }
    };

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    class matrix_col_iterator {
        static_assert(Rows > 1 && Cols > 1, "invalid dimension");

        using _base = matrix<NumericType, Rows, Cols, OnStack>;
        using _self = matrix_col_iterator<NumericType, Rows, Cols, OnStack>;
        using _const_it = matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>;

    public:
        typedef typename _base::difference_type difference_type;
        typedef typename _base::value_type value_type;
        typedef typename _base::pointer pointer;
        typedef typename _base::reference reference;
        typedef std::random_access_iterator_tag iterator_category;

        constexpr matrix_col_iterator() : _row {0}, _col {0}, _ptr {nullptr} {}

        constexpr matrix_col_iterator(pointer ptr, index_t row, index_t col) noexcept
                : _row {row}, _col {col}, _ptr {ptr} {}

        constexpr reference operator*() const {
            return *_ptr;
        }

        constexpr pointer operator->() const noexcept {
            return _ptr;
        }

        constexpr _self& operator++() noexcept {
            if (_row + 1 == Rows) {
                _row = 0;
                ++_col;
                _ptr -= (Rows - 1) * Cols - 1;
            } else {
                ++_row;
                _ptr += Cols;
            }
            return *this;
        }

        constexpr const _self operator++(int) noexcept {
            _self tmp {*this};
            ++*this;
            return tmp;
        }

        constexpr _self& operator--() noexcept {
            if (_row == 0) {
                _row = Rows - 1;
                --_col;
                _ptr += (Rows - 1) * Cols - 1;
            } else {
                --_row;
                _ptr -= Cols;
            }
            return *this;
        }

        constexpr const _self operator--(int) noexcept {
            _self tmp {*this};
            --*this;
            return tmp;
        }

        constexpr bool operator==(const _self& rhs) const noexcept {
            return _ptr == rhs._ptr && _row == rhs._row && _col == rhs._col;
        }

        constexpr bool operator==(const _const_it& rhs) const noexcept {
            return _ptr == rhs._ptr && _row == rhs._row && _col == rhs._col;
        }

        constexpr bool operator!=(const _self& rhs) const noexcept {
            return !(*this == rhs);
        }

        constexpr bool operator!=(const _const_it& rhs) const noexcept {
            return !(*this == rhs);
        }

        constexpr _self& operator+=(difference_type n) noexcept;

        constexpr _self& operator-=(difference_type n) noexcept {
            return *this += -n;
        }

        constexpr _self operator+(difference_type n) const noexcept {
            _self tmp {*this};
            return tmp += n;
        }

        constexpr _self operator-(difference_type n) const noexcept {
            _self tmp {*this};
            return tmp -= n;
        }

        constexpr difference_type operator-(const _self& other) const noexcept {
            return (_col - other._col) * Rows + _row - other._row;
        }

        constexpr difference_type operator-(const _const_it& other) const noexcept {
            return (_col - other._col) * Rows + _row - other._row;
        }

        constexpr reference operator[](difference_type n) const {
            return *(*this + n);
        }

        constexpr bool operator<(const _self& rhs) const noexcept {
            return _col == rhs._col ? _row < rhs._row : _col < rhs._col;
        }

        constexpr bool operator<(const _const_it& rhs) const noexcept {
            return _col == rhs._col ? _row < rhs._row : _col < rhs._col;
        }

        constexpr bool operator>(const _self& rhs) const noexcept {
            return rhs < *this;
        }

        constexpr bool operator>(const _const_it& rhs) const noexcept {
            return rhs < *this;
        }

        constexpr bool operator<=(const _self& rhs) const noexcept {
            return _col == rhs._col ? _row <= rhs._row : _col < rhs._col;
        }

        constexpr bool operator<=(const _const_it& rhs) const noexcept {
            return _col == rhs._col ? _row <= rhs._row : _col < rhs._col;
        }

        constexpr bool operator>=(const _self& rhs) const noexcept {
            return rhs <= *this;
        }

        constexpr bool operator>=(const _const_it& rhs) const noexcept {
            return rhs <= *this;
        }

    private:
        index_t _row;
        index_t _col;
        pointer _ptr;
    };

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    constexpr matrix_col_iterator<NumericType, Rows, Cols, OnStack>&
    matrix_col_iterator<NumericType, Rows, Cols, OnStack>::operator+=(
            matrix_col_iterator<NumericType, Rows, Cols, OnStack>::difference_type n
    ) noexcept {
        _ptr -= _row * Cols + _col;
        auto new_pos = _col * Rows + _row + n;
        _row = new_pos % Rows;
        _col = new_pos / Rows;
        if (_row < 0) {
            --_col;
            _row += Rows;
        }
        _ptr += _row * Cols + _col;
        return *this;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    constexpr inline matrix_col_iterator<NumericType, Rows, Cols, OnStack>
    operator+(typename matrix_col_iterator<NumericType, Rows, Cols, OnStack>::difference_type n,
              matrix_col_iterator<NumericType, Rows, Cols, OnStack> it) noexcept {
        return it + n;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    class matrix_const_col_iterator {
        static_assert(Rows > 1 && Cols > 1, "invalid dimension");

        using _base = matrix<NumericType, Rows, Cols, OnStack>;
        using _self = matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>;
        using _it = matrix_col_iterator<NumericType, Rows, Cols, OnStack>;

        friend class matrix_col_iterator<NumericType, Rows, Cols, OnStack>;

    public:
        typedef typename _base::difference_type difference_type;
        typedef typename _base::value_type value_type;
        typedef typename _base::const_pointer pointer;
        typedef typename _base::const_reference reference;
        typedef std::random_access_iterator_tag iterator_category;

        constexpr matrix_const_col_iterator() : _row {0}, _col {0}, _ptr {nullptr} {}

        constexpr matrix_const_col_iterator(pointer ptr, index_t row, index_t col) noexcept
                : _row {row}, _col {col}, _ptr {ptr} {}

        constexpr reference operator*() const {
            return *_ptr;
        }

        constexpr pointer operator->() const noexcept {
            return _ptr;
        }

        constexpr _self& operator++() noexcept {
            if (_row + 1 == Rows) {
                _row = 0;
                ++_col;
                _ptr -= (Rows - 1) * Cols - 1;
            } else {
                ++_row;
                _ptr += Cols;
            }
            return *this;
        }

        constexpr const _self operator++(int) noexcept {
            _self tmp {*this};
            ++*this;
            return tmp;
        }

        constexpr _self& operator--() noexcept {
            if (_row == 0) {
                _row = Rows - 1;
                --_col;
                _ptr += (Rows - 1) * Cols - 1;
            } else {
                --_row;
                _ptr -= Cols;
            }
            return *this;
        }

        constexpr const _self operator--(int) noexcept {
            _self tmp {*this};
            --*this;
            return tmp;
        }

        constexpr bool operator==(const _self& rhs) const noexcept {
            return _ptr == rhs._ptr && _row == rhs._row && _col == rhs._col;
        }

        constexpr bool operator==(const _it& rhs) const noexcept {
            return rhs == *this;
        }

        constexpr bool operator!=(const _self& rhs) const noexcept {
            return !(*this == rhs);
        }

        constexpr bool operator!=(const _it& rhs) const noexcept {
            return !(*this == rhs);
        }

        constexpr _self& operator+=(difference_type n) noexcept;

        constexpr _self& operator-=(difference_type n) noexcept {
            return *this += -n;
        }

        constexpr _self operator+(difference_type n) const noexcept {
            _self tmp {*this};
            return tmp += n;
        }

        constexpr _self operator-(difference_type n) const noexcept {
            _self tmp {*this};
            return tmp -= n;
        }

        constexpr difference_type operator-(const _self& other) const noexcept {
            return (_col - other._col) * Rows + _row - other._row;
        }

        constexpr difference_type operator-(const _it& other) const noexcept {
            return (_col - other._col) * Rows + _row - other._row;
        }

        constexpr reference operator[](difference_type n) const {
            return *(*this + n);
        }

        constexpr bool operator<(const _self& rhs) const noexcept {
            return _col == rhs._col ? _row < rhs._row : _col < rhs._col;
        }

        constexpr bool operator<(const _it& rhs) const noexcept {
            return rhs > *this;
        }

        constexpr bool operator>(const _self& rhs) const noexcept {
            return rhs < *this;
        }

        constexpr bool operator>(const _it& rhs) const noexcept {
            return rhs < *this;
        }

        constexpr bool operator<=(const _self& rhs) const noexcept {
            return _col == rhs._col ? _row <= rhs._row : _col < rhs._col;
        }

        constexpr bool operator<=(const _it& rhs) const noexcept {
            return rhs >= *this;
        }

        constexpr bool operator>=(const _self& rhs) const noexcept {
            return rhs <= *this;
        }

        constexpr bool operator>=(const _it& rhs) const noexcept {
            return rhs <= *this;
        }

    private:
        index_t _row;
        index_t _col;
        pointer _ptr;
    };

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    constexpr matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>&
    matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>::operator+=(
            matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>::difference_type n
    ) noexcept {
        _ptr -= _row * Cols + _col;
        auto new_pos = _col * Rows + _row + n;
        _row = new_pos % Rows;
        _col = new_pos / Rows;
        if (_row < 0) {
            --_col;
            _row += Rows;
        }
        _ptr += _row * Cols + _col;
        return *this;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    constexpr inline matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>
    operator+(typename matrix_const_col_iterator<NumericType, Rows, Cols, OnStack>::difference_type n,
              matrix_const_col_iterator <NumericType, Rows, Cols, OnStack> it) noexcept {
        return it + n;
    }

    template <typename NumericType1, typename NumericType2, index_t Rows, index_t Cols, bool OnStack1, bool OnStack2>
    constexpr inline bool
    operator==(const matrix<NumericType1, Rows, Cols, OnStack1>& lhs,
               const matrix<NumericType2, Rows, Cols, OnStack2>& rhs) {
        return algo::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename NumericType1, typename NumericType2, index_t Rows, index_t Cols, bool OnStack1, bool OnStack2>
    constexpr inline bool
    operator!=(const matrix<NumericType1, Rows, Cols, OnStack1>& lhs,
               const matrix<NumericType2, Rows, Cols, OnStack2>& rhs) {
        return !(lhs == rhs);
    }

    template <typename NumericType1, typename NumericType2, index_t Rows, index_t Cols, bool OnStack1, bool OnStack2>
    constexpr inline matrix<NumericType1, Rows, Cols, OnStack1>
    operator+(const matrix<NumericType1, Rows, Cols, OnStack1>& m1,
              const matrix<NumericType2, Rows, Cols, OnStack2>& m2) {
        matrix<NumericType1, Rows, Cols, OnStack1> ret;
        algo::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                        [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a + b; });
        return ret;
    }

    template <typename NumericType1, typename NumericType2, index_t Rows, index_t Cols, bool OnStack1, bool OnStack2>
    constexpr inline matrix<NumericType1, Rows, Cols, OnStack1>
    operator-(const matrix<NumericType1, Rows, Cols, OnStack1>& m1,
              const matrix<NumericType2, Rows, Cols, OnStack2>& m2) {
        matrix<NumericType1, Rows, Cols, OnStack1> ret;
        algo::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
                        [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a - b; });
        return ret;
    }

    template <typename NumericType1, typename NumericType2,
            index_t Rows1, index_t Cols1, index_t Cols2, bool OnStack1, bool OnStack2>
    constexpr matrix<NumericType1, Rows1, Cols2, OnStack1>
    operator*(const matrix<NumericType1, Rows1, Cols1, OnStack1>& m1,
              const matrix<NumericType2, Cols1, Cols2, OnStack2>& m2) {
        matrix<NumericType1, Rows1, Cols2, OnStack1> ret {0};
        // TODO: optimize
        for (index_t i {0}; i < Rows1; ++i) {
            for (index_t j {0}; j < Cols2; ++j) {
                for (index_t k {0}; k < Cols1; ++k)
                    ret[i][j] += m1[i][k] * m2[k][j];
            }
        }
        return ret;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack, typename NumericType2>
    constexpr inline matrix<NumericType, Rows, Cols, OnStack>
    operator*(const matrix<NumericType, Rows, Cols, OnStack>& m, const NumericType2& number) {
        matrix<NumericType, Rows, Cols, OnStack> ret;
        algo::transform(m.begin(), m.end(), ret.begin(), [number](const NumericType& a) -> NumericType {
            return a * number;
        });
        return ret;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack, typename NumericType2>
    constexpr inline matrix<NumericType, Rows, Cols, OnStack>
    operator*(const NumericType2& number, const matrix<NumericType, Rows, Cols, OnStack>& m) {
        return m * number;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack, typename NumericType2>
    constexpr inline matrix<NumericType, Rows, Cols, OnStack>
    operator/(const matrix<NumericType, Rows, Cols, OnStack>& m, const NumericType2& number) {
        matrix<NumericType, Rows, Cols, OnStack> ret;
        algo::transform(m.begin(), m.end(), ret.begin(), [number](const NumericType& a) -> NumericType {
            return a / number;
        });
        return ret;
    }

    template <index_t Size, typename NumericType = double,
            bool OnStack = Size * Size * sizeof(NumericType) < _stack_threshold>
    constexpr matrix<NumericType, Size, Size, OnStack>
    make_identity(const NumericType& one = 1, const NumericType& zero = 0) noexcept(OnStack) {
        matrix<NumericType, Size, Size, OnStack> ret {zero};
        for (index_t i {0}; i < Size; ++i)
            ret[i][i] = one;
        return ret;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    std::ostream& operator<<(std::ostream& os, const matrix<NumericType, Rows, Cols, OnStack>& m) {
        for (index_t i {0}; i < Rows; ++i) {
            for (index_t j {0}; j < Cols; ++j)
                os << " " << m[i][j];
            os << '\n';
        }
        return os;
    }

    template <typename NumericType, index_t Rows, index_t Cols, bool OnStack>
    std::istream& operator>>(std::istream& is, matrix<NumericType, Rows, Cols, OnStack>& m) {
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
