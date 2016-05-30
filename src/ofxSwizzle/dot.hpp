#ifndef OFX_SWIZZLE_DOT_HPP
#define OFX_SWIZZLE_DOT_HPP

#include <iterator>
#include <numeric>
#include <utility>
#include "./detail/is_same_size.hpp"
#include "./arithmetric.hpp"
#include "./begin.hpp"
#include "./end.hpp"

namespace ofxSwizzle {

template <
    typename Lhs, typename Rhs,
    std::enable_if_t<ofxSwizzle::detail::is_same_size_v<Lhs, Rhs>>* = nullptr>
inline auto dot(Lhs&& lhs, Rhs&& rhs) -> decltype(auto)
{
    auto product = std::forward<Lhs>(lhs) * std::forward<Rhs>(rhs);
    return std::accumulate(
        ++std::make_move_iterator(ofxSwizzle::begin(product)),
        std::make_move_iterator(ofxSwizzle::end(product)),
        product[0]);
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_DOT_HPP
