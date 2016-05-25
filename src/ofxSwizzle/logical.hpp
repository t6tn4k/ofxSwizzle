#ifndef OFX_SWIZZLE_LOGICAL_HPP
#define OFX_SWIZZLE_LOGICAL_HPP

#include <functional>
#include <type_traits>
#include <utility>
#include "./detail/binary_operator_impl.hpp"
#include "./detail/is_vector.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator!(Vector&& vector) -> decltype(auto)
{
    return ofxSwizzle::apply(std::logical_not<>(), std::forward<Vector>(vector));
}

template <typename Lhs, typename Rhs>
inline auto operator&&(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_operator_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::logical_and<>()))
{
    return ofxSwizzle::detail::binary_operator_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::logical_and<>());
}

template <typename Lhs, typename Rhs>
inline auto operator||(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_operator_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::logical_or<>()))
{
    return ofxSwizzle::detail::binary_operator_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::logical_or<>());
}

} // namespace detail

using ofxSwizzle::detail::operator!;
using ofxSwizzle::detail::operator&&;
using ofxSwizzle::detail::operator||;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_LOGICAL_HPP
