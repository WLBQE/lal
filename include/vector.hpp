#ifndef LAL_VECTOR_HPP
#define LAL_VECTOR_HPP

#include <array>
#include <iostream>
#include <stdexcept>

#include "basics.hpp"
#include "matrix.hpp"
#include "dmatrix.hpp"
#include "constexpr_algorithm.hpp"

namespace lal {
    template <typename NumericType, index_t Size>
    class vector{
        using _base_type = std::array<NumericType, Size>;
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

        constexpr vector() : _base() {}

        constexpr explicit vector(_base_type init) noexcept : _base(init) {}

        constexpr explicit vector(const value_type& val) noexcept;

        template <typename NumericType2, bool OnStack>
        constexpr explicit vector(const matrix<NumericType2, 1, Size, OnStack>& mat) noexcept(OnStack) : _base() {
            algo::copy(mat.begin(), mat.end(), begin());
        }

        constexpr reference operator[](index_t idx) {
            return _base[idx];
        }

        constexpr const_reference operator[](index_t idx) const {
            return _base[idx];
        }

        constexpr reference at(index_t idx) {
            if (idx > Size)
                throw std::out_of_range("index out of range");
            return _base[idx];
        }

        constexpr const_reference at(index_t idx) const {
            if (idx > Size)
                throw std::out_of_range("index out of range");
            return _base[idx];
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

        void swap(vector& other) noexcept {
            _base.swap(other._base);
        }

        constexpr size_type size() const noexcept {
            return Size;
        }

        constexpr size_type max_size() const noexcept {
            return Size;
        }

        constexpr bool empty() const noexcept {
            return Size == 0;
        }

        template <typename NumericType2>
        constexpr vector& operator+=(vector<NumericType2, Size>& v) {
            algo::transform(begin(), end(), v.begin(), begin(),
                            [](const NumericType& a, const NumericType2& b) -> NumericType { return a + b; });
            return *this;
        }

        template <typename NumericType2>
        constexpr vector& operator-=(vector<NumericType2, Size>& v) {
            algo::transform(begin(), end(), v.begin(), begin(),
                            [](const NumericType& a, const NumericType2& b) -> NumericType { return a - b; });
            return *this;
        }

        template <typename NumericType2>
        constexpr vector& operator*=(const NumericType2& num) {
            algo::transform(begin(), end(), begin(), [num](const NumericType& a) -> NumericType {
                return a * num;
            });
            return *this;
        }

        template <typename NumericType2>
        constexpr vector& operator/=(const NumericType2& num) {
            algo::transform(begin(), end(), begin(), [num](const NumericType& a) -> NumericType {
                return a / num;
            });
            return *this;
        }

        template <bool OnStack = Size * sizeof(NumericType) < _stack_threshold>
        constexpr matrix<NumericType, 1, Size, OnStack> to_matrix() const noexcept {
            return matrix<NumericType, 1, Size, OnStack> {_base};
        }

        template <bool OnStack = Size * sizeof(NumericType) < _stack_threshold>
        constexpr matrix<NumericType, Size, 1, OnStack> transpose() const noexcept {
            return matrix<NumericType, Size, 1, OnStack> {_base};
        }
    };

    template <typename NumericType, index_t Size>
    constexpr vector<NumericType, Size>::vector(const value_type& val) noexcept : _base {} {
        for (auto& v : _base)
            v = val;
    }

    template <typename NumericType1, typename NumericType2, index_t Size>
    constexpr inline bool operator==(const vector<NumericType1, Size>& lhs, const vector<NumericType2, Size>& rhs) {
        return algo::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename NumericType1, typename NumericType2, index_t Size>
    constexpr inline bool operator!=(const vector<NumericType1, Size>& lhs, const vector<NumericType2, Size>& rhs) {
        return !(lhs == rhs);
    }

    template <typename NumericType1, typename NumericType2, index_t Size>
    constexpr inline vector<NumericType1, Size>
    operator+(const vector<NumericType1, Size>& v1, const vector<NumericType2, Size>& v2) {
        vector<NumericType1, Size> ret;
        algo::transform(v1.begin(), v1.end(), v2.begin(), ret.begin(),
                        [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a + b; });
        return ret;
    }

    template <typename NumericType1, typename NumericType2, index_t Size>
    constexpr inline vector<NumericType1, Size>
    operator-(const vector<NumericType1, Size>& v1, const vector<NumericType2, Size>& v2) {
        vector<NumericType1, Size> ret;
        algo::transform(v1.begin(), v1.end(), v2.begin(), ret.begin(),
                        [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a - b; });
        return ret;
    }

    // Dot product
    template <typename NumericType1, typename NumericType2, index_t Size>
    constexpr NumericType1 operator*(const vector<NumericType1, Size>& v1, const vector<NumericType2, Size>& v2) {
        NumericType1 ret {0};
        auto it1 = v1.begin();
        auto it2 = v2.begin();
        for (; it1 != v1.end(); ++it1, ++it2)
            ret += *it1 * *it2;
        return ret;
    }

    // Cross product
    template <bool OnStack, typename NumericType1, typename NumericType2, index_t Size>
    constexpr square_matrix<NumericType1, Size, OnStack>
    vector_cross_product(const vector<NumericType1, Size>& v1, const vector<NumericType2, Size>& v2) {
        square_matrix<NumericType1, Size, OnStack> ret;
        for (index_t i {0}; i < Size; ++i) {
            for (index_t j {0}; j < Size; ++j)
                ret[i][j] = v1[i] * v2[j];
        }
        return ret;
    }

    template <typename NumericType1, typename NumericType2, index_t Size>
    constexpr inline square_matrix<NumericType1, Size>
    vector_cross_product(const vector<NumericType1, Size>& v1, const vector<NumericType2, Size>& v2) {
        constexpr bool on_stack = Size * Size * sizeof(NumericType1) < _stack_threshold;
        return vector_cross_product<on_stack>(v1, v2);
    }

    template <typename NumericType, index_t Size, typename NumericType2>
    constexpr inline vector<NumericType, Size>
    operator*(const vector<NumericType, Size>& v, const NumericType2& number) {
        vector<NumericType, Size> ret;
        algo::transform(v.begin(), v.end(), ret.begin(), [number](const NumericType& a) -> NumericType {
            return a * number;
        });
        return ret;
    }

    template <typename NumericType, index_t Size, typename NumericType2>
    constexpr inline vector<NumericType, Size>
    operator*(const NumericType2& number, const vector<NumericType, Size>& v) {
        return v * number;
    }

    template <typename NumericType1, index_t Size, typename NumericType2, index_t Cols, bool OnStack>
    constexpr inline vector<NumericType1, Cols>
    operator*(const vector<NumericType1, Size>& v, const matrix<NumericType2, Size, Cols, OnStack>& m) {
        vector<NumericType1, Cols> ret {0};
        auto it_ret = ret.begin();
        for (index_t i {0}; i < Cols; ++i, ++it_ret) {
            auto it_m = m.begin(i);
            auto it_v = v.begin();
            for (; it_v != v.end(); ++it_v, ++it_m)
                *it_ret += *it_v * *it_m;
        }
        return ret;
    }

    template <typename NumericType1, index_t Rows, typename NumericType2, index_t Size, bool OnStack>
    constexpr inline vector<NumericType1, Rows>
    operator*(const matrix<NumericType1, Rows, Size, OnStack>& m, const vector<NumericType2, Size>& v) {
        vector<NumericType1, Rows> ret {0};
        auto it_ret = ret.begin();
        for (index_t i {0}; i < Rows; ++i, ++it_ret) {
            auto it_m = m.begin(i);
            auto it_v = v.begin();
            for (; it_v != v.end(); ++it_m, ++it_v)
                *it_ret += *it_m * *it_v;
        }
        return ret;
    }

    template <typename NumericType, index_t Size, typename NumericType2>
    constexpr inline vector<NumericType, Size>
    operator/(const vector<NumericType, Size>& v, const NumericType2& number) {
        vector<NumericType, Size> ret;
        algo::transform(v.begin(), v.end(), ret.begin(), [number](const NumericType& a) -> NumericType {
            return a / number;
        });
        return ret;
    }

    template <typename NumericType, index_t Size>
    std::ostream& operator<<(std::ostream& os, const vector<NumericType, Size>& v) {
        for (auto& val : v)
            os << val << ' ';
        return os;
    }

    template <typename NumericType, index_t Size>
    std::istream& operator>>(std::istream& is, vector<NumericType, Size>& v) {
        for (auto& val : v) {
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

#endif //LAL_VECTOR_HPP
