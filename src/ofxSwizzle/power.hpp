#ifndef OFX_SWIZZLE_POWER_HPP
#define OFX_SWIZZLE_POWER_HPP

#include <utility>
#include "./detail/functional/power.hpp"
#include "./detail/binary_function_impl.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Lhs, typename Rhs>
inline auto pow(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_pow(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_pow(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <typename Vector>
inline auto sqrt(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_sqrt(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_sqrt(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto cbrt(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_cbrt(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_cbrt(), std::forward<Vector>(vector));
}

template <typename Lhs, typename Rhs>
inline auto hypot(Lhs&& lhs, Rhs&& rhs)
    -> decltype(ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_hypot(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs)))
{
    return ofxSwizzle::detail::binary_function_impl(
        ofxSwizzle::detail::call_hypot(), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

} // namespace detail

using ofxSwizzle::detail::pow;
using ofxSwizzle::detail::sqrt;
using ofxSwizzle::detail::cbrt;
using ofxSwizzle::detail::hypot;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_POWER_HPP
