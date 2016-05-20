#ifndef OFX_SWIZZLE_DETAIL_FWD_HPP
#define OFX_SWIZZLE_DETAIL_FWD_HPP

#include <cstddef>

namespace ofxSwizzle { namespace detail {

template <typename T, std::size_t N>
class vec;

template <typename T, std::size_t N, typename Indices, bool IsAssignable>
class swizzle_proxy;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FWD_HPP
