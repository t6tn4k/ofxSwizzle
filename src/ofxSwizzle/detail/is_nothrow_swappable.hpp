#ifndef OFX_SWIZZLE_DETAIL_IS_NOTHROW_SWAPPABLE_HPP
#define OFX_SWIZZLE_DETAIL_IS_NOTHROW_SWAPPABLE_HPP

#include <type_traits>
#include <utility>

namespace ofxSwizzle { namespace detail {

namespace {

template <typename T, typename U>
constexpr auto is_nothrow_swappable_with_impl() noexcept
{
    using std::swap;
    return noexcept(swap(std::declval<T&>(), std::declval<U&>()));
}

} // namespace <unnamed>

template <typename T, typename U>
struct is_nothrow_swappable_with
    : std::integral_constant<bool,
        ofxSwizzle::detail::is_nothrow_swappable_with_impl<T, U>()>
{};

template <typename T>
using is_nothrow_swappable = ofxSwizzle::detail::is_nothrow_swappable_with<T, T>;

template <typename T, typename U>
constexpr auto is_nothrow_swappable_with_v
    = ofxSwizzle::detail::is_nothrow_swappable_with<T, U>::value;

template <typename T>
constexpr auto is_nothrow_swappable_v
    = ofxSwizzle::detail::is_nothrow_swappable<T>::value;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_IS_NOTHROW_SWAPPABLE_HPP
