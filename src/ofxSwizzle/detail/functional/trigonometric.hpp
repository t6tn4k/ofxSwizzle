#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_TRIGONOMETRIC_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_TRIGONOMETRIC_HPP

#include <cmath>
#include <utility>

namespace ofxSwizzle { namespace detail {

namespace math {

using std::sin;
using std::cos;
using std::tan;
using std::asin;
using std::acos;
using std::atan;
using std::atan2;

struct call_sin
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(sin(std::forward<T>(t)))
    {
        return sin(std::forward<T>(t));
    }
};

struct call_cos
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(cos(std::forward<T>(t)))
    {
        return cos(std::forward<T>(t));
    }
};

struct call_tan
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(tan(std::forward<T>(t)))
    {
        return tan(std::forward<T>(t));
    }
};

struct call_asin
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(asin(std::forward<T>(t)))
    {
        return asin(std::forward<T>(t));
    }
};

struct call_acos
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(acos(std::forward<T>(t)))
    {
        return acos(std::forward<T>(t));
    }
};

struct call_atan
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(atan(std::forward<T>(t)))
    {
        return atan(std::forward<T>(t));
    }
};

struct call_atan2
{
    template <typename T, typename U>
    auto operator()(T&& t, U&& u) const
        -> decltype(atan2(std::forward<T>(t), std::forward<U>(u)))
    {
        return atan2(std::forward<T>(t), std::forward<U>(u));
    }
};

} // namespace math

using ofxSwizzle::detail::math::call_sin;
using ofxSwizzle::detail::math::call_cos;
using ofxSwizzle::detail::math::call_tan;
using ofxSwizzle::detail::math::call_asin;
using ofxSwizzle::detail::math::call_acos;
using ofxSwizzle::detail::math::call_atan;
using ofxSwizzle::detail::math::call_atan2;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_TRIGONOMETRIC_HPP
