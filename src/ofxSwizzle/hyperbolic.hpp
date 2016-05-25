#ifndef OFX_SWIZZLE_HYPERBOLIC_HPP
#define OFX_SWIZZLE_HYPERBOLIC_HPP

#include <utility>
#include "./detail/functional/hyperbolic.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector>
inline auto sinh(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_sinh(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_sinh(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto cosh(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_cosh(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_cosh(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto tanh(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_tanh(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_tanh(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto asinh(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_asinh(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_asinh(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto acosh(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_acosh(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_acosh(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto atanh(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_atanh(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_atanh(), std::forward<Vector>(vector));
}

} // namespace detail

using ofxSwizzle::detail::sinh;
using ofxSwizzle::detail::cosh;
using ofxSwizzle::detail::tanh;
using ofxSwizzle::detail::asinh;
using ofxSwizzle::detail::acosh;
using ofxSwizzle::detail::atanh;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_HYPERBOLIC_HPP
