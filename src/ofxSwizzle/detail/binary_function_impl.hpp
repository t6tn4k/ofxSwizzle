#ifndef OFX_SWIZZLE_DETAIL_BINARY_FUNCTION_IMPL_HPP
#define OFX_SWIZZLE_DETAIL_BINARY_FUNCTION_IMPL_HPP

#include <functional>
#include <type_traits>
#include <utility>
#include "./is_same_size.hpp"
#include "./is_vector.hpp"
#include "../apply.hpp"

namespace ofxSwizzle { namespace detail { namespace {

template <
    typename Lhs, typename Rhs, typename F,
    std::enable_if_t<
        ofxSwizzle::detail::is_same_size_v<Lhs, Rhs>,
        decltype(void(std::declval<F const&>()(
            std::declval<Lhs&&>()[0], std::declval<Rhs&&>()[0])))>* = nullptr>
inline auto binary_function_impl(Lhs&& lhs, Rhs&& rhs, F const& f) -> decltype(auto)
{
    return ofxSwizzle::apply(f, std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

template <
    typename Lhs, typename Rhs, typename F,
    std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>
            && !ofxSwizzle::detail::is_vector_v<Rhs>,
        decltype(void(std::declval<F const&>()(
            std::declval<Lhs&&>()[0], std::declval<Rhs&&>())))>* = nullptr>
inline auto binary_function_impl(Lhs&& lhs, Rhs&& rhs, F const& f) -> decltype(auto)
{
    return ofxSwizzle::apply(
        std::bind(f, std::placeholders::_1, std::forward<Rhs>(rhs)),
        std::forward<Lhs>(lhs));
}

template <
    typename Lhs, typename Rhs, typename F,
    std::enable_if_t<
        !ofxSwizzle::detail::is_vector_v<Lhs>
            && ofxSwizzle::detail::is_vector_v<Rhs>,
        decltype(void(std::declval<F const&>()(
            std::declval<Lhs&&>(), std::declval<Rhs&&>()[0])))>* = nullptr>
inline auto binary_function_impl(Lhs&& lhs, Rhs&& rhs, F const& f) -> decltype(auto)
{
    return ofxSwizzle::apply(
        std::bind(f, std::forward<Lhs>(lhs), std::placeholders::_1),
        std::forward<Rhs>(rhs));
}

} } } // namespace ofxSwizzle::detail::<unnamed>

#endif // #ifndef OFX_SWIZZLE_DETAIL_BINARY_FUNCTION_IMPL_HPP
