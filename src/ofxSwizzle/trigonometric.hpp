#ifndef OFX_SWIZZLE_TRIGONOMETRIC_HPP
#define OFX_SWIZZLE_TRIGONOMETRIC_HPP

#include <utility>
#include "./detail/functional/trigonometric.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector>
inline auto sin(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_sin(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_sin(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto cos(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_cos(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_cos(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto tan(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_tan(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_tan(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto asin(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_asin(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_asin(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto acos(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_acos(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_acos(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto atan(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_atan(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_atan(), std::forward<Vector>(vector));
}

} // namespace detail

using ofxSwizzle::detail::sin;
using ofxSwizzle::detail::cos;
using ofxSwizzle::detail::tan;
using ofxSwizzle::detail::asin;
using ofxSwizzle::detail::acos;
using ofxSwizzle::detail::atan;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_TRIGONOMETRIC_HPP
