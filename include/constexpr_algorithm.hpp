#ifndef LAL_CONSTEXPR_ALGORITHM_HPP
#define LAL_CONSTEXPR_ALGORITHM_HPP

namespace lal::algo {
    template <typename InputIt, typename OutputIt>
    constexpr OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
        for (; first != last; ++first, ++d_first)
            *d_first = *first;
        return d_first;
    }

    template <typename InputIt1, typename InputIt2>
    constexpr bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
        for (; first1 != last1; ++first1, ++first2) {
            if (*first1 != *first2)
                return false;
        }
        return true;
    }

    template <typename InputIt, typename OutputIt, typename UnaryOperation>
    constexpr OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op) {
        for (; first1 != last1; ++first1, ++d_first)
            *d_first = unary_op(*first1);
        return d_first;
    }

    template <typename InputIt1, typename InputIt2, typename OutputIt, typename BinaryOperation>
    constexpr OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                                 OutputIt d_first, BinaryOperation binary_op) {
        for (; first1 != last1; ++first1, ++first2, ++d_first)
            *d_first = binary_op(*first1, *first2);
        return d_first;
    }
}

#endif // LAL_CONSTEXPR_ALGORITHM_HPP