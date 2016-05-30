#ifndef OFX_SWIZZLE_LENGTH_HPP
#define OFX_SWIZZLE_LENGTH_HPP

#include <cmath>
#include <type_traits>
#include "./detail/is_vector.hpp"
#include "./dot.hpp"

namespace ofxSwizzle {

template <typename Vector, std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>>* = nullptr>
inline auto length(Vector&& vector) -> decltype(auto)
{
    using std::sqrt;
    return sqrt(ofxSwizzle::dot(vector, vector));
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_LENGTH_HPP
