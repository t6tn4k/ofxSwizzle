#ifndef OFX_SWIZZLE_DISTANCE_HPP
#define OFX_SWIZZLE_DISTANCE_HPP

#include <type_traits>
#include <utility>
#include "./detail/is_same_size.hpp"
#include "./length.hpp"

namespace ofxSwizzle {

template <
    typename From, typename To,
    std::enable_if_t<ofxSwizzle::detail::is_same_size_v<From, To>>* = nullptr>
inline auto distance(From&& from, To&& to) -> decltype(auto)
{
    return ofxSwizzle::length(std::forward<To>(to) - std::forward<From>(from));
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_DISTANCE_HPP
