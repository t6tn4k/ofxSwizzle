#ifndef OFX_SWIZZLE_DETAIL_UNPACK_HPP
#define OFX_SWIZZLE_DETAIL_UNPACK_HPP

#include <type_traits>
#include "./conjunction.hpp"

namespace ofxSwizzle { namespace detail {

struct unpack
{
    template <typename... Ts>
    constexpr unpack(Ts&&...) {}
};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_UNPACK_HPP
