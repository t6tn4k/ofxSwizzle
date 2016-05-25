#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_HYPERBOLIC_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_HYPERBOLIC_HPP

#include <cmath>
#include <utility>

namespace ofxSwizzle { namespace detail {

namespace math {

using std::sinh;
using std::cosh;
using std::tanh;
using std::asinh;
using std::acosh;
using std::atanh;

struct call_sinh
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(sinh(std::forward<T>(t)))
    {
        return sinh(std::forward<T>(t));
    }
};

struct call_cosh
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(cosh(std::forward<T>(t)))
    {
        return cosh(std::forward<T>(t));
    }
};

struct call_tanh
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(tanh(std::forward<T>(t)))
    {
        return tanh(std::forward<T>(t));
    }
};

struct call_asinh
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(asinh(std::forward<T>(t)))
    {
        return asinh(std::forward<T>(t));
    }
};

struct call_acosh
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(acosh(std::forward<T>(t)))
    {
        return acosh(std::forward<T>(t));
    }
};

struct call_atanh
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(atanh(std::forward<T>(t)))
    {
        return atanh(std::forward<T>(t));
    }
};

} // namespace math

using ofxSwizzle::detail::math::call_sinh;
using ofxSwizzle::detail::math::call_cosh;
using ofxSwizzle::detail::math::call_tanh;
using ofxSwizzle::detail::math::call_asinh;
using ofxSwizzle::detail::math::call_acosh;
using ofxSwizzle::detail::math::call_atanh;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_HYPERBOLIC_HPP
