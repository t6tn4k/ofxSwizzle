#ifndef OFX_SWIZZLE_DETAIL_IS_VECTOR
#define OFX_SWIZZLE_DETAIL_IS_VECTOR

#include <type_traits>
#include "./fwd.hpp"
#include "./has_duplicated.hpp"

namespace ofxSwizzle { namespace detail {

template <typename T>
struct is_vector
    : std::false_type
{};

template <typename T, std::size_t N>
struct is_vector<ofxSwizzle::detail::vec<T, N>>
    : std::true_type
{};

template <typename T, std::size_t N, typename Indices>
struct is_vector<ofxSwizzle::detail::swizzle_proxy<
    T, N, Indices, !ofxSwizzle::detail::has_duplicated(Indices())>>
    : std::integral_constant<bool, Indices::size() != 1>
{};

template <>
struct is_vector<ofVec2f>
    : std::true_type
{};

template <>
struct is_vector<ofVec3f>
    : std::true_type
{};

template <>
struct is_vector<ofVec4f>
    : std::true_type
{};

template <typename T>
struct is_vector<T&>
    : ofxSwizzle::detail::is_vector<T>
{};

template <typename T>
struct is_vector<T&&>
    : ofxSwizzle::detail::is_vector<T>
{};

template <typename T>
struct is_vector<T const>
    : ofxSwizzle::detail::is_vector<T>
{};

template <typename T>
struct is_vector<T volatile>
    : ofxSwizzle::detail::is_vector<T>
{};

template <typename T>
struct is_vector<T const volatile>
    : ofxSwizzle::detail::is_vector<T>
{};

template <typename T>
constexpr auto is_vector_v = ofxSwizzle::detail::is_vector<T>::value;

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_IS_VECTOR
