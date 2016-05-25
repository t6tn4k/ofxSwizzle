#ifndef OFX_SWIZZLE_EXPONENTIAL_HPP
#define OFX_SWIZZLE_EXPONENTIAL_HPP

#include <utility>
#include "./detail/functional/exponential.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector>
inline auto exp(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_exp(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_exp(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto exp2(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_exp2(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_exp2(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto expm1(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_expm1(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_expm1(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto log(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_log(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_log(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto log10(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_log10(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_log10(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto log2(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_log2(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_log2(), std::forward<Vector>(vector));
}

template <typename Vector>
inline auto log1p(Vector&& vector)
    -> decltype(ofxSwizzle::apply(ofxSwizzle::detail::call_log1p(), std::forward<Vector>(vector)))
{
    return ofxSwizzle::apply(ofxSwizzle::detail::call_log1p(), std::forward<Vector>(vector));
}

} // namespace detail

using ofxSwizzle::detail::exp;
using ofxSwizzle::detail::exp2;
using ofxSwizzle::detail::expm1;
using ofxSwizzle::detail::log;
using ofxSwizzle::detail::log10;
using ofxSwizzle::detail::log2;
using ofxSwizzle::detail::log1p;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_EXPONENTIAL_HPP
