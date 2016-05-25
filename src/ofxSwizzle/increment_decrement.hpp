#ifndef OFX_SWIZZLE_ARITHMETRIC_HPP
#define OFX_SWIZZLE_ARITHMETRIC_HPP

#include <type_traits>
#include <utility>
#include "./detail/functional/increment_decrement.hpp"
#include "./detail/is_vector.hpp"
#include "./apply.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator++(Vector&& vector) -> decltype(auto)
{
    return ofxSwizzle::apply(ofxSwizzle::detail::pre_increment(), std::forward<Vector>(vector));
}

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator++(Vector&& vector, int) -> decltype(auto)
{
    return ofxSwizzle::apply(ofxSwizzle::detail::post_increment(), std::forward<Vector>(vector));
}

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator--(Vector&& vector) -> decltype(auto)
{
    return ofxSwizzle::apply(ofxSwizzle::detail::pre_decrement(), std::forward<Vector>(vector));
}

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator--(Vector&& vector, int) -> decltype(auto)
{
    return ofxSwizzle::apply(ofxSwizzle::detail::post_decrement(), std::forward<Vector>(vector));
}

} // namespace detail

using ofxSwizzle::detail::operator++;
using ofxSwizzle::detail::operator--;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_ARITHMETRIC_HPP
