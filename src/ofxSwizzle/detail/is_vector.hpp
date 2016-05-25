#ifndef OFX_SWIZZLE_DETAIL_IS_VECTOR
#define OFX_SWIZZLE_DETAIL_IS_VECTOR

#include <type_traits>
#include "./vector_traits.hpp"

namespace ofxSwizzle { namespace detail {

template <typename T>
struct is_vector
    : std::integral_constant<bool,
        ofxSwizzle::detail::vector_traits<T>::is_vector>
{};

template <typename T>
constexpr auto is_vector_v = ofxSwizzle::detail::is_vector<T>::value;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_IS_VECTOR
