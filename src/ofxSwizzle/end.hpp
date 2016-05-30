#ifndef OFX_SWIZZLE_END_HPP
#define OFX_SWIZZLE_END_HPP

#include <iterator>
#include <utility>

namespace ofxSwizzle {

template <typename T>
inline auto end(T&& t) -> decltype(std::end(std::forward<T>(t)))
{
    return std::end(std::forward<T>(t));
}

template <typename T>
inline auto end(T&& t) -> decltype(std::forward<T>(t).getPtr())
{
    return std::forward<T>(t).getPtr() + t.DIM;
}

template <typename T>
inline auto cend(T const& t) -> decltype(std::cend(t))
{
    return std::cend(t);
}

template <typename T>
inline auto cend(T const& t) -> decltype(t.getPtr() + t.DIM)
{
    return t.getPtr() + t.DIM;
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_END_HPP
