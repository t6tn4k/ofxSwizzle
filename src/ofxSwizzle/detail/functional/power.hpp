#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_POWER_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_POWER_HPP

#include <cmath>
#include <utility>

namespace ofxSwizzle { namespace detail {

namespace math {

using std::pow;
using std::sqrt;
using std::cbrt;
using std::hypot;

struct call_pow
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(pow(std::forward<T>(t), std::forward<U>(u)))
    {
        return pow(std::forward<T>(t), std::forward<U>(u));
    }
};

struct call_sqrt
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(sqrt(std::forward<T>(t)))
    {
        return sqrt(std::forward<T>(t));
    }
};

struct call_cbrt
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(cbrt(std::forward<T>(t)))
    {
        return cbrt(std::forward<T>(t));
    }
};

struct call_hypot
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(hypot(std::forward<T>(t), std::forward<U>(u)))
    {
        return hypot(std::forward<T>(t), std::forward<U>(u));
    }
};

} // namespace math

using ofxSwizzle::detail::math::call_pow;
using ofxSwizzle::detail::math::call_sqrt;
using ofxSwizzle::detail::math::call_cbrt;
using ofxSwizzle::detail::math::call_hypot;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_POWER_HPP
