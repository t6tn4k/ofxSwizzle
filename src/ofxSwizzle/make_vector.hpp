#ifndef OFX_SWIZZLE_MAKE_VECTOR_HPP
#define OFX_SWIZZLE_MAKE_VECTOR_HPP

#include <type_traits>
#include <utility>
#include "./vec.hpp"

namespace ofxSwizzle {

template <typename... Ts>
inline auto make_vector(Ts&&... elems)
    -> ofxSwizzle::detail::vec<std::decay_t<std::common_type_t<Ts...>>, sizeof...(Ts)>
{
    return {std::forward<Ts>(elems)...};
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_MAKE_VECTOR_HPP
