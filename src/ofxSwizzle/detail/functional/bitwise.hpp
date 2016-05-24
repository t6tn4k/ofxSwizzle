#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_BITWISE_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_BITWISE_HPP

#include <utility>

namespace ofxSwizzle { namespace detail {

struct shift_left
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs&& lhs, Rhs&& rhs) const
        -> decltype(std::forward<Lhs>(lhs) << std::forward<Rhs>(rhs))
    {
        return std::forward<Lhs>(lhs) << std::forward<Rhs>(rhs);
    }
};

struct shift_right
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs&& lhs, Rhs&& rhs) const
        -> decltype(std::forward<Lhs>(lhs) >> std::forward<Rhs>(rhs))
    {
        return std::forward<Lhs>(lhs) >> std::forward<Rhs>(rhs);
    }
};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_BITWISE_HPP
