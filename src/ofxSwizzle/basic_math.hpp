#ifndef OFX_SWIZZLE_BASIC_MATH_HPP
#define OFX_SWIZZLE_BASIC_MATH_HPP

#include <utility>
#include "./detail/binary_function_impl.hpp"
#include "./detail/functional/basic_math.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector>
inline auto abs(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_abs(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_abs(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto fabs(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_fabs(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_fabs(), std::forward<Vector>(vector));
}

template <typename Lhs, typename Rhs>
inline auto fmod(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fmod(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fmod(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto remainder(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_remainder(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_remainder(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto fmax(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fmax(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fmax(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto fmin(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fmin(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fmin(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Lhs, typename Rhs>
inline auto fdim(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fdim(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_fdim(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

} // namespace detail

using ofxSwizzle::detail::abs;
using ofxSwizzle::detail::fabs;
using ofxSwizzle::detail::fmod;
using ofxSwizzle::detail::remainder;
using ofxSwizzle::detail::fmax;
using ofxSwizzle::detail::fmin;
using ofxSwizzle::detail::fdim;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_BASIC_MATH_HPP
