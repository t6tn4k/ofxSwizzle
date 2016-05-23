#ifndef OFX_SWIZZLE_DATA_HPP
#define OFX_SWIZZLE_DATA_HPP

#include <type_traits>
#include <utility>

namespace ofxSwizzle {

template <typename T>
inline auto data(T&& t) -> decltype(std::forward<T>(t).data())
{
    return std::forward<T>(t).data();
}

template <typename T>
inline auto data(T&& t) -> decltype(std::forward<T>(t).getPtr())
{
    return std::forward<T>(t).getPtr();
}

template <typename T>
inline auto cdata(T const& t) -> decltype(t.data())
{
    return t.data();
}

template <typename T>
inline auto cdata(T const& t) -> decltype(t.getPtr())
{
    return t.getPtr();
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_DATA_HPP
