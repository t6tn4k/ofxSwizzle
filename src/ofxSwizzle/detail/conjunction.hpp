#ifndef OFX_SWIZZLE_DETAIL_CONJUNCTION_HPP
#define OFX_SWIZZLE_DETAIL_CONJUNCTION_HPP

#include <type_traits>
#include <utility>

namespace ofxSwizzle { namespace detail {

template <typename... Ts>
struct conjunction
    : std::is_same<
        std::integer_sequence<bool, Ts::value...>,
        std::integer_sequence<bool, ((void)Ts::value, true)...>>
{};

template <typename... Ts>
constexpr auto conjunction_v = ofxSwizzle::detail::conjunction<Ts...>::value;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_CONJUNCTION_HPP
