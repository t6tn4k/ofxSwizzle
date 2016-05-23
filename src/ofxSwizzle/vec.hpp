#ifndef OFX_SWIZZLE_VEC_HPP
#define OFX_SWIZZLE_VEC_HPP

#include <type_traits>
#include <utility>
#include "./detail/forward_element.hpp"
#include "./detail/fwd.hpp"
#include "./detail/has_duplicated.hpp"
#include "./detail/is_vector.hpp"
#include "./detail/member_impl.hpp"
#include "./detail/vector_traits.hpp"

namespace ofxSwizzle {

namespace detail {

template <typename T, std::size_t N>
class vec
    : private ofxSwizzle::detail::member_impl<T, N>
{
private:
    using index_type = std::make_index_sequence<N>;
    using base_type = ofxSwizzle::detail::member_impl<T, N>;

public:
    using typename base_type::value_type;
    using typename base_type::size_type;
    using typename base_type::difference_type;
    using typename base_type::reference;
    using typename base_type::const_reference;
    using typename base_type::pointer;
    using typename base_type::const_pointer;
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

    using base_type::vector_size;

    vec() = default;
    vec(vec const&) = default;
    vec(vec&&) = default;

private:
    template <
        typename Vector, std::size_t... Indices,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<Vector>::size == vector_size>* = nullptr>
    vec(Vector&& other, std::index_sequence<Indices...> const&)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<Vector, Indices>(other))...>::value)
        : base_type(ofxSwizzle::detail::forward_element<Vector, Indices>(other)...)
    {
    }

    template <std::size_t... Indices>
    vec(value_type const& x, std::index_sequence<Indices...> const&)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(Indices, std::declval<value_type const&>())...>::value)
        : base_type((Indices, x)...)
    {
    }

public:
    template <
        typename Vector,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<Vector>::size == vector_size>* = nullptr>
    vec(Vector&& other)
        noexcept(std::is_nothrow_constructible<vec, Vector&&, index_type&&>::value)
        : vec(std::forward<Vector>(other), index_type())
    {
    }

    explicit vec(value_type const& x)
        noexcept(std::is_nothrow_constructible<vec, value_type const&, index_type&&>::value)
        : vec(x, index_type())
    {
    }

    ~vec() = default;

    auto operator=(vec const&) & -> vec& = default;
    auto operator=(vec&&) & -> vec& = default;

    using base_type::empty;
    using base_type::size;
    using base_type::max_size;
    using base_type::data;
    using base_type::at;
    using base_type::operator[];
    using base_type::front;
    using base_type::back;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::rend;
    using base_type::crbegin;
    using base_type::crend;
    using base_type::fill;
    using base_type::swap;
};

template <typename T>
class vec<T, 2>
    : private ofxSwizzle::detail::member_impl<T, 2>
{
private:
    using base_type = ofxSwizzle::detail::member_impl<T, 2>;

public:
    using typename base_type::value_type;
    using typename base_type::size_type;
    using typename base_type::difference_type;
    using typename base_type::reference;
    using typename base_type::const_reference;
    using typename base_type::pointer;
    using typename base_type::const_pointer;
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

    using base_type::vector_size;

    vec() = default;
    vec(vec const&) = default;
    vec(vec&&) = default;

    template <
        typename Vector,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<Vector>::size == vector_size>* = nullptr>
    vec(Vector&& other)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<Vector, 0>(other)),
            decltype(ofxSwizzle::detail::forward_element<Vector, 1>(other))>::value)
        : base_type(
            ofxSwizzle::detail::forward_element<Vector, 0>(other),
            ofxSwizzle::detail::forward_element<Vector, 1>(other))
    {
    }

    template<typename X, typename Y>
    vec(X&& x, Y&& y)
        noexcept(std::is_nothrow_constructible<base_type, X&&, Y&&>::value)
        : base_type(std::forward<X>(x), std::forward<Y>(y))
    {
    }

    explicit vec(value_type const& x)
        noexcept(std::is_nothrow_constructible<base_type,
            value_type const&, value_type const&>::value)
        : base_type(x, x)
    {
    }

    ~vec() = default;

    auto operator=(vec const&) & -> vec& = default;
    auto operator=(vec&&) & -> vec& = default;

    operator ofVec2f() const&
    {
        return ofVec2f((*this)[0], (*this)[1]);
    }

    using base_type::empty;
    using base_type::size;
    using base_type::max_size;
    using base_type::data;
    using base_type::at;
    using base_type::operator[];
    using base_type::front;
    using base_type::back;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::rend;
    using base_type::crbegin;
    using base_type::crend;
    using base_type::fill;
    using base_type::swap;

    using base_type::x;
    using base_type::y;

    using base_type::xx;
    using base_type::xy;
    using base_type::yx;
    using base_type::yy;

    using base_type::xxx;
    using base_type::xxy;
    using base_type::xyx;
    using base_type::xyy;
    using base_type::yxx;
    using base_type::yxy;
    using base_type::yyx;
    using base_type::yyy;

    using base_type::xxxx;
    using base_type::xxxy;
    using base_type::xxyx;
    using base_type::xxyy;
    using base_type::xyxx;
    using base_type::xyxy;
    using base_type::xyyx;
    using base_type::xyyy;
    using base_type::yxxx;
    using base_type::yxxy;
    using base_type::yxyx;
    using base_type::yxyy;
    using base_type::yyxx;
    using base_type::yyxy;
    using base_type::yyyx;
    using base_type::yyyy;

    using base_type::r;
    using base_type::g;

    using base_type::rr;
    using base_type::rg;
    using base_type::gr;
    using base_type::gg;

    using base_type::rrr;
    using base_type::rrg;
    using base_type::rgr;
    using base_type::rgg;
    using base_type::grr;
    using base_type::grg;
    using base_type::ggr;
    using base_type::ggg;

    using base_type::rrrr;
    using base_type::rrrg;
    using base_type::rrgr;
    using base_type::rrgg;
    using base_type::rgrr;
    using base_type::rgrg;
    using base_type::rggr;
    using base_type::rggg;
    using base_type::grrr;
    using base_type::grrg;
    using base_type::grgr;
    using base_type::grgg;
    using base_type::ggrr;
    using base_type::ggrg;
    using base_type::gggr;
    using base_type::gggg;

    using base_type::s;
    using base_type::t;

    using base_type::ss;
    using base_type::st;
    using base_type::ts;
    using base_type::tt;

    using base_type::sss;
    using base_type::sst;
    using base_type::sts;
    using base_type::stt;
    using base_type::tss;
    using base_type::tst;
    using base_type::tts;
    using base_type::ttt;

    using base_type::ssss;
    using base_type::ssst;
    using base_type::ssts;
    using base_type::sstt;
    using base_type::stss;
    using base_type::stst;
    using base_type::stts;
    using base_type::sttt;
    using base_type::tsss;
    using base_type::tsst;
    using base_type::tsts;
    using base_type::tstt;
    using base_type::ttss;
    using base_type::ttst;
    using base_type::ttts;
    using base_type::tttt;
};

template <typename T>
class vec<T, 3>
    : private ofxSwizzle::detail::member_impl<T, 3>
{
private:
    using base_type = ofxSwizzle::detail::member_impl<T, 3>;

public:
    using typename base_type::value_type;
    using typename base_type::size_type;
    using typename base_type::difference_type;
    using typename base_type::reference;
    using typename base_type::const_reference;
    using typename base_type::pointer;
    using typename base_type::const_pointer;
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

    using base_type::vector_size;

    vec() = default;
    vec(vec const&) = default;
    vec(vec&&) = default;

    template <
        typename Vector,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<Vector>::size == vector_size>* = nullptr>
    vec(Vector&& other)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<Vector, 0>(other)),
            decltype(ofxSwizzle::detail::forward_element<Vector, 1>(other)),
            decltype(ofxSwizzle::detail::forward_element<Vector, 2>(other))>::value)
        : base_type(
            ofxSwizzle::detail::forward_element<Vector, 0>(other),
            ofxSwizzle::detail::forward_element<Vector, 1>(other),
            ofxSwizzle::detail::forward_element<Vector, 2>(other))
    {
    }

    template<typename X, typename Y, typename Z>
    vec(X&& x, Y&& y, Z&& z)
        noexcept(std::is_nothrow_constructible<base_type, X&&, Y&&, Z&&>::value)
        : base_type(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z))
    {
    }

    template <
        typename X, typename YZ,
        std::enable_if_t<!ofxSwizzle::detail::is_vector_v<X>
            && ofxSwizzle::detail::vector_traits<YZ>::size == 2>* = nullptr>
    vec(X&& x, YZ&& yz)
        noexcept(std::is_nothrow_constructible<base_type,
            X&&,
            decltype(ofxSwizzle::detail::forward_element<YZ, 0>(yz)),
            decltype(ofxSwizzle::detail::forward_element<YZ, 1>(yz))>::value)
        : base_type(
            std::forward<X>(x),
            ofxSwizzle::detail::forward_element<YZ, 0>(yz),
            ofxSwizzle::detail::forward_element<YZ, 1>(yz))
    {
    }

    template <
        typename XY, typename Z,
        std::enable_if_t<!ofxSwizzle::detail::vector_traits<XY>::size == 2
            && ofxSwizzle::detail::is_vector_v<Z>>* = nullptr>
    vec(XY&& xy, Z&& z)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<XY, 0>(xy)),
            decltype(ofxSwizzle::detail::forward_element<XY, 1>(xy)),
            Z&&>::value)
        : base_type(
            ofxSwizzle::detail::forward_element<XY, 0>(xy),
            ofxSwizzle::detail::forward_element<XY, 1>(xy),
            std::forward<Z>(z))
    {
    }

    explicit vec(value_type const& x)
        noexcept(std::is_nothrow_constructible<base_type,
            value_type const&, value_type const&, value_type const&>::value)
        : base_type(x, x, x)
    {
    }

    ~vec() = default;

    auto operator=(vec const&) & -> vec& = default;
    auto operator=(vec&&) & -> vec& = default;

    operator ofVec3f() const&
    {
        return ofVec3f((*this)[0], (*this)[1], (*this)[2]);
    }

    using base_type::empty;
    using base_type::size;
    using base_type::max_size;
    using base_type::data;
    using base_type::at;
    using base_type::operator[];
    using base_type::front;
    using base_type::back;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::rend;
    using base_type::crbegin;
    using base_type::crend;
    using base_type::fill;
    using base_type::swap;

    using base_type::x;
    using base_type::y;
    using base_type::z;

    using base_type::xx;
    using base_type::xy;
    using base_type::xz;
    using base_type::yx;
    using base_type::yy;
    using base_type::yz;
    using base_type::zx;
    using base_type::zy;
    using base_type::zz;

    using base_type::xxx;
    using base_type::xxy;
    using base_type::xxz;
    using base_type::xyx;
    using base_type::xyy;
    using base_type::xyz;
    using base_type::xzx;
    using base_type::xzy;
    using base_type::xzz;
    using base_type::yxx;
    using base_type::yxy;
    using base_type::yxz;
    using base_type::yyx;
    using base_type::yyy;
    using base_type::yyz;
    using base_type::yzx;
    using base_type::yzy;
    using base_type::yzz;
    using base_type::zxx;
    using base_type::zxy;
    using base_type::zxz;
    using base_type::zyx;
    using base_type::zyy;
    using base_type::zyz;
    using base_type::zzx;
    using base_type::zzy;
    using base_type::zzz;

    using base_type::xxxx;
    using base_type::xxxy;
    using base_type::xxxz;
    using base_type::xxyx;
    using base_type::xxyy;
    using base_type::xxyz;
    using base_type::xxzx;
    using base_type::xxzy;
    using base_type::xxzz;
    using base_type::xyxx;
    using base_type::xyxy;
    using base_type::xyxz;
    using base_type::xyyx;
    using base_type::xyyy;
    using base_type::xyyz;
    using base_type::xyzx;
    using base_type::xyzy;
    using base_type::xyzz;
    using base_type::xzxx;
    using base_type::xzxy;
    using base_type::xzxz;
    using base_type::xzyx;
    using base_type::xzyy;
    using base_type::xzyz;
    using base_type::xzzx;
    using base_type::xzzy;
    using base_type::xzzz;
    using base_type::yxxx;
    using base_type::yxxy;
    using base_type::yxxz;
    using base_type::yxyx;
    using base_type::yxyy;
    using base_type::yxyz;
    using base_type::yxzx;
    using base_type::yxzy;
    using base_type::yxzz;
    using base_type::yyxx;
    using base_type::yyxy;
    using base_type::yyxz;
    using base_type::yyyx;
    using base_type::yyyy;
    using base_type::yyyz;
    using base_type::yyzx;
    using base_type::yyzy;
    using base_type::yyzz;
    using base_type::yzxx;
    using base_type::yzxy;
    using base_type::yzxz;
    using base_type::yzyx;
    using base_type::yzyy;
    using base_type::yzyz;
    using base_type::yzzx;
    using base_type::yzzy;
    using base_type::yzzz;
    using base_type::zxxx;
    using base_type::zxxy;
    using base_type::zxxz;
    using base_type::zxyx;
    using base_type::zxyy;
    using base_type::zxyz;
    using base_type::zxzx;
    using base_type::zxzy;
    using base_type::zxzz;
    using base_type::zyxx;
    using base_type::zyxy;
    using base_type::zyxz;
    using base_type::zyyx;
    using base_type::zyyy;
    using base_type::zyyz;
    using base_type::zyzx;
    using base_type::zyzy;
    using base_type::zyzz;
    using base_type::zzxx;
    using base_type::zzxy;
    using base_type::zzxz;
    using base_type::zzyx;
    using base_type::zzyy;
    using base_type::zzyz;
    using base_type::zzzx;
    using base_type::zzzy;
    using base_type::zzzz;

    using base_type::r;
    using base_type::g;
    using base_type::b;

    using base_type::rr;
    using base_type::rg;
    using base_type::rb;
    using base_type::gr;
    using base_type::gg;
    using base_type::gb;
    using base_type::br;
    using base_type::bg;
    using base_type::bb;

    using base_type::rrr;
    using base_type::rrg;
    using base_type::rrb;
    using base_type::rgr;
    using base_type::rgg;
    using base_type::rgb;
    using base_type::rbr;
    using base_type::rbg;
    using base_type::rbb;
    using base_type::grr;
    using base_type::grg;
    using base_type::grb;
    using base_type::ggr;
    using base_type::ggg;
    using base_type::ggb;
    using base_type::gbr;
    using base_type::gbg;
    using base_type::gbb;
    using base_type::brr;
    using base_type::brg;
    using base_type::brb;
    using base_type::bgr;
    using base_type::bgg;
    using base_type::bgb;
    using base_type::bbr;
    using base_type::bbg;
    using base_type::bbb;

    using base_type::rrrr;
    using base_type::rrrg;
    using base_type::rrrb;
    using base_type::rrgr;
    using base_type::rrgg;
    using base_type::rrgb;
    using base_type::rrbr;
    using base_type::rrbg;
    using base_type::rrbb;
    using base_type::rgrr;
    using base_type::rgrg;
    using base_type::rgrb;
    using base_type::rggr;
    using base_type::rggg;
    using base_type::rggb;
    using base_type::rgbr;
    using base_type::rgbg;
    using base_type::rgbb;
    using base_type::rbrr;
    using base_type::rbrg;
    using base_type::rbrb;
    using base_type::rbgr;
    using base_type::rbgg;
    using base_type::rbgb;
    using base_type::rbbr;
    using base_type::rbbg;
    using base_type::rbbb;
    using base_type::grrr;
    using base_type::grrg;
    using base_type::grrb;
    using base_type::grgr;
    using base_type::grgg;
    using base_type::grgb;
    using base_type::grbr;
    using base_type::grbg;
    using base_type::grbb;
    using base_type::ggrr;
    using base_type::ggrg;
    using base_type::ggrb;
    using base_type::gggr;
    using base_type::gggg;
    using base_type::gggb;
    using base_type::ggbr;
    using base_type::ggbg;
    using base_type::ggbb;
    using base_type::gbrr;
    using base_type::gbrg;
    using base_type::gbrb;
    using base_type::gbgr;
    using base_type::gbgg;
    using base_type::gbgb;
    using base_type::gbbr;
    using base_type::gbbg;
    using base_type::gbbb;
    using base_type::brrr;
    using base_type::brrg;
    using base_type::brrb;
    using base_type::brgr;
    using base_type::brgg;
    using base_type::brgb;
    using base_type::brbr;
    using base_type::brbg;
    using base_type::brbb;
    using base_type::bgrr;
    using base_type::bgrg;
    using base_type::bgrb;
    using base_type::bggr;
    using base_type::bggg;
    using base_type::bggb;
    using base_type::bgbr;
    using base_type::bgbg;
    using base_type::bgbb;
    using base_type::bbrr;
    using base_type::bbrg;
    using base_type::bbrb;
    using base_type::bbgr;
    using base_type::bbgg;
    using base_type::bbgb;
    using base_type::bbbr;
    using base_type::bbbg;
    using base_type::bbbb;

    using base_type::s;
    using base_type::t;
    using base_type::p;

    using base_type::ss;
    using base_type::st;
    using base_type::sp;
    using base_type::ts;
    using base_type::tt;
    using base_type::tp;
    using base_type::ps;
    using base_type::pt;
    using base_type::pp;

    using base_type::sss;
    using base_type::sst;
    using base_type::ssp;
    using base_type::sts;
    using base_type::stt;
    using base_type::stp;
    using base_type::sps;
    using base_type::spt;
    using base_type::spp;
    using base_type::tss;
    using base_type::tst;
    using base_type::tsp;
    using base_type::tts;
    using base_type::ttt;
    using base_type::ttp;
    using base_type::tps;
    using base_type::tpt;
    using base_type::tpp;
    using base_type::pss;
    using base_type::pst;
    using base_type::psp;
    using base_type::pts;
    using base_type::ptt;
    using base_type::ptp;
    using base_type::pps;
    using base_type::ppt;
    using base_type::ppp;

    using base_type::ssss;
    using base_type::ssst;
    using base_type::sssp;
    using base_type::ssts;
    using base_type::sstt;
    using base_type::sstp;
    using base_type::ssps;
    using base_type::sspt;
    using base_type::sspp;
    using base_type::stss;
    using base_type::stst;
    using base_type::stsp;
    using base_type::stts;
    using base_type::sttt;
    using base_type::sttp;
    using base_type::stps;
    using base_type::stpt;
    using base_type::stpp;
    using base_type::spss;
    using base_type::spst;
    using base_type::spsp;
    using base_type::spts;
    using base_type::sptt;
    using base_type::sptp;
    using base_type::spps;
    using base_type::sppt;
    using base_type::sppp;
    using base_type::tsss;
    using base_type::tsst;
    using base_type::tssp;
    using base_type::tsts;
    using base_type::tstt;
    using base_type::tstp;
    using base_type::tsps;
    using base_type::tspt;
    using base_type::tspp;
    using base_type::ttss;
    using base_type::ttst;
    using base_type::ttsp;
    using base_type::ttts;
    using base_type::tttt;
    using base_type::tttp;
    using base_type::ttps;
    using base_type::ttpt;
    using base_type::ttpp;
    using base_type::tpss;
    using base_type::tpst;
    using base_type::tpsp;
    using base_type::tpts;
    using base_type::tptt;
    using base_type::tptp;
    using base_type::tpps;
    using base_type::tppt;
    using base_type::tppp;
    using base_type::psss;
    using base_type::psst;
    using base_type::pssp;
    using base_type::psts;
    using base_type::pstt;
    using base_type::pstp;
    using base_type::psps;
    using base_type::pspt;
    using base_type::pspp;
    using base_type::ptss;
    using base_type::ptst;
    using base_type::ptsp;
    using base_type::ptts;
    using base_type::pttt;
    using base_type::pttp;
    using base_type::ptps;
    using base_type::ptpt;
    using base_type::ptpp;
    using base_type::ppss;
    using base_type::ppst;
    using base_type::ppsp;
    using base_type::ppts;
    using base_type::pptt;
    using base_type::pptp;
    using base_type::ppps;
    using base_type::pppt;
    using base_type::pppp;
};

template <typename T>
class vec<T, 4>
    : private ofxSwizzle::detail::member_impl<T, 4>
{
private:
    using base_type = ofxSwizzle::detail::member_impl<T, 4>;

public:
    using typename base_type::value_type;
    using typename base_type::size_type;
    using typename base_type::difference_type;
    using typename base_type::reference;
    using typename base_type::const_reference;
    using typename base_type::pointer;
    using typename base_type::const_pointer;
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

    using base_type::vector_size;

    vec() = default;
    vec(vec const&) = default;
    vec(vec&&) = default;

    template <
        typename Vector,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<Vector>::size == vector_size>* = nullptr>
    vec(Vector&& other)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<Vector, 0>(other)),
            decltype(ofxSwizzle::detail::forward_element<Vector, 1>(other)),
            decltype(ofxSwizzle::detail::forward_element<Vector, 2>(other)),
            decltype(ofxSwizzle::detail::forward_element<Vector, 3>(other))>::value)
        : base_type(
            ofxSwizzle::detail::forward_element<Vector, 0>(other),
            ofxSwizzle::detail::forward_element<Vector, 1>(other),
            ofxSwizzle::detail::forward_element<Vector, 2>(other),
            ofxSwizzle::detail::forward_element<Vector, 3>(other))
    {
    }

    template<typename X, typename Y, typename Z, typename W>
    vec(X&& x, Y&& y, Z&& z, W&& w)
        noexcept(std::is_nothrow_constructible<base_type, X&&, Y&&, Z&&, W&&>::value)
        : base_type(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z), std::forward<W>(w))
    {
    }

    template <
        typename X, typename Y, typename ZW,
        std::enable_if_t<!ofxSwizzle::detail::is_vector_v<X>
            && !ofxSwizzle::detail::is_vector_v<Y>
            && ofxSwizzle::detail::vector_traits<ZW>::size == 2>* = nullptr>
    vec(X&& x, Y&& y, ZW&& zw)
        noexcept(std::is_nothrow_constructible<base_type,
            X&&,
            Y&&,
            decltype(ofxSwizzle::detail::forward_element<ZW, 0>(zw)),
            decltype(ofxSwizzle::detail::forward_element<ZW, 1>(zw))>::value)
        : base_type(
            std::forward<X>(x),
            std::forward<Y>(y),
            ofxSwizzle::detail::forward_element<ZW, 0>(zw),
            ofxSwizzle::detail::forward_element<ZW, 1>(zw))
    {
    }

    template <
        typename X, typename YZ, typename W,
        std::enable_if_t<!ofxSwizzle::detail::is_vector_v<X>
            && ofxSwizzle::detail::vector_traits<YZ>::size == 2
            && !ofxSwizzle::detail::is_vector_v<W>>* = nullptr>
    vec(X&& x, YZ&& yz, W&& w)
        noexcept(std::is_nothrow_constructible<base_type,
            X&&,
            decltype(ofxSwizzle::detail::forward_element<YZ, 0>(yz)),
            decltype(ofxSwizzle::detail::forward_element<YZ, 1>(yz)),
            W&&>::value)
        : base_type(
            std::forward<X>(x),
            ofxSwizzle::detail::forward_element<YZ, 0>(yz),
            ofxSwizzle::detail::forward_element<YZ, 1>(yz),
            std::forward<W>(x))
    {
    }

    template <
        typename XY, typename Z, typename W,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<XY>::size == 2
            && !ofxSwizzle::detail::is_vector_v<Z>
            && !ofxSwizzle::detail::is_vector_v<W>>* = nullptr>
    vec(XY&& xy, Z&& z, W&& w)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<XY, 0>(xy)),
            decltype(ofxSwizzle::detail::forward_element<XY, 1>(xy)),
            Z&&,
            W&&>::value)
        : base_type(
            ofxSwizzle::detail::forward_element<XY, 0>(xy),
            ofxSwizzle::detail::forward_element<XY, 1>(xy),
            std::forward<Z>(z),
            std::forward<W>(w))
    {
    }

    template <
        typename XY, typename ZW,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<XY>::size == 2
            && ofxSwizzle::detail::vector_traits<ZW>::size == 2>* = nullptr>
    vec(XY&& xy, ZW&& zw)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<XY, 0>(xy)),
            decltype(ofxSwizzle::detail::forward_element<XY, 1>(xy)),
            decltype(ofxSwizzle::detail::forward_element<ZW, 0>(zw)),
            decltype(ofxSwizzle::detail::forward_element<ZW, 1>(zw))>::value)
        : base_type(
            ofxSwizzle::detail::forward_element<XY, 0>(xy),
            ofxSwizzle::detail::forward_element<XY, 1>(xy),
            ofxSwizzle::detail::forward_element<ZW, 0>(zw),
            ofxSwizzle::detail::forward_element<ZW, 1>(zw))
    {
    }

    template <
        typename X, typename YZW,
        std::enable_if_t<!ofxSwizzle::detail::is_vector_v<X>
            && ofxSwizzle::detail::vector_traits<YZW>::size == 3>* = nullptr>
    vec(X&& x, YZW&& yzw)
        noexcept(std::is_nothrow_constructible<base_type,
            X&&,
            decltype(ofxSwizzle::detail::forward_element<YZW, 0>(yzw)),
            decltype(ofxSwizzle::detail::forward_element<YZW, 1>(yzw)),
            decltype(ofxSwizzle::detail::forward_element<YZW, 2>(yzw))>::value)
        : base_type(
            std::forward<X>(x),
            ofxSwizzle::detail::forward_element<YZW, 0>(yzw),
            ofxSwizzle::detail::forward_element<YZW, 1>(yzw),
            ofxSwizzle::detail::forward_element<YZW, 2>(yzw))
    {
    }

    template <
        typename XYZ, typename W,
        std::enable_if_t<ofxSwizzle::detail::vector_traits<XYZ>::size == 3
            && !ofxSwizzle::detail::is_vector_v<W>>* = nullptr>
    vec(XYZ&& xyz, W&& w)
        noexcept(std::is_nothrow_constructible<base_type,
            decltype(ofxSwizzle::detail::forward_element<XYZ, 0>(xyz)),
            decltype(ofxSwizzle::detail::forward_element<XYZ, 1>(xyz)),
            decltype(ofxSwizzle::detail::forward_element<XYZ, 2>(xyz)),
            W&&>::value)
        : base_type(
            ofxSwizzle::detail::forward_element<XYZ, 0>(xyz),
            ofxSwizzle::detail::forward_element<XYZ, 1>(xyz),
            ofxSwizzle::detail::forward_element<XYZ, 2>(xyz),
            std::forward<W>(w))
    {
    }

    explicit vec(value_type const& x)
        noexcept(std::is_nothrow_constructible<base_type,
            value_type const&, value_type const&, value_type const&, value_type const&>::value)
        : base_type(x, x, x, x)
    {
    }

    ~vec() = default;

    auto operator=(vec const&) & -> vec& = default;
    auto operator=(vec&&) & -> vec& = default;

    operator ofVec4f() const&
    {
        return ofVec4f((*this)[0], (*this)[1], (*this)[2], (*this)[3]);
    }

    using base_type::empty;
    using base_type::size;
    using base_type::max_size;
    using base_type::data;
    using base_type::at;
    using base_type::operator[];
    using base_type::front;
    using base_type::back;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::rend;
    using base_type::crbegin;
    using base_type::crend;
    using base_type::fill;
    using base_type::swap;

    using base_type::x;
    using base_type::y;
    using base_type::z;
    using base_type::w;

    using base_type::xx;
    using base_type::xy;
    using base_type::xz;
    using base_type::xw;
    using base_type::yx;
    using base_type::yy;
    using base_type::yz;
    using base_type::yw;
    using base_type::zx;
    using base_type::zy;
    using base_type::zz;
    using base_type::zw;
    using base_type::wx;
    using base_type::wy;
    using base_type::wz;
    using base_type::ww;

    using base_type::xxx;
    using base_type::xxy;
    using base_type::xxz;
    using base_type::xxw;
    using base_type::xyx;
    using base_type::xyy;
    using base_type::xyz;
    using base_type::xyw;
    using base_type::xzx;
    using base_type::xzy;
    using base_type::xzz;
    using base_type::xzw;
    using base_type::xwx;
    using base_type::xwy;
    using base_type::xwz;
    using base_type::xww;
    using base_type::yxx;
    using base_type::yxy;
    using base_type::yxz;
    using base_type::yxw;
    using base_type::yyx;
    using base_type::yyy;
    using base_type::yyz;
    using base_type::yyw;
    using base_type::yzx;
    using base_type::yzy;
    using base_type::yzz;
    using base_type::yzw;
    using base_type::ywx;
    using base_type::ywy;
    using base_type::ywz;
    using base_type::yww;
    using base_type::zxx;
    using base_type::zxy;
    using base_type::zxz;
    using base_type::zxw;
    using base_type::zyx;
    using base_type::zyy;
    using base_type::zyz;
    using base_type::zyw;
    using base_type::zzx;
    using base_type::zzy;
    using base_type::zzz;
    using base_type::zzw;
    using base_type::zwx;
    using base_type::zwy;
    using base_type::zwz;
    using base_type::zww;
    using base_type::wxx;
    using base_type::wxy;
    using base_type::wxz;
    using base_type::wxw;
    using base_type::wyx;
    using base_type::wyy;
    using base_type::wyz;
    using base_type::wyw;
    using base_type::wzx;
    using base_type::wzy;
    using base_type::wzz;
    using base_type::wzw;
    using base_type::wwx;
    using base_type::wwy;
    using base_type::wwz;
    using base_type::www;

    using base_type::xxxx;
    using base_type::xxxy;
    using base_type::xxxz;
    using base_type::xxxw;
    using base_type::xxyx;
    using base_type::xxyy;
    using base_type::xxyz;
    using base_type::xxyw;
    using base_type::xxzx;
    using base_type::xxzy;
    using base_type::xxzz;
    using base_type::xxzw;
    using base_type::xxwx;
    using base_type::xxwy;
    using base_type::xxwz;
    using base_type::xxww;
    using base_type::xyxx;
    using base_type::xyxy;
    using base_type::xyxz;
    using base_type::xyxw;
    using base_type::xyyx;
    using base_type::xyyy;
    using base_type::xyyz;
    using base_type::xyyw;
    using base_type::xyzx;
    using base_type::xyzy;
    using base_type::xyzz;
    using base_type::xyzw;
    using base_type::xywx;
    using base_type::xywy;
    using base_type::xywz;
    using base_type::xyww;
    using base_type::xzxx;
    using base_type::xzxy;
    using base_type::xzxz;
    using base_type::xzxw;
    using base_type::xzyx;
    using base_type::xzyy;
    using base_type::xzyz;
    using base_type::xzyw;
    using base_type::xzzx;
    using base_type::xzzy;
    using base_type::xzzz;
    using base_type::xzzw;
    using base_type::xzwx;
    using base_type::xzwy;
    using base_type::xzwz;
    using base_type::xzww;
    using base_type::xwxx;
    using base_type::xwxy;
    using base_type::xwxz;
    using base_type::xwxw;
    using base_type::xwyx;
    using base_type::xwyy;
    using base_type::xwyz;
    using base_type::xwyw;
    using base_type::xwzx;
    using base_type::xwzy;
    using base_type::xwzz;
    using base_type::xwzw;
    using base_type::xwwx;
    using base_type::xwwy;
    using base_type::xwwz;
    using base_type::xwww;
    using base_type::yxxx;
    using base_type::yxxy;
    using base_type::yxxz;
    using base_type::yxxw;
    using base_type::yxyx;
    using base_type::yxyy;
    using base_type::yxyz;
    using base_type::yxyw;
    using base_type::yxzx;
    using base_type::yxzy;
    using base_type::yxzz;
    using base_type::yxzw;
    using base_type::yxwx;
    using base_type::yxwy;
    using base_type::yxwz;
    using base_type::yxww;
    using base_type::yyxx;
    using base_type::yyxy;
    using base_type::yyxz;
    using base_type::yyxw;
    using base_type::yyyx;
    using base_type::yyyy;
    using base_type::yyyz;
    using base_type::yyyw;
    using base_type::yyzx;
    using base_type::yyzy;
    using base_type::yyzz;
    using base_type::yyzw;
    using base_type::yywx;
    using base_type::yywy;
    using base_type::yywz;
    using base_type::yyww;
    using base_type::yzxx;
    using base_type::yzxy;
    using base_type::yzxz;
    using base_type::yzxw;
    using base_type::yzyx;
    using base_type::yzyy;
    using base_type::yzyz;
    using base_type::yzyw;
    using base_type::yzzx;
    using base_type::yzzy;
    using base_type::yzzz;
    using base_type::yzzw;
    using base_type::yzwx;
    using base_type::yzwy;
    using base_type::yzwz;
    using base_type::yzww;
    using base_type::ywxx;
    using base_type::ywxy;
    using base_type::ywxz;
    using base_type::ywxw;
    using base_type::ywyx;
    using base_type::ywyy;
    using base_type::ywyz;
    using base_type::ywyw;
    using base_type::ywzx;
    using base_type::ywzy;
    using base_type::ywzz;
    using base_type::ywzw;
    using base_type::ywwx;
    using base_type::ywwy;
    using base_type::ywwz;
    using base_type::ywww;
    using base_type::zxxx;
    using base_type::zxxy;
    using base_type::zxxz;
    using base_type::zxxw;
    using base_type::zxyx;
    using base_type::zxyy;
    using base_type::zxyz;
    using base_type::zxyw;
    using base_type::zxzx;
    using base_type::zxzy;
    using base_type::zxzz;
    using base_type::zxzw;
    using base_type::zxwx;
    using base_type::zxwy;
    using base_type::zxwz;
    using base_type::zxww;
    using base_type::zyxx;
    using base_type::zyxy;
    using base_type::zyxz;
    using base_type::zyxw;
    using base_type::zyyx;
    using base_type::zyyy;
    using base_type::zyyz;
    using base_type::zyyw;
    using base_type::zyzx;
    using base_type::zyzy;
    using base_type::zyzz;
    using base_type::zyzw;
    using base_type::zywx;
    using base_type::zywy;
    using base_type::zywz;
    using base_type::zyww;
    using base_type::zzxx;
    using base_type::zzxy;
    using base_type::zzxz;
    using base_type::zzxw;
    using base_type::zzyx;
    using base_type::zzyy;
    using base_type::zzyz;
    using base_type::zzyw;
    using base_type::zzzx;
    using base_type::zzzy;
    using base_type::zzzz;
    using base_type::zzzw;
    using base_type::zzwx;
    using base_type::zzwy;
    using base_type::zzwz;
    using base_type::zzww;
    using base_type::zwxx;
    using base_type::zwxy;
    using base_type::zwxz;
    using base_type::zwxw;
    using base_type::zwyx;
    using base_type::zwyy;
    using base_type::zwyz;
    using base_type::zwyw;
    using base_type::zwzx;
    using base_type::zwzy;
    using base_type::zwzz;
    using base_type::zwzw;
    using base_type::zwwx;
    using base_type::zwwy;
    using base_type::zwwz;
    using base_type::zwww;
    using base_type::wxxx;
    using base_type::wxxy;
    using base_type::wxxz;
    using base_type::wxxw;
    using base_type::wxyx;
    using base_type::wxyy;
    using base_type::wxyz;
    using base_type::wxyw;
    using base_type::wxzx;
    using base_type::wxzy;
    using base_type::wxzz;
    using base_type::wxzw;
    using base_type::wxwx;
    using base_type::wxwy;
    using base_type::wxwz;
    using base_type::wxww;
    using base_type::wyxx;
    using base_type::wyxy;
    using base_type::wyxz;
    using base_type::wyxw;
    using base_type::wyyx;
    using base_type::wyyy;
    using base_type::wyyz;
    using base_type::wyyw;
    using base_type::wyzx;
    using base_type::wyzy;
    using base_type::wyzz;
    using base_type::wyzw;
    using base_type::wywx;
    using base_type::wywy;
    using base_type::wywz;
    using base_type::wyww;
    using base_type::wzxx;
    using base_type::wzxy;
    using base_type::wzxz;
    using base_type::wzxw;
    using base_type::wzyx;
    using base_type::wzyy;
    using base_type::wzyz;
    using base_type::wzyw;
    using base_type::wzzx;
    using base_type::wzzy;
    using base_type::wzzz;
    using base_type::wzzw;
    using base_type::wzwx;
    using base_type::wzwy;
    using base_type::wzwz;
    using base_type::wzww;
    using base_type::wwxx;
    using base_type::wwxy;
    using base_type::wwxz;
    using base_type::wwxw;
    using base_type::wwyx;
    using base_type::wwyy;
    using base_type::wwyz;
    using base_type::wwyw;
    using base_type::wwzx;
    using base_type::wwzy;
    using base_type::wwzz;
    using base_type::wwzw;
    using base_type::wwwx;
    using base_type::wwwy;
    using base_type::wwwz;
    using base_type::wwww;

    using base_type::r;
    using base_type::g;
    using base_type::b;
    using base_type::a;

    using base_type::rr;
    using base_type::rg;
    using base_type::rb;
    using base_type::ra;
    using base_type::gr;
    using base_type::gg;
    using base_type::gb;
    using base_type::ga;
    using base_type::br;
    using base_type::bg;
    using base_type::bb;
    using base_type::ba;
    using base_type::ar;
    using base_type::ag;
    using base_type::ab;
    using base_type::aa;

    using base_type::rrr;
    using base_type::rrg;
    using base_type::rrb;
    using base_type::rra;
    using base_type::rgr;
    using base_type::rgg;
    using base_type::rgb;
    using base_type::rga;
    using base_type::rbr;
    using base_type::rbg;
    using base_type::rbb;
    using base_type::rba;
    using base_type::rar;
    using base_type::rag;
    using base_type::rab;
    using base_type::raa;
    using base_type::grr;
    using base_type::grg;
    using base_type::grb;
    using base_type::gra;
    using base_type::ggr;
    using base_type::ggg;
    using base_type::ggb;
    using base_type::gga;
    using base_type::gbr;
    using base_type::gbg;
    using base_type::gbb;
    using base_type::gba;
    using base_type::gar;
    using base_type::gag;
    using base_type::gab;
    using base_type::gaa;
    using base_type::brr;
    using base_type::brg;
    using base_type::brb;
    using base_type::bra;
    using base_type::bgr;
    using base_type::bgg;
    using base_type::bgb;
    using base_type::bga;
    using base_type::bbr;
    using base_type::bbg;
    using base_type::bbb;
    using base_type::bba;
    using base_type::bar;
    using base_type::bag;
    using base_type::bab;
    using base_type::baa;
    using base_type::arr;
    using base_type::arg;
    using base_type::arb;
    using base_type::ara;
    using base_type::agr;
    using base_type::agg;
    using base_type::agb;
    using base_type::aga;
    using base_type::abr;
    using base_type::abg;
    using base_type::abb;
    using base_type::aba;
    using base_type::aar;
    using base_type::aag;
    using base_type::aab;
    using base_type::aaa;

    using base_type::rrrr;
    using base_type::rrrg;
    using base_type::rrrb;
    using base_type::rrra;
    using base_type::rrgr;
    using base_type::rrgg;
    using base_type::rrgb;
    using base_type::rrga;
    using base_type::rrbr;
    using base_type::rrbg;
    using base_type::rrbb;
    using base_type::rrba;
    using base_type::rrar;
    using base_type::rrag;
    using base_type::rrab;
    using base_type::rraa;
    using base_type::rgrr;
    using base_type::rgrg;
    using base_type::rgrb;
    using base_type::rgra;
    using base_type::rggr;
    using base_type::rggg;
    using base_type::rggb;
    using base_type::rgga;
    using base_type::rgbr;
    using base_type::rgbg;
    using base_type::rgbb;
    using base_type::rgba;
    using base_type::rgar;
    using base_type::rgag;
    using base_type::rgab;
    using base_type::rgaa;
    using base_type::rbrr;
    using base_type::rbrg;
    using base_type::rbrb;
    using base_type::rbra;
    using base_type::rbgr;
    using base_type::rbgg;
    using base_type::rbgb;
    using base_type::rbga;
    using base_type::rbbr;
    using base_type::rbbg;
    using base_type::rbbb;
    using base_type::rbba;
    using base_type::rbar;
    using base_type::rbag;
    using base_type::rbab;
    using base_type::rbaa;
    using base_type::rarr;
    using base_type::rarg;
    using base_type::rarb;
    using base_type::rara;
    using base_type::ragr;
    using base_type::ragg;
    using base_type::ragb;
    using base_type::raga;
    using base_type::rabr;
    using base_type::rabg;
    using base_type::rabb;
    using base_type::raba;
    using base_type::raar;
    using base_type::raag;
    using base_type::raab;
    using base_type::raaa;
    using base_type::grrr;
    using base_type::grrg;
    using base_type::grrb;
    using base_type::grra;
    using base_type::grgr;
    using base_type::grgg;
    using base_type::grgb;
    using base_type::grga;
    using base_type::grbr;
    using base_type::grbg;
    using base_type::grbb;
    using base_type::grba;
    using base_type::grar;
    using base_type::grag;
    using base_type::grab;
    using base_type::graa;
    using base_type::ggrr;
    using base_type::ggrg;
    using base_type::ggrb;
    using base_type::ggra;
    using base_type::gggr;
    using base_type::gggg;
    using base_type::gggb;
    using base_type::ggga;
    using base_type::ggbr;
    using base_type::ggbg;
    using base_type::ggbb;
    using base_type::ggba;
    using base_type::ggar;
    using base_type::ggag;
    using base_type::ggab;
    using base_type::ggaa;
    using base_type::gbrr;
    using base_type::gbrg;
    using base_type::gbrb;
    using base_type::gbra;
    using base_type::gbgr;
    using base_type::gbgg;
    using base_type::gbgb;
    using base_type::gbga;
    using base_type::gbbr;
    using base_type::gbbg;
    using base_type::gbbb;
    using base_type::gbba;
    using base_type::gbar;
    using base_type::gbag;
    using base_type::gbab;
    using base_type::gbaa;
    using base_type::garr;
    using base_type::garg;
    using base_type::garb;
    using base_type::gara;
    using base_type::gagr;
    using base_type::gagg;
    using base_type::gagb;
    using base_type::gaga;
    using base_type::gabr;
    using base_type::gabg;
    using base_type::gabb;
    using base_type::gaba;
    using base_type::gaar;
    using base_type::gaag;
    using base_type::gaab;
    using base_type::gaaa;
    using base_type::brrr;
    using base_type::brrg;
    using base_type::brrb;
    using base_type::brra;
    using base_type::brgr;
    using base_type::brgg;
    using base_type::brgb;
    using base_type::brga;
    using base_type::brbr;
    using base_type::brbg;
    using base_type::brbb;
    using base_type::brba;
    using base_type::brar;
    using base_type::brag;
    using base_type::brab;
    using base_type::braa;
    using base_type::bgrr;
    using base_type::bgrg;
    using base_type::bgrb;
    using base_type::bgra;
    using base_type::bggr;
    using base_type::bggg;
    using base_type::bggb;
    using base_type::bgga;
    using base_type::bgbr;
    using base_type::bgbg;
    using base_type::bgbb;
    using base_type::bgba;
    using base_type::bgar;
    using base_type::bgag;
    using base_type::bgab;
    using base_type::bgaa;
    using base_type::bbrr;
    using base_type::bbrg;
    using base_type::bbrb;
    using base_type::bbra;
    using base_type::bbgr;
    using base_type::bbgg;
    using base_type::bbgb;
    using base_type::bbga;
    using base_type::bbbr;
    using base_type::bbbg;
    using base_type::bbbb;
    using base_type::bbba;
    using base_type::bbar;
    using base_type::bbag;
    using base_type::bbab;
    using base_type::bbaa;
    using base_type::barr;
    using base_type::barg;
    using base_type::barb;
    using base_type::bara;
    using base_type::bagr;
    using base_type::bagg;
    using base_type::bagb;
    using base_type::baga;
    using base_type::babr;
    using base_type::babg;
    using base_type::babb;
    using base_type::baba;
    using base_type::baar;
    using base_type::baag;
    using base_type::baab;
    using base_type::baaa;
    using base_type::arrr;
    using base_type::arrg;
    using base_type::arrb;
    using base_type::arra;
    using base_type::argr;
    using base_type::argg;
    using base_type::argb;
    using base_type::arga;
    using base_type::arbr;
    using base_type::arbg;
    using base_type::arbb;
    using base_type::arba;
    using base_type::arar;
    using base_type::arag;
    using base_type::arab;
    using base_type::araa;
    using base_type::agrr;
    using base_type::agrg;
    using base_type::agrb;
    using base_type::agra;
    using base_type::aggr;
    using base_type::aggg;
    using base_type::aggb;
    using base_type::agga;
    using base_type::agbr;
    using base_type::agbg;
    using base_type::agbb;
    using base_type::agba;
    using base_type::agar;
    using base_type::agag;
    using base_type::agab;
    using base_type::agaa;
    using base_type::abrr;
    using base_type::abrg;
    using base_type::abrb;
    using base_type::abra;
    using base_type::abgr;
    using base_type::abgg;
    using base_type::abgb;
    using base_type::abga;
    using base_type::abbr;
    using base_type::abbg;
    using base_type::abbb;
    using base_type::abba;
    using base_type::abar;
    using base_type::abag;
    using base_type::abab;
    using base_type::abaa;
    using base_type::aarr;
    using base_type::aarg;
    using base_type::aarb;
    using base_type::aara;
    using base_type::aagr;
    using base_type::aagg;
    using base_type::aagb;
    using base_type::aaga;
    using base_type::aabr;
    using base_type::aabg;
    using base_type::aabb;
    using base_type::aaba;
    using base_type::aaar;
    using base_type::aaag;
    using base_type::aaab;
    using base_type::aaaa;

    using base_type::s;
    using base_type::t;
    using base_type::p;
    using base_type::q;

    using base_type::ss;
    using base_type::st;
    using base_type::sp;
    using base_type::sq;
    using base_type::ts;
    using base_type::tt;
    using base_type::tp;
    using base_type::tq;
    using base_type::ps;
    using base_type::pt;
    using base_type::pp;
    using base_type::pq;
    using base_type::qs;
    using base_type::qt;
    using base_type::qp;
    using base_type::qq;

    using base_type::sss;
    using base_type::sst;
    using base_type::ssp;
    using base_type::ssq;
    using base_type::sts;
    using base_type::stt;
    using base_type::stp;
    using base_type::stq;
    using base_type::sps;
    using base_type::spt;
    using base_type::spp;
    using base_type::spq;
    using base_type::sqs;
    using base_type::sqt;
    using base_type::sqp;
    using base_type::sqq;
    using base_type::tss;
    using base_type::tst;
    using base_type::tsp;
    using base_type::tsq;
    using base_type::tts;
    using base_type::ttt;
    using base_type::ttp;
    using base_type::ttq;
    using base_type::tps;
    using base_type::tpt;
    using base_type::tpp;
    using base_type::tpq;
    using base_type::tqs;
    using base_type::tqt;
    using base_type::tqp;
    using base_type::tqq;
    using base_type::pss;
    using base_type::pst;
    using base_type::psp;
    using base_type::psq;
    using base_type::pts;
    using base_type::ptt;
    using base_type::ptp;
    using base_type::ptq;
    using base_type::pps;
    using base_type::ppt;
    using base_type::ppp;
    using base_type::ppq;
    using base_type::pqs;
    using base_type::pqt;
    using base_type::pqp;
    using base_type::pqq;
    using base_type::qss;
    using base_type::qst;
    using base_type::qsp;
    using base_type::qsq;
    using base_type::qts;
    using base_type::qtt;
    using base_type::qtp;
    using base_type::qtq;
    using base_type::qps;
    using base_type::qpt;
    using base_type::qpp;
    using base_type::qpq;
    using base_type::qqs;
    using base_type::qqt;
    using base_type::qqp;
    using base_type::qqq;

    using base_type::ssss;
    using base_type::ssst;
    using base_type::sssp;
    using base_type::sssq;
    using base_type::ssts;
    using base_type::sstt;
    using base_type::sstp;
    using base_type::sstq;
    using base_type::ssps;
    using base_type::sspt;
    using base_type::sspp;
    using base_type::sspq;
    using base_type::ssqs;
    using base_type::ssqt;
    using base_type::ssqp;
    using base_type::ssqq;
    using base_type::stss;
    using base_type::stst;
    using base_type::stsp;
    using base_type::stsq;
    using base_type::stts;
    using base_type::sttt;
    using base_type::sttp;
    using base_type::sttq;
    using base_type::stps;
    using base_type::stpt;
    using base_type::stpp;
    using base_type::stpq;
    using base_type::stqs;
    using base_type::stqt;
    using base_type::stqp;
    using base_type::stqq;
    using base_type::spss;
    using base_type::spst;
    using base_type::spsp;
    using base_type::spsq;
    using base_type::spts;
    using base_type::sptt;
    using base_type::sptp;
    using base_type::sptq;
    using base_type::spps;
    using base_type::sppt;
    using base_type::sppp;
    using base_type::sppq;
    using base_type::spqs;
    using base_type::spqt;
    using base_type::spqp;
    using base_type::spqq;
    using base_type::sqss;
    using base_type::sqst;
    using base_type::sqsp;
    using base_type::sqsq;
    using base_type::sqts;
    using base_type::sqtt;
    using base_type::sqtp;
    using base_type::sqtq;
    using base_type::sqps;
    using base_type::sqpt;
    using base_type::sqpp;
    using base_type::sqpq;
    using base_type::sqqs;
    using base_type::sqqt;
    using base_type::sqqp;
    using base_type::sqqq;
    using base_type::tsss;
    using base_type::tsst;
    using base_type::tssp;
    using base_type::tssq;
    using base_type::tsts;
    using base_type::tstt;
    using base_type::tstp;
    using base_type::tstq;
    using base_type::tsps;
    using base_type::tspt;
    using base_type::tspp;
    using base_type::tspq;
    using base_type::tsqs;
    using base_type::tsqt;
    using base_type::tsqp;
    using base_type::tsqq;
    using base_type::ttss;
    using base_type::ttst;
    using base_type::ttsp;
    using base_type::ttsq;
    using base_type::ttts;
    using base_type::tttt;
    using base_type::tttp;
    using base_type::tttq;
    using base_type::ttps;
    using base_type::ttpt;
    using base_type::ttpp;
    using base_type::ttpq;
    using base_type::ttqs;
    using base_type::ttqt;
    using base_type::ttqp;
    using base_type::ttqq;
    using base_type::tpss;
    using base_type::tpst;
    using base_type::tpsp;
    using base_type::tpsq;
    using base_type::tpts;
    using base_type::tptt;
    using base_type::tptp;
    using base_type::tptq;
    using base_type::tpps;
    using base_type::tppt;
    using base_type::tppp;
    using base_type::tppq;
    using base_type::tpqs;
    using base_type::tpqt;
    using base_type::tpqp;
    using base_type::tpqq;
    using base_type::tqss;
    using base_type::tqst;
    using base_type::tqsp;
    using base_type::tqsq;
    using base_type::tqts;
    using base_type::tqtt;
    using base_type::tqtp;
    using base_type::tqtq;
    using base_type::tqps;
    using base_type::tqpt;
    using base_type::tqpp;
    using base_type::tqpq;
    using base_type::tqqs;
    using base_type::tqqt;
    using base_type::tqqp;
    using base_type::tqqq;
    using base_type::psss;
    using base_type::psst;
    using base_type::pssp;
    using base_type::pssq;
    using base_type::psts;
    using base_type::pstt;
    using base_type::pstp;
    using base_type::pstq;
    using base_type::psps;
    using base_type::pspt;
    using base_type::pspp;
    using base_type::pspq;
    using base_type::psqs;
    using base_type::psqt;
    using base_type::psqp;
    using base_type::psqq;
    using base_type::ptss;
    using base_type::ptst;
    using base_type::ptsp;
    using base_type::ptsq;
    using base_type::ptts;
    using base_type::pttt;
    using base_type::pttp;
    using base_type::pttq;
    using base_type::ptps;
    using base_type::ptpt;
    using base_type::ptpp;
    using base_type::ptpq;
    using base_type::ptqs;
    using base_type::ptqt;
    using base_type::ptqp;
    using base_type::ptqq;
    using base_type::ppss;
    using base_type::ppst;
    using base_type::ppsp;
    using base_type::ppsq;
    using base_type::ppts;
    using base_type::pptt;
    using base_type::pptp;
    using base_type::pptq;
    using base_type::ppps;
    using base_type::pppt;
    using base_type::pppp;
    using base_type::pppq;
    using base_type::ppqs;
    using base_type::ppqt;
    using base_type::ppqp;
    using base_type::ppqq;
    using base_type::pqss;
    using base_type::pqst;
    using base_type::pqsp;
    using base_type::pqsq;
    using base_type::pqts;
    using base_type::pqtt;
    using base_type::pqtp;
    using base_type::pqtq;
    using base_type::pqps;
    using base_type::pqpt;
    using base_type::pqpp;
    using base_type::pqpq;
    using base_type::pqqs;
    using base_type::pqqt;
    using base_type::pqqp;
    using base_type::pqqq;
    using base_type::qsss;
    using base_type::qsst;
    using base_type::qssp;
    using base_type::qssq;
    using base_type::qsts;
    using base_type::qstt;
    using base_type::qstp;
    using base_type::qstq;
    using base_type::qsps;
    using base_type::qspt;
    using base_type::qspp;
    using base_type::qspq;
    using base_type::qsqs;
    using base_type::qsqt;
    using base_type::qsqp;
    using base_type::qsqq;
    using base_type::qtss;
    using base_type::qtst;
    using base_type::qtsp;
    using base_type::qtsq;
    using base_type::qtts;
    using base_type::qttt;
    using base_type::qttp;
    using base_type::qttq;
    using base_type::qtps;
    using base_type::qtpt;
    using base_type::qtpp;
    using base_type::qtpq;
    using base_type::qtqs;
    using base_type::qtqt;
    using base_type::qtqp;
    using base_type::qtqq;
    using base_type::qpss;
    using base_type::qpst;
    using base_type::qpsp;
    using base_type::qpsq;
    using base_type::qpts;
    using base_type::qptt;
    using base_type::qptp;
    using base_type::qptq;
    using base_type::qpps;
    using base_type::qppt;
    using base_type::qppp;
    using base_type::qppq;
    using base_type::qpqs;
    using base_type::qpqt;
    using base_type::qpqp;
    using base_type::qpqq;
    using base_type::qqss;
    using base_type::qqst;
    using base_type::qqsp;
    using base_type::qqsq;
    using base_type::qqts;
    using base_type::qqtt;
    using base_type::qqtp;
    using base_type::qqtq;
    using base_type::qqps;
    using base_type::qqpt;
    using base_type::qqpp;
    using base_type::qqpq;
    using base_type::qqqs;
    using base_type::qqqt;
    using base_type::qqqp;
    using base_type::qqqq;
};

template <typename T, std::size_t N>
inline auto swap(ofxSwizzle::detail::vec<T, N>& lhs, ofxSwizzle::detail::vec<T, N>& rhs)
    noexcept(ofxSwizzle::detail::is_nothrow_swappable_v<T>)
{
    lhs.swap(rhs);
}

} // namespace detail

using ofxSwizzle::detail::vec;

} // namespace ofxSwizzle

#endif // #ifndef OFX_SWIZZLE_VEC_HPP
