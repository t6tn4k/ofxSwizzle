#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_INCREMENT_DECREMENT_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_INCREMENT_DECREMENT_HPP

#include <utility>

namespace ofxSwizzle { namespace detail {

struct pre_increment
{
    template <typename T>
    constexpr auto operator()(T&& t) const -> decltype(++std::forward<T>(t))
    {
        return ++std::forward<T>(t);
    }
};

struct post_increment
{
    template <typename T>
    constexpr auto operator()(T&& t, int) const -> decltype(std::forward<T>(t)++)
    {
        return std::forward<T>(t)++;
    }
};

struct pre_decrement
{
    template <typename T>
    constexpr auto operator()(T&& t) const -> decltype(--std::forward<T>(t))
    {
        return --std::forward<T>(t);
    }
};

struct post_decrement
{
    template <typename T>
    constexpr auto operator()(T&& t, int) const -> decltype(std::forward<T>(t)--)
    {
        return std::forward<T>(t)--;
    }
};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_INCREMENT_DECREMENT_HPP
