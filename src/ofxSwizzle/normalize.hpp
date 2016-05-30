#ifndef OFX_SWIZZLE_NORMALIZE_HPP
#define OFX_SWIZZLE_NORMALIZE_HPP

#include <type_traits>
#include <utility>
#include "./detail/is_vector.hpp"
#include "./length.hpp"

namespace ofxSwizzle {

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto normalize(Vector&& vector) -> decltype(auto)
{
    return vector / ofxSwizzle::length(vector);
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_NORMALIZE_HPP
