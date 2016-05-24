#ifndef OFX_SWIZZLE_APPLY_HPP
#define OFX_SWIZZLE_APPLY_HPP

#include <type_traits>
#include <utility>
#include "./detail/forward_element.hpp"
#include "./detail/is_same_size.hpp"
#include "./detail/is_vector.hpp"
#include "./detail/vector_traits.hpp"
#include "./make_vector.hpp"

namespace ofxSwizzle {

namespace detail { namespace {

template <typename F, typename Vector, std::size_t... Indices>
inline auto apply_impl(
    F const& f, Vector&& vector, std::index_sequence<Indices...> const&) -> decltype(auto)
{
    return ofxSwizzle::make_vector(f(ofxSwizzle::detail::forward_element<Vector, Indices>(vector))...);
}

template <typename F, typename Lhs, typename Rhs, std::size_t... Indices>
inline auto apply_impl(
    F const& f, Lhs&& lhs, Rhs&& rhs, std::index_sequence<Indices...> const&) -> decltype(auto)
{
    return ofxSwizzle::make_vector(f(
        ofxSwizzle::detail::forward_element<Lhs, Indices>(lhs),
        ofxSwizzle::detail::forward_element<Rhs, Indices>(rhs))...);
}

} } // namespace detail::<unnamed>

template <typename F, typename Vector>
inline auto apply(F const& f, Vector&& vector)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Vector>,
        decltype(ofxSwizzle::detail::apply_impl(
            f, std::forward<Vector>(vector),
            std::make_index_sequence<ofxSwizzle::detail::vector_traits<Vector>::size>()))>
{
    return ofxSwizzle::detail::apply_impl(
        f, std::forward<Vector>(vector),
        std::make_index_sequence<ofxSwizzle::detail::vector_traits<Vector>::size>());
}

template <typename F, typename Lhs, typename Rhs>
inline auto apply(F const& f, Lhs&& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_same_size_v<Lhs, Rhs>,
        decltype(ofxSwizzle::detail::apply_impl(
            f, std::forward<Lhs>(lhs), std::forward<Rhs>(rhs),
            std::make_index_sequence<ofxSwizzle::detail::vector_traits<Lhs>::size>()))>
{
    return ofxSwizzle::detail::apply_impl(
        f, std::forward<Lhs>(lhs), std::forward<Rhs>(rhs),
        std::make_index_sequence<ofxSwizzle::detail::vector_traits<Lhs>::size>());
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_APPLY_HPP
