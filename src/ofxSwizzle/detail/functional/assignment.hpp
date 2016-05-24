#ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_ASSIGNMENT_HPP
#define OFX_SWIZZLE_DETAIL_FUNCTIONAL_ASSIGNMENT_HPP

#include <utility>

namespace ofxSwizzle { namespace detail {

struct plus_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs += std::forward<Rhs>(rhs))
    {
        return lhs += std::forward<Rhs>(rhs);
    }
};

struct minus_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs -= std::forward<Rhs>(rhs))
    {
        return lhs -= std::forward<Rhs>(rhs);
    }
};

struct multiplies_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs *= std::forward<Rhs>(rhs))
    {
        return lhs *= std::forward<Rhs>(rhs);
    }
};

struct divides_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs /= std::forward<Rhs>(rhs))
    {
        return lhs /= std::forward<Rhs>(rhs);
    }
};

struct modulus_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs %= std::forward<Rhs>(rhs))
    {
        return lhs %= std::forward<Rhs>(rhs);
    }
};

struct bit_and_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs &= std::forward<Rhs>(rhs))
    {
        return lhs &= std::forward<Rhs>(rhs);
    }
};

struct bit_or_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs |= std::forward<Rhs>(rhs))
    {
        return lhs |= std::forward<Rhs>(rhs);
    }
};

struct bit_xor_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs ^= std::forward<Rhs>(rhs))
    {
        return lhs ^= std::forward<Rhs>(rhs);
    }
};

struct shift_left_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs <<= std::forward<Rhs>(rhs))
    {
        return lhs <<= std::forward<Rhs>(rhs);
    }
};

struct shift_right_assign
{
    template <typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs& lhs, Rhs&& rhs) const
        -> decltype(lhs >>= std::forward<Rhs>(rhs))
    {
        return lhs >>= std::forward<Rhs>(rhs);
    }
};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_FUNCTIONAL_ASSIGNMENT_HPP
