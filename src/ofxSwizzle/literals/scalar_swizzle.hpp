#ifndef OFX_SWIZZLE_LITERALS_SCALAR_SWIZZLE_HPP
#define OFX_SWIZZLE_LITERALS_SCALAR_SWIZZLE_HPP

#include "../make_vector.hpp"

namespace ofxSwizzle { namespace literals {

inline auto operator""_xx(long double x) -> decltype(auto)
{
    return ofxSwizzle::make_vector(x, x);
}

inline auto operator""_xxx(long double x) -> decltype(auto)
{
    return ofxSwizzle::make_vector(x, x, x);
}

inline auto operator""_xxxx(long double x) -> decltype(auto)
{
    return ofxSwizzle::make_vector(x, x, x, x);
}

} } // namespace ofxSwizzle::literals

#endif // #ifndef OFX_SWIZZLE_LITERALS_SCALAR_SWIZZLE_HPP
