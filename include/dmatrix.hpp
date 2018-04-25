#ifndef LAL_DMATRIX_HPP
#define LAL_DMATRIX_HPP

#include <algorithm>
#include <vector>
#include <limits>
#include <memory>
#include <iostream>
#include <iterator>

#include "basics.hpp"
#include "matrix.hpp"
#include "iterators.hpp"

namespace lal {
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

        dynamic_matrix() : _base {} , _cols {0} {}

        dynamic_matrix(index_t rows, index_t cols, const NumericType& val = 0) :
                _base {rows, _row_type {cols, val}}, _cols {cols} {}

        template <typename NumericType2, index_t Rows, index_t Cols, bool OnStack>
        explicit dynamic_matrix(const matrix<NumericType2, Rows, Cols, OnStack>& other) :
                _base {Rows, _row_type {Cols}}, _cols {Cols} {
            std::transform(other.begin(), other.end(), begin(), [](const NumericType2& val) -> NumericType {
                return val;
            });
        }

        template <typename NumericType2>
        explicit dynamic_matrix(const dynamic_matrix<NumericType2>& other) :
                _base {other.rows(), _row_type {other.cols()}}, _cols {other.cols()} {
            std::transform(other.begin(), other.end(), begin(), [](const NumericType2& val) -> NumericType {
                return val;
            });
        }

        pointer operator[](index_t idx) {
            return _base[idx].data();
        }

        const_pointer operator[](index_t idx) const {
            return _base[idx].data();
        }

        reference at(index_t row, index_t col) {
            if (row >= rows() || col >= cols())
                throw std::out_of_range("index out of range");
            return _base[row][col];
        }

        const_reference at(index_t row, index_t col) const {
            if (row >= rows() || col >= cols())
                throw std::out_of_range("index out of range");
            return _base[row][col];
        }

        index_t rows() const {
            return _base.size();
        }

        index_t cols() const {
            return _cols;
        }

        size_t size() const {
            return rows() * cols();
        }

        constexpr size_t max_size() const {
            return static_cast<size_t>(std::numeric_limits<difference_type>::max());
        }

        void insertRow(const std::vector<NumericType>& _row){
            if((*_base)[0].size()!=_row.size()){
                throw std::logic_error("Row size mismatch error");
                return ;
            }
            (*_base).push_back(_row);
            return ;
        }

        void insertColumn(const std::vector<NumericType>& _column){
            if((*_base).size()!=_column.size()){
                throw std::logic_error("Column size mismatch error");
                return ;
            }
            std::transform((*_base).begin(), (*_base).end(), _column.begin(), (*_base).begin(), [&](std::vector<NumericType>& _row, NumericType newValue)->std::vector<NumericType>&{
                _row.push_back(newValue);
                return _row;});
        }

        void deleteRow(index_t _rowId){
            if((*_base).size()<=_rowId){
                throw std::out_of_range("Row id out of range");
            }
            (*_base).erase(begin()+_rowId);
            return ;
        }

        void deleteCol(index_t _colId){
            if((*_base)[0].size()<=_colId){
                throw std::out_of_range("Column id out of range");
            }

            std::for_each(begin(), end(), [&](std::vector<NumericType>& _row){
                _row.erase(_row.begin()+_colId);
            });
            return ;
        }

    };
}

#endif // LAL_DMATRIX_HPP
