#ifndef OFX_SWIZZLE_COMPARISON_HPP
#define OFX_SWIZZLE_COMPARISON_HPP

#include <algorithm>
#include <functional>
#include <type_traits>
#include "./detail/is_same_size.hpp"
#include "./detail/is_vector.hpp"
#include "./apply.hpp"
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

template <typename Lhs, typename Rhs>
inline auto equal_to(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::apply(
        std::equal_to<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::apply(
        std::equal_to<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto not_equal_to(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::apply(
        std::not_equal_to<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::apply(
        std::not_equal_to<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto less(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::apply(
        std::less<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::apply(
        std::less<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto less_equal(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::apply(
        std::less_equal<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::apply(
        std::less_equal<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto greater(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::apply(
        std::greater<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::apply(
        std::greater<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto greater_equal(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::apply(
        std::greater_equal<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::apply(
        std::greater_equal<>(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_COMPARISON_HPP
