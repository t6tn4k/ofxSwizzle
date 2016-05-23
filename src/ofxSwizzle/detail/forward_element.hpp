#ifndef OFX_SWIZZLE_DETAIL_FORWARD_ELEMENT_HPP
#define OFX_SWIZZLE_DETAIL_FORWARD_ELEMENT_HPP

#include <type_traits>
#include <utility>
#include "./vector_traits.hpp"

namespace ofxSwizzle { namespace detail { namespace {

template <typename Vector, std::size_t Index>
inline constexpr auto forward_element(std::remove_reference_t<Vector>& vector)
    -> std::enable_if_t<
        ofxSwizzle::detail::vector_traits<Vector>::has_duplicated_index,
        decltype(vector[Index])>
{
    return vector[Index];
}

template <typename Vector, std::size_t Index>
inline constexpr auto forward_element(std::remove_reference_t<Vector>&& vector)
    -> std::enable_if_t<
        ofxSwizzle::detail::vector_traits<Vector>::has_duplicated_index,
        decltype(vector[Index])>
{
    return vector[Index];
}

template <typename Vector, std::size_t Index>
inline constexpr auto forward_element(std::remove_reference_t<Vector>& vector)
    -> std::enable_if_t<
        !ofxSwizzle::detail::vector_traits<Vector>::has_duplicated_index,
        decltype(std::forward<Vector>(vector)[Index])>
{
    return std::forward<Vector>(vector)[Index];
}

template <typename Vector, std::size_t Index>
inline constexpr auto forward_element(std::remove_reference_t<Vector>&& vector)
    -> std::enable_if_t<
        !ofxSwizzle::detail::vector_traits<Vector>::has_duplicated_index,
        decltype(std::forward<Vector>(vector)[Index])>
{
    return std::forward<Vector>(vector)[Index];
}

} } } // namespace ofxSwizzle::detail::<unnamed>

#endif // #ifndef OFX_SWIZZLE_DETAIL_FORWARD_ELEMENT_HPP
