#ifndef OFX_SWIZZLE_ASSIGNMENT_HPP
#define OFX_SWIZZLE_ASSIGNMENT_HPP

#include <functional>
#include <type_traits>
#include <utility>
#include "./detail/is_same_size.hpp"
#include "./detail/is_same_value_type.hpp"
#include "./detail/is_vector.hpp"
#include "./detail/functional/assignment.hpp"
#include "./data.hpp"
#include "./for_each.hpp"

namespace ofxSwizzle {

namespace detail {

namespace {

template <typename Lhs, typename Rhs, typename Assign>
inline auto assign_impl(Lhs& lhs, Rhs&& rhs, Assign const& assign, std::nullptr_t)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_same_value_type_v<Lhs, Rhs>
            && ofxSwizzle::detail::is_same_size_v<Lhs, Rhs>,
        decltype(void(assign(lhs[0], rhs[0])), lhs)>
{
    ofxSwizzle::for_each(
        lhs,
        ofxSwizzle::cdata(lhs) == ofxSwizzle::cdata(rhs)
            ? std::decay_t<Rhs>(rhs)
            : std::forward<Rhs>(rhs),
        assign);
    return lhs;
}

template <typename Lhs, typename Rhs, typename Assign>
inline auto assign_impl(Lhs& lhs, Rhs&& rhs, Assign const& assign, std::nullptr_t)
    -> std::enable_if_t<
        !ofxSwizzle::detail::is_same_value_type_v<Lhs, Rhs>
            && ofxSwizzle::detail::is_same_size_v<Lhs, Rhs>,
        decltype(void(assign(lhs[0], rhs[0])), lhs)>

{
    ofxSwizzle::for_each(lhs, std::forward<Rhs>(rhs), assign);
    return lhs;
}

template <typename Lhs, typename Rhs, typename Assign>
inline auto assign_impl(Lhs& lhs, Rhs&& rhs, Assign const& assign, ...)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_same_value_type_v<Lhs, Rhs>,
        decltype(void(assign(lhs[0], rhs)), lhs)>
{
    ofxSwizzle::for_each(
        lhs,
        std::bind(
            assign,
            std::placeholders::_1,
            ofxSwizzle::cdata(lhs) == ofxSwizzle::cdata(rhs)
                ? std::decay_t<Rhs>(rhs)
                : std::forward<Rhs>(rhs)));
    return lhs;
}

template <typename Lhs, typename Rhs, typename Assign>
inline auto assign_impl(Lhs& lhs, Rhs&& rhs, Assign const& assign, ...)
    -> std::enable_if_t<
        !ofxSwizzle::detail::is_same_value_type_v<Lhs, Rhs>,
        decltype(void(assign(lhs[0], rhs)), lhs)>
{
    ofxSwizzle::for_each(lhs, std::bind(assign, std::placeholders::_1, std::forward<Rhs>(rhs)));
    return lhs;
}

} // namespace <unnamed>

template <typename Lhs, typename Rhs>
inline auto operator+=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::plus_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::plus_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator-=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::minus_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::minus_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator*=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::multiplies_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::multiplies_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator/=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::divides_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::divides_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator%=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::modulus_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::modulus_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator&=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::bit_and_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::bit_and_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator|=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::bit_or_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::bit_or_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator^=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::bit_xor_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::bit_xor_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator<<=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_left_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_left_assign(), nullptr);
}

template <typename Lhs, typename Rhs>
inline auto operator>>=(Lhs& lhs, Rhs&& rhs)
    -> std::enable_if_t<
        ofxSwizzle::detail::is_vector_v<Lhs>,
        decltype(ofxSwizzle::detail::assign_impl(
            lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_right_assign(), nullptr))>
{
    return ofxSwizzle::detail::assign_impl(
        lhs, std::forward<Rhs>(rhs), ofxSwizzle::detail::shift_right_assign(), nullptr);
}

} // namespace detail

using ofxSwizzle::detail::operator+=;
using ofxSwizzle::detail::operator-=;
using ofxSwizzle::detail::operator*=;
using ofxSwizzle::detail::operator/=;
using ofxSwizzle::detail::operator%=;
using ofxSwizzle::detail::operator&=;
using ofxSwizzle::detail::operator|=;
using ofxSwizzle::detail::operator^=;
using ofxSwizzle::detail::operator<<=;
using ofxSwizzle::detail::operator>>=;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_ASSIGNMENT_HPP
