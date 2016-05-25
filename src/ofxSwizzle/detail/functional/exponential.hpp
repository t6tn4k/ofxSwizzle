#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_EXPONENTIAL_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_EXPONENTIAL_HPP

#include <cmath>
#include <utility>

namespace ofxSwizzle { namespace detail {

namespace math {

using std::exp;
using std::exp2;
using std::expm1;
using std::log;
using std::log10;
using std::log2;
using std::log1p;

struct call_exp
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(exp(std::forward<T>(t)))
    {
        return exp(std::forward<T>(t));
    }
};

struct call_exp2
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(exp2(std::forward<T>(t)))
    {
        return exp2(std::forward<T>(t));
    }
};

struct call_expm1
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(expm1(std::forward<T>(t)))
    {
        return expm1(std::forward<T>(t));
    }
};

struct call_log
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(log(std::forward<T>(t)))
    {
        return log(std::forward<T>(t));
    }
};

struct call_log10
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(log10(std::forward<T>(t)))
    {
        return log10(std::forward<T>(t));
    }
};

struct call_log2
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(log2(std::forward<T>(t)))
    {
        return log2(std::forward<T>(t));
    }
};

struct call_log1p
{
    template <typename T>
    auto operator()(T&& t) const -> decltype(log1p(std::forward<T>(t)))
    {
        return log1p(std::forward<T>(t));
    }
};

} // namespace math

using ofxSwizzle::detail::math::call_exp;
using ofxSwizzle::detail::math::call_exp2;
using ofxSwizzle::detail::math::call_expm1;
using ofxSwizzle::detail::math::call_log;
using ofxSwizzle::detail::math::call_log10;
using ofxSwizzle::detail::math::call_log2;
using ofxSwizzle::detail::math::call_log1p;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_EXPONENTIAL_HPP
