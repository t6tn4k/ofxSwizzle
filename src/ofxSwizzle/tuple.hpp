#ifndef OFX_SWIZZLE_TUPLE_HPP
#define OFX_SWIZZLE_TUPLE_HPP

#include <tuple>
#include <type_traits>
#include "./detail/fwd.hpp"
#include "./detail/has_duplicated.hpp"

namespace std {

template <typename T, std::size_t N>
struct tuple_size<ofxSwizzle::detail::vec<T, N>>
    : std::integral_constant<std::size_t, N>
{};

template <typename T, std::size_t N, typename Indices>
struct tuple_size<
    ofxSwizzle::detail::swizzle_proxy<
        T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())>>
    : std::integral_constant<std::size_t, Indices::size()>
{};

template <std::size_t Index, typename T, std::size_t N>
struct tuple_element<Index, ofxSwizzle::detail::vec<T, N>>
{
    static_assert(Index < N, "Index out of range");
    using type = T;
};

template <std::size_t Index, typename T, std::size_t N, typename Indices>
struct tuple_element<Index,
    ofxSwizzle::detail::swizzle_proxy<
        T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())>>
{
    static_assert(Index < Indices::size(), "Index out of range");
    using type = T;
};

template <std::size_t Index, typename T, std::size_t N>
inline auto get(ofxSwizzle::detail::vec<T, N>& vector) -> decltype(auto)
{
    static_assert(Index < N, "Index out of range");
    return vector[Index];
}

template <std::size_t Index, typename T, std::size_t N>
inline auto get(ofxSwizzle::detail::vec<T, N> const& vector) -> decltype(auto)
{
    static_assert(Index < N, "Index out of range");
    return vector[Index];
}

template <std::size_t Index, typename T, std::size_t N>
inline auto get(ofxSwizzle::detail::vec<T, N>&& vector) -> decltype(auto)
{
    static_assert(Index < N, "Index out of range");
    return std::move(vector[Index]);
}

template <std::size_t Index, typename T, std::size_t N, typename Indices>
inline auto get(
    ofxSwizzle::detail::swizzle_proxy<
        T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())>& vector)
    -> decltype(auto)
{
    static_assert(Index < Indices::size(), "Index out of range");
    return vector[Index];
}

template <std::size_t Index, typename T, std::size_t N, typename Indices>
inline auto get(
    ofxSwizzle::detail::swizzle_proxy<
        T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())> const& vector)
    -> decltype(auto)
{
    static_assert(Index < Indices::size(), "Index out of range");
    return vector[Index];
}

template <std::size_t Index, typename T, std::size_t N, typename Indices>
inline auto get(
    ofxSwizzle::detail::swizzle_proxy<
        T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())>&& vector)
    -> decltype(auto)
{
    static_assert(Index < Indices::size(), "Index out of range");
    return std::move(vector[Index]);
}

} // namespace std

namespace ofxSwizzle {

using std::tuple_size;
using std::tuple_element;
using std::get;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_TUPLE_HPP
