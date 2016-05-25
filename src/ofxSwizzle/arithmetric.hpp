#ifndef OFX_SWIZZLE_ARITHMETRIC_HPP
#define OFX_SWIZZLE_ARITHMETRIC_HPP

#include <functional>
#include <type_traits>
#include <utility>
#include "./detail/binary_function_impl.hpp"
#include "./detail/functional/arithmetric.hpp"
#include "./detail/is_vector.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator+(Vector&& vector) -> decltype(auto)
{
    return ofxSwizzle::apply(ofxSwizzle::detail::unary_plus(), std::forward<Vector>(vector));
}

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator-(Vector&& vector) -> decltype(auto)
{
    return ofxSwizzle::apply(std::negate<>(), std::forward<Vector>(vector));
}

template <typename Lhs, typename Rhs>
inline auto operator+(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::plus<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::plus<>());
}

template <typename Lhs, typename Rhs>
inline auto operator-(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::minus<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::minus<>());
}

template <typename Lhs, typename Rhs>
inline auto operator*(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::multiplies<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::multiplies<>());
}

template <typename Lhs, typename Rhs>
inline auto operator/(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::divides<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::divides<>());
}

template <typename Lhs, typename Rhs>
inline auto operator%(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::modulus<>()))
{
    return ofxSwizzle::detail::binary_function_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), std::modulus<>());
}

} // namespace detail

using ofxSwizzle::detail::operator+;
using ofxSwizzle::detail::operator-;
using ofxSwizzle::detail::operator*;
using ofxSwizzle::detail::operator/;
using ofxSwizzle::detail::operator%;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_ARITHMETRIC_HPP
