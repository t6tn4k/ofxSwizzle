#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_BASIC_MATH_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_BASIC_MATH_HPP

#include <cmath>
#include <utility>

namespace ofxSwizzle { namespace detail {

namespace math {

using std::abs;
using std::fabs;
using std::fmod;
using std::remainder;
using std::fmax;
using std::fmin;
using std::fdim;

struct call_abs
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(abs(std::forward<T>(t)))
    {
        return abs(std::forward<T>(t));
    }
};

struct call_fabs
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(fabs(std::forward<T>(t)))
    {
        return fabs(std::forward<T>(t));
    }
};

struct call_fmod
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(fmod(std::forward<T>(t), std::forward<U>(u)))
    {
        return fmod(std::forward<T>(t), std::forward<U>(u));
    }
};

struct call_remainder
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(fmod(std::forward<T>(t), std::forward<U>(u)))
    {
        return fmod(std::forward<T>(t), std::forward<U>(u));
    }
};

struct call_fmax
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(fmod(std::forward<T>(t), std::forward<U>(u)))
    {
        return fmod(std::forward<T>(t), std::forward<U>(u));
    }
};

struct call_fmin
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(fmod(std::forward<T>(t), std::forward<U>(u)))
    {
        return fmod(std::forward<T>(t), std::forward<U>(u));
    }
};

struct call_fdim
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(fmod(std::forward<T>(t), std::forward<U>(u)))
    {
        return fmod(std::forward<T>(t), std::forward<U>(u));
    }
};

} // namespace math

using ofxSwizzle::detail::math::call_abs;
using ofxSwizzle::detail::math::call_fabs;
using ofxSwizzle::detail::math::call_fmod;
using ofxSwizzle::detail::math::call_remainder;
using ofxSwizzle::detail::math::call_fmax;
using ofxSwizzle::detail::math::call_fmin;
using ofxSwizzle::detail::math::call_fdim;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_BASIC_MATH_HPP
