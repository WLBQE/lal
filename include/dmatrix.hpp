
#ifndef Header_h
#define Header_h

#ifndef LAL_DMATRIX_HPP
#define LAL_DMATRIX_HPP

#include <algorithm>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <iterator>
#include <type_traits>

namespace lal {
    
    typedef std::size_t index_t;
    
    
    template <typename NumericType>
    class matrix {
        
        using _atom_type = std::vector<NumericType>;
        
        using _base_type = std::vector<std::vector<NumericType>>;
        using _self = matrix<NumericType>;
        
        _base_type* _base;
        
    public:
        typedef typename _atom_type::value_type value_type;
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
        
        
        matrix() : _base {new _base_type()} {}
        
        
        explicit matrix(_base_type init) : _base { new _base_type(init)} {}
        
        
        explicit matrix(const size_type rows, const size_type cols, const value_type& val) : _base { new _base_type(rows, _atom_type(cols, val))} {
        }
        
        
        operator matrix<NumericType>() const noexcept {
            return matrix<NumericType> {*_base};
        }
        
        template <typename NumericType2>
        operator matrix<NumericType2>() const {
            matrix<NumericType2> ret;
            std::transform(begin(), end(), ret.begin(), [](const value_type& val) -> NumericType2 {
                return val;
            });
            return ret;
        }
        
        _atom_type& operator[](index_t idx) {
            return (*_base)[idx];
        }
        
        _atom_type operator[](index_t idx) const {
            return (*_base)[idx];
        }
        
        reference at(index_t row, index_t col) {
            if (row >= (*_base).size() || col >= (*_base)[0].size())
                throw std::out_of_range("index out of range");
            return (*_base)[row][col];
        }
        
        const_reference at(index_t row, index_t col) const{
            if (row >= (*_base).size() || col >= (*_base)[0].size())
                throw std::out_of_range("index out of range");
            return (*_base)[row][col];
        }
        
        iterator begin() noexcept {
            return (*_base).begin();
        }
        
        const_iterator begin() const noexcept {
            return (*_base).begin();
        }
        
        const_iterator cbegin() const noexcept {
            return (*_base).cbegin();
        }
        
        iterator end() noexcept {
            return (*_base).end();
        }
        
        const_iterator end() const noexcept {
            return (*_base).end();
        }
        
        const_iterator cend() const noexcept {
            return (*_base).cend();
        }
        
        reverse_iterator rbegin() noexcept {
            return (*_base).rbegin();
        }
        
        const_reverse_iterator rbegin() const noexcept {
            return (*_base).rbegin();
        }
        
        const_reverse_iterator crbegin() const noexcept {
            return (*_base).crbegin();
        }
        
        reverse_iterator rend() noexcept {
            return (*_base).rend();
        }
        
        const_reverse_iterator rend() const noexcept {
            return (*_base).rend();
        }
        
        const_reverse_iterator crend() const noexcept {
            return (*_base).crend();
        }
        /*
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
         */
        
        void swap(_self& other) noexcept {
            this->_base.swap(other._base);
        }
        
        
        size_type size() noexcept{
            return (*_base).size();
        }
        
        size_type size() const noexcept{
            return (*_base).size();
        }
        
        constexpr bool empty() const noexcept {
            return (*_base).size()==0;
        }
        
        _self& operator+=(matrix<NumericType>& m) {
            
            std::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType& b) -> NumericType { return a + b; });
            return *this;
        }
        
        template <typename NumericType2>
        _self& operator-=(matrix<NumericType2>& m) {
            std::transform(begin(), end(), m.begin(), begin(),
                           [](const NumericType& a, const NumericType2& b) -> NumericType { return a - b; });
            return *this;
        }
        
        template <typename NumericType2>
        _self& operator*=(const NumericType& number) {
            std::transform(begin(), end(), begin(), [number](const NumericType2& a) -> NumericType {
                return a * number;
            });
            return *this;
        }
        
        template <typename NumericType2>
        _self& operator/=(const NumericType& number) {
            std::transform(begin(), end(), begin(), [number](const NumericType2& a) -> NumericType {
                return a / number;
            });
            return *this;
        }
        
        template <typename NumericType2>
        _self& operator*=(matrix<NumericType2>& m) {
            *this = *this * m;
            return *this;
        }
        
        matrix<NumericType> transpose() const {
            matrix<NumericType> ret;
            std::copy(begin(), end(), ret.col_begin());
            return ret;
        }
    };
    
    
    template <typename NumericType1, typename NumericType2>
    constexpr inline bool
    operator==(const matrix<NumericType1>& lhs,
               const matrix<NumericType2>& rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    template <typename NumericType1, typename NumericType2>
    constexpr inline bool
    operator!=(const matrix<NumericType1>& lhs,
               const matrix<NumericType2>& rhs) {
        return !(lhs == rhs);
    }
    
    template <typename NumericType>
    std::ostream& operator<<(std::ostream& os, const matrix<NumericType>& m) {
        
        //std::cout<<"The row size is: "<<m.size()<<std::endl;
        //std::cout<<"The col size is: "<<m[0].size()<<std::endl;
        for (index_t i {0}; i < m.size(); ++i) {
            for (index_t j {0}; j < m[i].size(); ++j)
                os << " " << m[i][j];
            os << '\n';
        }
        return os;
    }
    
    template <typename NumericType>
    std::istream& operator>>(std::istream& is, matrix<NumericType>& m) {
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
    
    template <typename NumericType1, typename NumericType2>
    constexpr inline matrix<NumericType1>
    operator+(const matrix<NumericType1>& m1,
              const matrix<NumericType2>& m2) {
        
        if(m1.size()!=m2.size() || m1[0].size()!=m2[0].size()){
            throw std::out_of_range("Index does not match");
        }
        
        matrix<NumericType1> ret(m1.size(), m1[0].size(), 0);
        //std::cout<<"I am called here"<<std::endl;
        //std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
        //                [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a + b; });
        
        //std::transform(m1.begin(), m1.end(), m2.begin(), m2.end(),
        //            [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a + b; });
        
        
        // TODO change to transform
        for(index_t i {0}; i < ret.size(); i++){
            for(index_t j {0} ; j <  ret[i].size(); j++){
                ret[i][j] = m1[i][j]+m2[i][j];
            }
        }
        
        return ret;
    }
    
    template <typename NumericType1, typename NumericType2>
    constexpr inline matrix<NumericType1>
    operator-(const matrix<NumericType1>& m1,
              const matrix<NumericType2>& m2) {
        
        if(m1.size()!=m2.size() || m1[0].size()!=m2[0].size()){
            throw std::out_of_range("Index does not match");
        }
        
        matrix<NumericType1> ret(m1.size(), m1[0].size(), 0);
        //std::transform(m1.begin(), m1.end(), m2.begin(), ret.begin(),
        //                [](const NumericType1& a, const NumericType2& b) -> NumericType1 { return a - b; });
        
        for(index_t i {0}; i < ret.size(); i++){
            for(index_t j {0} ; j <  ret[i].size(); j++){
                ret[i][j] = m1[i][j]-m2[i][j];
            }
        }
        
        return ret;
    }
    
    template <typename NumericType1, typename NumericType2>
    constexpr matrix<NumericType1>
    operator*(const matrix<NumericType1>& m1,
              const matrix<NumericType2>& m2) {
        
        if(m1[0].size()!=m2.size()){
            throw std::out_of_range("Index does not match");
        }
        
        matrix<NumericType1> ret(m1.size(), m2[0].size(), 1);
        // TODO: optimize
        for (index_t i {0}; i < m1.size(); ++i) {
            for (index_t j {0}; j < m2[0].size(); ++j) {
                for (index_t k {0}; k < m1[0].size(); ++k)
                    ret[i][j] += m1[i][k] * m2[k][j];
            }
        }
        return ret;
    }
    
    template <typename NumericType, typename NumericType2>
    constexpr inline matrix<NumericType>
    operator*(const matrix<NumericType>& m, const NumericType2& number) {
        matrix<NumericType> ret(m.size(), m[0].size(), 0);
        //std::transform(m.begin(), m.end(), ret.begin(), [number](const NumericType2& a) -> NumericType {
        //    return a * number;
        //});
        
        for(index_t i {0}; i < m.size(); i++){
            for(index_t j {0}; j < m[0].size(); j++){
                ret[i][j] = m[i][j]*number;
            }
        }
        return ret;
    }
    
    template <typename NumericType, typename NumericType2>
    constexpr inline matrix<NumericType>
    operator*(const NumericType2& number, const matrix<NumericType>& m) {
        return m * number;
    }
    
    template <typename NumericType, typename NumericType2>
    constexpr inline matrix<NumericType>
    operator/(const matrix<NumericType>& m, const NumericType2& number) {
        matrix<NumericType> ret(m.size(), m[0].size(), 0);
        //std::transform(m.begin(), m.end(), ret.begin(), [number](const NumericType2& a) -> NumericType {
        //    return a * number;
        //});
        
        for(index_t i {0}; i < m.size(); i++){
            for(index_t j {0}; j < m[0].size(); j++){
                ret[i][j] = m[i][j]/number;
            }
        }
        return ret;
    }
    
    template <index_t Size, typename NumericType = double>
    constexpr matrix<NumericType>
    make_identity(const NumericType& one = 1, const NumericType& zero = 0) noexcept {
        matrix<NumericType> ret {zero};
        for (index_t i {0}; i < Size; ++i)
            ret[i][i] = one;
            return ret;
    }
}


#endif //LAL_DMATRIX_HPP
#endif /* Header_h */
