#ifndef OFX_SWIZZLE_BEGIN_HPP
#define OFX_SWIZZLE_BEGIN_HPP

#include <iterator>
#include <utility>

namespace ofxSwizzle {

template <typename T>
inline auto begin(T&& t) -> decltype(std::begin(std::forward<T>(t)))
{
    return std::begin(std::forward<T>(t));
}

template <typename T>
inline auto begin(T&& t) -> decltype(std::forward<T>(t).getPtr())
{
    return std::forward<T>(t).getPtr();
}

template <typename T>
inline auto cbegin(T const& t) -> decltype(t.cbegin())
{
    return t.cbegin();
}

template <typename T>
inline auto cbegin(T const& t) -> decltype(t.getPtr())
{
    return t.getPtr();
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_BEGIN_HPP
