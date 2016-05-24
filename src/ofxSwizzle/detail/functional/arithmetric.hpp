#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_ARITHMETRIC_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_ARITHMETRIC_HPP

#include <utility>

namespace ofxSwizzle { namespace detail {

struct unary_plus
{
    template <typename T>
    constexpr auto operator()(T&& t) const -> decltype(+std::forward<T>(t))
    {
        return +std::forward<T>(t);
    }
};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_ARITHMETRIC_HPP
