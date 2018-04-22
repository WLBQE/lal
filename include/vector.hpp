#ifndef LAL_VECTOR_HPP
#define LAL_VECTOR_HPP

#include "matrix.hpp"

namespace lal {
    template <typename NumericType, index_t Size>
    class vector : public std::array<NumericType, Size> {
        
    };
}

#endif //LAL_VECTOR_HPP
