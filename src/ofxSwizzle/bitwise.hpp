#ifndef OFX_SWIZZLE_BITWISE_HPP
#define OFX_SWIZZLE_BITWISE_HPP

#include <functional>
#include <type_traits>
#include <utility>
#include "./detail/binary_function_impl.hpp"
#include "./detail/functional/bitwise.hpp"
#include "./detail/is_vector.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator~(Vector&& vector) -> decltype(auto)
{
    return ofxSwizzle::apply(std::bit_not<>(), std::forward<Vector>(vector));
}

template <typename Lhs, typename Rhs>
inline auto operator&(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::bit_and<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::bit_and<>());
}

template <typename Lhs, typename Rhs>
inline auto operator|(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::bit_or<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::bit_or<>());
}

template <typename Lhs, typename Rhs>
inline auto operator^(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::bit_xor<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::bit_xor<>());
}

template <typename Lhs, typename Rhs>
inline auto operator<<(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_left()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_left());
}

template <typename Lhs, typename Rhs>
inline auto operator>>(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_right()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_right());
}

} // namespace detail

using ofxSwizzle::detail::operator~;
using ofxSwizzle::detail::operator&;
using ofxSwizzle::detail::operator|;
using ofxSwizzle::detail::operator^;
using ofxSwizzle::detail::operator<<;
using ofxSwizzle::detail::operator>>;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_BITWISE_HPP
