#ifndef OFX_SWIZZLE_FOR_EACH_HPP
#define OFX_SWIZZLE_FOR_EACH_HPP

#include <type_traits>
#include <utility>
#include "./detail/forward_element.hpp"
#include "./detail/is_vector.hpp"
#include "./detail/is_same_size.hpp"
#include "./detail/vector_traits.hpp"
#include "./detail/unpack.hpp"

namespace ofxSwizzle {

namespace detail { namespace {

template <typename Vector, typename F, std::size_t... Indices>
inline auto for_each_impl(Vector&& vector, F const& f, std::index_sequence<Indices...> const&)
{
    ofxSwizzle::detail::unpack
    {
        (void(f(ofxSwizzle::detail::forward_element<Vector, Indices>(vector))), 0)...
    };
}

template <typename Lhs, typename Rhs, typename F, std::size_t... Indices>
inline auto for_each_impl(Lhs&& lhs, Rhs&& rhs, F const& f, std::index_sequence<Indices...> const&)
{
    ofxSwizzle::detail::unpack
    {
        (void(f(
            ofxSwizzle::detail::forward_element<Lhs, Indices>(lhs),
            ofxSwizzle::detail::forward_element<Rhs, Indices>(rhs))),
         0)...
    };
}

} } // namespace detail::<unnamed>

template <typename Vector, typename F>
auto for_each(Vector&& vector, F const& f)
    -> std::enable_if_t<ofxSwizzle::detail::is_vector_v<Vector>, F const&>
{
    ofxSwizzle::detail::for_each_impl(
        std::forward<Vector>(vector), f,
        std::make_index_sequence<ofxSwizzle::detail::vector_traits<Vector>::size>());
    return f;
}

template <typename Lhs, typename Rhs, typename F>
auto for_each(Lhs&& lhs, Rhs&& rhs, F const& f)
    -> std::enable_if_t<ofxSwizzle::detail::is_same_size_v<Lhs, Rhs>, F const&>
{
    ofxSwizzle::detail::for_each_impl(
        std::forward<Lhs>(lhs), std::forward<Rhs>(rhs), f,
        std::make_index_sequence<ofxSwizzle::detail::vector_traits<Lhs>::size>());
    return f;
}

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_FOR_EACH_HPP
