#ifndef OFX_SWIZZLE_DETAIL_VECTOR_TRAITS_HPP
#define OFX_SWIZZLE_DETAIL_VECTOR_TRAITS_HPP

#include <cstddef>
#include <iterator>
#include "./fwd.hpp"
#include "./has_duplicated.hpp"

namespace ofxSwizzle { namespace detail {

template <typename Vector>
struct vector_traits
{
    static constexpr bool is_vector = false;
};

template <typename T, std::size_t N>
struct vector_traits<ofxSwizzle::detail::vec<T, N>>
{
    using vector_type = ofxSwizzle::detail::vec<T, N>;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;
    using iterator = T*;
    using const_iterator = T const*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    static constexpr size_type size = N;
    static constexpr size_type vector_size = size;
    using index_type = std::make_index_sequence<size>;
    static constexpr bool has_duplicated_index = false;
    static constexpr bool is_vector = true;
};

template <typename T, std::size_t N, typename Indices>
struct vector_traits<ofxSwizzle::detail::swizzle_proxy<
    T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())>>
{
    using vector_type = ofxSwizzle::detail::swizzle_proxy<
        T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())>;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;
    using iterator = T*;
    using const_iterator = T const*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    static constexpr size_type size = Indices::size();
    static constexpr size_type vector_size = size;
    using index_type = Indices;
    static constexpr bool has_duplicated_index
        = ofxSwizzle::detail::has_duplicated(index_type());
    static constexpr bool is_vector = Indices::size() > 1;
};

template <>
struct vector_traits<ofVec2f>
{
    using vector_type = ofVec2f;
    using value_type = float;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = float&;
    using const_reference = float const&;
    using pointer = float*;
    using const_pointer = float const*;
    using iterator = float*;
    using const_iterator = float const*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    static constexpr size_type size = 2;
    static constexpr size_type vector_size = size;
    using index_type = std::index_sequence<size>;
    static constexpr bool has_duplicated_index = false;
    static constexpr bool is_vector = true;
};

template <>
struct vector_traits<ofVec3f>
{
    using vector_type = ofVec3f;
    using value_type = float;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = float&;
    using const_reference = float const&;
    using pointer = float*;
    using const_pointer = float const*;
    using iterator = float*;
    using const_iterator = float const*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    static constexpr size_type size = 3;
    static constexpr size_type vector_size = size;
    using index_type = std::make_index_sequence<size>;
    static constexpr bool has_duplicated_index = false;
    static constexpr bool is_vector = true;
};

template <>
struct vector_traits<ofVec4f>
{
    using vector_type = ofVec4f;
    using value_type = float;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = float&;
    using const_reference = float const&;
    using pointer = float*;
    using const_pointer = float const*;
    using iterator = float*;
    using const_iterator = float const*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    static constexpr size_type size = 4;
    static constexpr size_type vector_size = size;
    using index_type = std::make_index_sequence<size>;
    static constexpr bool has_duplicated_index = false;
    static constexpr bool is_vector = true;
};

template <typename T>
struct vector_traits<T&>
    : ofxSwizzle::detail::vector_traits<T>
{};

template <typename T>
struct vector_traits<T&&>
    : ofxSwizzle::detail::vector_traits<T>
{};

template <typename T>
struct vector_traits<T const>
    : ofxSwizzle::detail::vector_traits<T>
{};

template <typename T>
struct vector_traits<T volatile>
    : ofxSwizzle::detail::vector_traits<T>
{};

template <typename T>
struct vector_traits<T const volatile>
    : ofxSwizzle::detail::vector_traits<T>
{};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_VECTOR_TRAITS_HPP
