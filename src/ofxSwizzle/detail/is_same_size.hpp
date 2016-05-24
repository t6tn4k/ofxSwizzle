#ifndef OFX_SWIZZLE_DETAIL_IS_SAME_SIZE_HPP
#define OFX_SWIZZLE_DETAIL_IS_SAME_SIZE_HPP

#include <type_traits>
#include "./vector_traits.hpp"

namespace ofxSwizzle { namespace detail {

namespace {

template <typename Lhs, typename Rhs>
auto is_same_size_impl(...) -> std::false_type;

template <typename Lhs, typename Rhs>
auto is_same_size_impl(std::nullptr_t)
    -> std::integral_constant<bool,
        ofxSwizzle::detail::vector_traits<Lhs>::size
            == ofxSwizzle::detail::vector_traits<Rhs>::size>;

} // namespace <unnamed>

template <typename Lhs, typename Rhs>
struct is_same_size
    : decltype(ofxSwizzle::detail::is_same_size_impl<Lhs, Rhs>(nullptr))
{};

template <typename Lhs, typename Rhs>
constexpr auto is_same_size_v = ofxSwizzle::detail::is_same_size<Lhs, Rhs>::value;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_IS_SAME_SIZE_HPP
