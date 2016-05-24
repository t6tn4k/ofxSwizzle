#ifndef OFX_SWIZZLE_COMPARISON_HPP
#define OFX_SWIZZLE_COMPARISON_HPP

#include <algorithm>
#include <type_traits>
#include "./detail/is_vector.hpp"
#include "./begin.hpp"
#include "./end.hpp"

namespace ofxSwizzle {

namespace detail {

template <
    typename Vector,
    std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator==(Vector const& lhs, Vector const& rhs) -> bool
{
    return std::equal(
        ofxSwizzle::cbegin(lhs), ofxSwizzle::cend(lhs),
        ofxSwizzle::cbegin(rhs), ofxSwizzle::cend(rhs));
}

template <
    typename Vector,
    std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator!=(Vector const& lhs, Vector const& rhs) -> bool
{
    return !(lhs == rhs);
}

} // namespace detail

using ofxSwizzle::detail::operator==;
using ofxSwizzle::detail::operator!=;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_COMPARISON_HPP
