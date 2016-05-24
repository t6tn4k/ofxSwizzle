#ifndef OFX_SWIZZLE_DETAIL_IS_SAME_VALUE_TYPE_HPP
#define OFX_SWIZZLE_DETAIL_IS_SAME_VALUE_TYPE_HPP

#include <type_traits>
#include "./vector_traits.hpp"

namespace ofxSwizzle { namespace detail {

namespace {

template <typename Lhs, typename Rhs>
auto is_same_value_type_impl(...) -> std::false_type;

template <typename Lhs, typename Rhs>
auto is_same_value_type_impl(std::nullptr_t)
    -> std::is_same<
        typename ofxSwizzle::detail::vector_traits<Lhs>::value_type,
        typename ofxSwizzle::detail::vector_traits<Rhs>::value_type>;

} // namespace <unnamed>

template <typename Lhs, typename Rhs>
struct is_same_value_type
    : decltype(ofxSwizzle::detail::is_same_value_type_impl<Lhs, Rhs>(nullptr))
{};

template <typename Lhs, typename Rhs>
constexpr auto is_same_value_type_v = ofxSwizzle::detail::is_same_value_type<Lhs, Rhs>::value;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_IS_SAME_VALUE_TYPE_HPP
