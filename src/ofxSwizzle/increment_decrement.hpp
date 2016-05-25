#ifndef OFX_SWIZZLE_INCREMENT_DECREMENT_HPP
#define OFX_SWIZZLE_INCREMENT_DECREMENT_HPP

#include <type_traits>
#include <utility>
#include "./detail/functional/increment_decrement.hpp"
#include "./detail/is_vector.hpp"
#include "./apply.hpp"
#include "./for_each.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator++(Vector& vector) -> Vector&
{
    ofxSwizzle::for_each(vector, ofxSwizzle::detail::pre_increment());
    return vector;
}

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator++(Vector& vector, int) -> Vector
{
    return ofxSwizzle::apply(ofxSwizzle::detail::post_increment(), vector);
}

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator--(Vector& vector) -> Vector&
{
    ofxSwizzle::for_each(vector, ofxSwizzle::detail::pre_decrement());
    return vector;
}

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto operator--(Vector& vector, int) -> Vector
{
    return ofxSwizzle::apply(ofxSwizzle::detail::post_decrement(), vector);
}

} // namespace detail

using ofxSwizzle::detail::operator++;
using ofxSwizzle::detail::operator--;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_INCREMENT_DECREMENT_HPP
