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

inline auto operator""_xx(unsigned long long x) -> decltype(auto)
{
    return ofxSwizzle::literals::operator""_xx(static_cast<long double>(x));
}

inline auto operator""_xxx(unsigned long long x) -> decltype(auto)
{
    return ofxSwizzle::literals::operator""_xxx(static_cast<long double>(x));
}

inline auto operator""_xxxx(unsigned long long x) -> decltype(auto)
{
    return ofxSwizzle::literals::operator""_xxxx(static_cast<long double>(x));
}

} } // namespace ofxSwizzle::literals

#endif // #ifndef OFX_SWIZZLE_LITERALS_SCALAR_SWIZZLE_HPP
