#ifndef OFX_SWIZZLE_DETAIL_SWIZZLE_IMPL_HPP
#define OFX_SWIZZLE_DETAIL_SWIZZLE_IMPL_HPP

#include <type_traits>
#include <utility>
#include "./conjunction.hpp"
#include "./fwd.hpp"
#include "./has_duplicated.hpp"
#include "./swizzle_proxy.hpp"
#include "./vector_traits.hpp"

namespace ofxSwizzle { namespace detail {

template <typename T, std::size_t N>
class swizzle_impl
{
private:
    using value_type = T;
    using size_type = std::size_t;
    static constexpr size_type vector_size = N;

protected:
    value_type elems[vector_size];

    swizzle_impl() = default;
    swizzle_impl(swizzle_impl const&) = default;
    swizzle_impl(swizzle_impl&&) = default;

    template <typename... Ts, std::enable_if_t<sizeof...(Ts) == vector_size>* = nullptr>
    swizzle_impl(Ts&&... ts)
        noexcept(ofxSwizzle::detail::conjunction_v<
            std::is_nothrow_move_constructible<value_type>,
            std::is_nothrow_constructible<value_type, Ts&&>...>)
        : elems{static_cast<value_type>(std::forward<Ts>(ts))...}
    {
    }

    ~swizzle_impl() = default;

    auto operator=(swizzle_impl const&) & -> swizzle_impl& = default;
    auto operator=(swizzle_impl&&) & -> swizzle_impl&  = default;
};

template <typename T>
class swizzle_impl<T, 2>
{
private:
    using value_type = T;
    using size_type = std::size_t;
    static constexpr size_type vector_size = 2;

    template <std::size_t... Indices>
    using proxy_type = ofxSwizzle::detail::swizzle_proxy<
        value_type, vector_size, std::index_sequence<Indices...>,
        !ofxSwizzle::detail::has_duplicated(std::index_sequence<Indices...>())>;

protected:
    union
    {
        struct
        {
            value_type elems[vector_size];
        };

        proxy_type<0> x;
        proxy_type<1> y;

        proxy_type<0, 0> xx;
        proxy_type<0, 1> xy;
        proxy_type<1, 0> yx;
        proxy_type<1, 1> yy;

        proxy_type<0, 0, 0> xxx;
        proxy_type<0, 0, 1> xxy;
        proxy_type<0, 1, 0> xyx;
        proxy_type<0, 1, 1> xyy;
        proxy_type<1, 0, 0> yxx;
        proxy_type<1, 0, 1> yxy;
        proxy_type<1, 1, 0> yyx;
        proxy_type<1, 1, 1> yyy;

        proxy_type<0, 0, 0, 0> xxxx;
        proxy_type<0, 0, 0, 1> xxxy;
        proxy_type<0, 0, 1, 0> xxyx;
        proxy_type<0, 0, 1, 1> xxyy;
        proxy_type<0, 1, 0, 0> xyxx;
        proxy_type<0, 1, 0, 1> xyxy;
        proxy_type<0, 1, 1, 0> xyyx;
        proxy_type<0, 1, 1, 1> xyyy;
        proxy_type<1, 0, 0, 0> yxxx;
        proxy_type<1, 0, 0, 1> yxxy;
        proxy_type<1, 0, 1, 0> yxyx;
        proxy_type<1, 0, 1, 1> yxyy;
        proxy_type<1, 1, 0, 0> yyxx;
        proxy_type<1, 1, 0, 1> yyxy;
        proxy_type<1, 1, 1, 0> yyyx;
        proxy_type<1, 1, 1, 1> yyyy;

        proxy_type<0> r;
        proxy_type<1> g;

        proxy_type<0, 0> rr;
        proxy_type<0, 1> rg;
        proxy_type<1, 0> gr;
        proxy_type<1, 1> gg;

        proxy_type<0, 0, 0> rrr;
        proxy_type<0, 0, 1> rrg;
        proxy_type<0, 1, 0> rgr;
        proxy_type<0, 1, 1> rgg;
        proxy_type<1, 0, 0> grr;
        proxy_type<1, 0, 1> grg;
        proxy_type<1, 1, 0> ggr;
        proxy_type<1, 1, 1> ggg;

        proxy_type<0, 0, 0, 0> rrrr;
        proxy_type<0, 0, 0, 1> rrrg;
        proxy_type<0, 0, 1, 0> rrgr;
        proxy_type<0, 0, 1, 1> rrgg;
        proxy_type<0, 1, 0, 0> rgrr;
        proxy_type<0, 1, 0, 1> rgrg;
        proxy_type<0, 1, 1, 0> rggr;
        proxy_type<0, 1, 1, 1> rggg;
        proxy_type<1, 0, 0, 0> grrr;
        proxy_type<1, 0, 0, 1> grrg;
        proxy_type<1, 0, 1, 0> grgr;
        proxy_type<1, 0, 1, 1> grgg;
        proxy_type<1, 1, 0, 0> ggrr;
        proxy_type<1, 1, 0, 1> ggrg;
        proxy_type<1, 1, 1, 0> gggr;
        proxy_type<1, 1, 1, 1> gggg;

        proxy_type<0> s;
        proxy_type<1> t;

        proxy_type<0, 0> ss;
        proxy_type<0, 1> st;
        proxy_type<1, 0> ts;
        proxy_type<1, 1> tt;

        proxy_type<0, 0, 0> sss;
        proxy_type<0, 0, 1> sst;
        proxy_type<0, 1, 0> sts;
        proxy_type<0, 1, 1> stt;
        proxy_type<1, 0, 0> tss;
        proxy_type<1, 0, 1> tst;
        proxy_type<1, 1, 0> tts;
        proxy_type<1, 1, 1> ttt;

        proxy_type<0, 0, 0, 0> ssss;
        proxy_type<0, 0, 0, 1> ssst;
        proxy_type<0, 0, 1, 0> ssts;
        proxy_type<0, 0, 1, 1> sstt;
        proxy_type<0, 1, 0, 0> stss;
        proxy_type<0, 1, 0, 1> stst;
        proxy_type<0, 1, 1, 0> stts;
        proxy_type<0, 1, 1, 1> sttt;
        proxy_type<1, 0, 0, 0> tsss;
        proxy_type<1, 0, 0, 1> tsst;
        proxy_type<1, 0, 1, 0> tsts;
        proxy_type<1, 0, 1, 1> tstt;
        proxy_type<1, 1, 0, 0> ttss;
        proxy_type<1, 1, 0, 1> ttst;
        proxy_type<1, 1, 1, 0> ttts;
        proxy_type<1, 1, 1, 1> tttt;
    };

    swizzle_impl()
        noexcept(std::is_nothrow_default_constructible<value_type>::value)
        : elems{}
    {
    }

    swizzle_impl(swizzle_impl const& other)
        noexcept(std::is_nothrow_copy_constructible<value_type>::value)
        : elems{other.elems[0], other.elems[1]}
    {
    }

    swizzle_impl(swizzle_impl&& other)
        noexcept(std::is_nothrow_move_constructible<value_type>::value)
        : elems{std::move(other.elems[0]), std::move(other.elems[1])}
    {
    }

    template <typename X, typename Y>
    swizzle_impl(X&& x, Y&& y)
        noexcept(ofxSwizzle::detail::conjunction_v<
            std::is_nothrow_move_constructible<value_type>,
            std::is_nothrow_constructible<value_type, X&&>,
            std::is_nothrow_constructible<value_type, Y&&>>)
        : elems{
            static_cast<value_type>(std::forward<X>(x)),
            static_cast<value_type>(std::forward<Y>(y))}
    {
    }

    ~swizzle_impl()
        noexcept(std::is_nothrow_destructible<value_type>::value)
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i].~T();
        }
    }

    auto operator=(swizzle_impl const& other) &
        noexcept(std::is_nothrow_copy_assignable<value_type>::value)
        -> swizzle_impl&
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i] = other.elems[i];
        }
        return *this;
    }

    auto operator=(swizzle_impl&& other) &
        noexcept(std::is_nothrow_move_assignable<value_type>::value)
        -> swizzle_impl&
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i] = std::move(other.elems[i]);
        }
        return *this;
    }
};

template <typename T>
class swizzle_impl<T, 3>
{
private:
    using value_type = T;
    using size_type = std::size_t;
    static constexpr size_type vector_size = 3;

    template <std::size_t... Indices>
    using proxy_type = ofxSwizzle::detail::swizzle_proxy<
        value_type, vector_size, std::index_sequence<Indices...>,
        !ofxSwizzle::detail::has_duplicated(std::index_sequence<Indices...>())>;

protected:
    union
    {
        struct
        {
            value_type elems[vector_size];
        };

        proxy_type<0> x;
        proxy_type<1> y;
        proxy_type<2> z;

        proxy_type<0, 0> xx;
        proxy_type<0, 1> xy;
        proxy_type<0, 2> xz;
        proxy_type<1, 0> yx;
        proxy_type<1, 1> yy;
        proxy_type<1, 2> yz;
        proxy_type<2, 0> zx;
        proxy_type<2, 1> zy;
        proxy_type<2, 2> zz;

        proxy_type<0, 0, 0> xxx;
        proxy_type<0, 0, 1> xxy;
        proxy_type<0, 0, 2> xxz;
        proxy_type<0, 1, 0> xyx;
        proxy_type<0, 1, 1> xyy;
        proxy_type<0, 1, 2> xyz;
        proxy_type<0, 2, 0> xzx;
        proxy_type<0, 2, 1> xzy;
        proxy_type<0, 2, 2> xzz;
        proxy_type<1, 0, 0> yxx;
        proxy_type<1, 0, 1> yxy;
        proxy_type<1, 0, 2> yxz;
        proxy_type<1, 1, 0> yyx;
        proxy_type<1, 1, 1> yyy;
        proxy_type<1, 1, 2> yyz;
        proxy_type<1, 2, 0> yzx;
        proxy_type<1, 2, 1> yzy;
        proxy_type<1, 2, 2> yzz;
        proxy_type<2, 0, 0> zxx;
        proxy_type<2, 0, 1> zxy;
        proxy_type<2, 0, 2> zxz;
        proxy_type<2, 1, 0> zyx;
        proxy_type<2, 1, 1> zyy;
        proxy_type<2, 1, 2> zyz;
        proxy_type<2, 2, 0> zzx;
        proxy_type<2, 2, 1> zzy;
        proxy_type<2, 2, 2> zzz;

        proxy_type<0, 0, 0, 0> xxxx;
        proxy_type<0, 0, 0, 1> xxxy;
        proxy_type<0, 0, 0, 2> xxxz;
        proxy_type<0, 0, 1, 0> xxyx;
        proxy_type<0, 0, 1, 1> xxyy;
        proxy_type<0, 0, 1, 2> xxyz;
        proxy_type<0, 0, 2, 0> xxzx;
        proxy_type<0, 0, 2, 1> xxzy;
        proxy_type<0, 0, 2, 2> xxzz;
        proxy_type<0, 1, 0, 0> xyxx;
        proxy_type<0, 1, 0, 1> xyxy;
        proxy_type<0, 1, 0, 2> xyxz;
        proxy_type<0, 1, 1, 0> xyyx;
        proxy_type<0, 1, 1, 1> xyyy;
        proxy_type<0, 1, 1, 2> xyyz;
        proxy_type<0, 1, 2, 0> xyzx;
        proxy_type<0, 1, 2, 1> xyzy;
        proxy_type<0, 1, 2, 2> xyzz;
        proxy_type<0, 2, 0, 0> xzxx;
        proxy_type<0, 2, 0, 1> xzxy;
        proxy_type<0, 2, 0, 2> xzxz;
        proxy_type<0, 2, 1, 0> xzyx;
        proxy_type<0, 2, 1, 1> xzyy;
        proxy_type<0, 2, 1, 2> xzyz;
        proxy_type<0, 2, 2, 0> xzzx;
        proxy_type<0, 2, 2, 1> xzzy;
        proxy_type<0, 2, 2, 2> xzzz;
        proxy_type<1, 0, 0, 0> yxxx;
        proxy_type<1, 0, 0, 1> yxxy;
        proxy_type<1, 0, 0, 2> yxxz;
        proxy_type<1, 0, 1, 0> yxyx;
        proxy_type<1, 0, 1, 1> yxyy;
        proxy_type<1, 0, 1, 2> yxyz;
        proxy_type<1, 0, 2, 0> yxzx;
        proxy_type<1, 0, 2, 1> yxzy;
        proxy_type<1, 0, 2, 2> yxzz;
        proxy_type<1, 1, 0, 0> yyxx;
        proxy_type<1, 1, 0, 1> yyxy;
        proxy_type<1, 1, 0, 2> yyxz;
        proxy_type<1, 1, 1, 0> yyyx;
        proxy_type<1, 1, 1, 1> yyyy;
        proxy_type<1, 1, 1, 2> yyyz;
        proxy_type<1, 1, 2, 0> yyzx;
        proxy_type<1, 1, 2, 1> yyzy;
        proxy_type<1, 1, 2, 2> yyzz;
        proxy_type<1, 2, 0, 0> yzxx;
        proxy_type<1, 2, 0, 1> yzxy;
        proxy_type<1, 2, 0, 2> yzxz;
        proxy_type<1, 2, 1, 0> yzyx;
        proxy_type<1, 2, 1, 1> yzyy;
        proxy_type<1, 2, 1, 2> yzyz;
        proxy_type<1, 2, 2, 0> yzzx;
        proxy_type<1, 2, 2, 1> yzzy;
        proxy_type<1, 2, 2, 2> yzzz;
        proxy_type<2, 0, 0, 0> zxxx;
        proxy_type<2, 0, 0, 1> zxxy;
        proxy_type<2, 0, 0, 2> zxxz;
        proxy_type<2, 0, 1, 0> zxyx;
        proxy_type<2, 0, 1, 1> zxyy;
        proxy_type<2, 0, 1, 2> zxyz;
        proxy_type<2, 0, 2, 0> zxzx;
        proxy_type<2, 0, 2, 1> zxzy;
        proxy_type<2, 0, 2, 2> zxzz;
        proxy_type<2, 1, 0, 0> zyxx;
        proxy_type<2, 1, 0, 1> zyxy;
        proxy_type<2, 1, 0, 2> zyxz;
        proxy_type<2, 1, 1, 0> zyyx;
        proxy_type<2, 1, 1, 1> zyyy;
        proxy_type<2, 1, 1, 2> zyyz;
        proxy_type<2, 1, 2, 0> zyzx;
        proxy_type<2, 1, 2, 1> zyzy;
        proxy_type<2, 1, 2, 2> zyzz;
        proxy_type<2, 2, 0, 0> zzxx;
        proxy_type<2, 2, 0, 1> zzxy;
        proxy_type<2, 2, 0, 2> zzxz;
        proxy_type<2, 2, 1, 0> zzyx;
        proxy_type<2, 2, 1, 1> zzyy;
        proxy_type<2, 2, 1, 2> zzyz;
        proxy_type<2, 2, 2, 0> zzzx;
        proxy_type<2, 2, 2, 1> zzzy;
        proxy_type<2, 2, 2, 2> zzzz;

        proxy_type<0> r;
        proxy_type<1> g;
        proxy_type<2> b;

        proxy_type<0, 0> rr;
        proxy_type<0, 1> rg;
        proxy_type<0, 2> rb;
        proxy_type<1, 0> gr;
        proxy_type<1, 1> gg;
        proxy_type<1, 2> gb;
        proxy_type<2, 0> br;
        proxy_type<2, 1> bg;
        proxy_type<2, 2> bb;

        proxy_type<0, 0, 0> rrr;
        proxy_type<0, 0, 1> rrg;
        proxy_type<0, 0, 2> rrb;
        proxy_type<0, 1, 0> rgr;
        proxy_type<0, 1, 1> rgg;
        proxy_type<0, 1, 2> rgb;
        proxy_type<0, 2, 0> rbr;
        proxy_type<0, 2, 1> rbg;
        proxy_type<0, 2, 2> rbb;
        proxy_type<1, 0, 0> grr;
        proxy_type<1, 0, 1> grg;
        proxy_type<1, 0, 2> grb;
        proxy_type<1, 1, 0> ggr;
        proxy_type<1, 1, 1> ggg;
        proxy_type<1, 1, 2> ggb;
        proxy_type<1, 2, 0> gbr;
        proxy_type<1, 2, 1> gbg;
        proxy_type<1, 2, 2> gbb;
        proxy_type<2, 0, 0> brr;
        proxy_type<2, 0, 1> brg;
        proxy_type<2, 0, 2> brb;
        proxy_type<2, 1, 0> bgr;
        proxy_type<2, 1, 1> bgg;
        proxy_type<2, 1, 2> bgb;
        proxy_type<2, 2, 0> bbr;
        proxy_type<2, 2, 1> bbg;
        proxy_type<2, 2, 2> bbb;

        proxy_type<0, 0, 0, 0> rrrr;
        proxy_type<0, 0, 0, 1> rrrg;
        proxy_type<0, 0, 0, 2> rrrb;
        proxy_type<0, 0, 1, 0> rrgr;
        proxy_type<0, 0, 1, 1> rrgg;
        proxy_type<0, 0, 1, 2> rrgb;
        proxy_type<0, 0, 2, 0> rrbr;
        proxy_type<0, 0, 2, 1> rrbg;
        proxy_type<0, 0, 2, 2> rrbb;
        proxy_type<0, 1, 0, 0> rgrr;
        proxy_type<0, 1, 0, 1> rgrg;
        proxy_type<0, 1, 0, 2> rgrb;
        proxy_type<0, 1, 1, 0> rggr;
        proxy_type<0, 1, 1, 1> rggg;
        proxy_type<0, 1, 1, 2> rggb;
        proxy_type<0, 1, 2, 0> rgbr;
        proxy_type<0, 1, 2, 1> rgbg;
        proxy_type<0, 1, 2, 2> rgbb;
        proxy_type<0, 2, 0, 0> rbrr;
        proxy_type<0, 2, 0, 1> rbrg;
        proxy_type<0, 2, 0, 2> rbrb;
        proxy_type<0, 2, 1, 0> rbgr;
        proxy_type<0, 2, 1, 1> rbgg;
        proxy_type<0, 2, 1, 2> rbgb;
        proxy_type<0, 2, 2, 0> rbbr;
        proxy_type<0, 2, 2, 1> rbbg;
        proxy_type<0, 2, 2, 2> rbbb;
        proxy_type<1, 0, 0, 0> grrr;
        proxy_type<1, 0, 0, 1> grrg;
        proxy_type<1, 0, 0, 2> grrb;
        proxy_type<1, 0, 1, 0> grgr;
        proxy_type<1, 0, 1, 1> grgg;
        proxy_type<1, 0, 1, 2> grgb;
        proxy_type<1, 0, 2, 0> grbr;
        proxy_type<1, 0, 2, 1> grbg;
        proxy_type<1, 0, 2, 2> grbb;
        proxy_type<1, 1, 0, 0> ggrr;
        proxy_type<1, 1, 0, 1> ggrg;
        proxy_type<1, 1, 0, 2> ggrb;
        proxy_type<1, 1, 1, 0> gggr;
        proxy_type<1, 1, 1, 1> gggg;
        proxy_type<1, 1, 1, 2> gggb;
        proxy_type<1, 1, 2, 0> ggbr;
        proxy_type<1, 1, 2, 1> ggbg;
        proxy_type<1, 1, 2, 2> ggbb;
        proxy_type<1, 2, 0, 0> gbrr;
        proxy_type<1, 2, 0, 1> gbrg;
        proxy_type<1, 2, 0, 2> gbrb;
        proxy_type<1, 2, 1, 0> gbgr;
        proxy_type<1, 2, 1, 1> gbgg;
        proxy_type<1, 2, 1, 2> gbgb;
        proxy_type<1, 2, 2, 0> gbbr;
        proxy_type<1, 2, 2, 1> gbbg;
        proxy_type<1, 2, 2, 2> gbbb;
        proxy_type<2, 0, 0, 0> brrr;
        proxy_type<2, 0, 0, 1> brrg;
        proxy_type<2, 0, 0, 2> brrb;
        proxy_type<2, 0, 1, 0> brgr;
        proxy_type<2, 0, 1, 1> brgg;
        proxy_type<2, 0, 1, 2> brgb;
        proxy_type<2, 0, 2, 0> brbr;
        proxy_type<2, 0, 2, 1> brbg;
        proxy_type<2, 0, 2, 2> brbb;
        proxy_type<2, 1, 0, 0> bgrr;
        proxy_type<2, 1, 0, 1> bgrg;
        proxy_type<2, 1, 0, 2> bgrb;
        proxy_type<2, 1, 1, 0> bggr;
        proxy_type<2, 1, 1, 1> bggg;
        proxy_type<2, 1, 1, 2> bggb;
        proxy_type<2, 1, 2, 0> bgbr;
        proxy_type<2, 1, 2, 1> bgbg;
        proxy_type<2, 1, 2, 2> bgbb;
        proxy_type<2, 2, 0, 0> bbrr;
        proxy_type<2, 2, 0, 1> bbrg;
        proxy_type<2, 2, 0, 2> bbrb;
        proxy_type<2, 2, 1, 0> bbgr;
        proxy_type<2, 2, 1, 1> bbgg;
        proxy_type<2, 2, 1, 2> bbgb;
        proxy_type<2, 2, 2, 0> bbbr;
        proxy_type<2, 2, 2, 1> bbbg;
        proxy_type<2, 2, 2, 2> bbbb;

        proxy_type<0> s;
        proxy_type<1> t;
        proxy_type<2> p;

        proxy_type<0, 0> ss;
        proxy_type<0, 1> st;
        proxy_type<0, 2> sp;
        proxy_type<1, 0> ts;
        proxy_type<1, 1> tt;
        proxy_type<1, 2> tp;
        proxy_type<2, 0> ps;
        proxy_type<2, 1> pt;
        proxy_type<2, 2> pp;

        proxy_type<0, 0, 0> sss;
        proxy_type<0, 0, 1> sst;
        proxy_type<0, 0, 2> ssp;
        proxy_type<0, 1, 0> sts;
        proxy_type<0, 1, 1> stt;
        proxy_type<0, 1, 2> stp;
        proxy_type<0, 2, 0> sps;
        proxy_type<0, 2, 1> spt;
        proxy_type<0, 2, 2> spp;
        proxy_type<1, 0, 0> tss;
        proxy_type<1, 0, 1> tst;
        proxy_type<1, 0, 2> tsp;
        proxy_type<1, 1, 0> tts;
        proxy_type<1, 1, 1> ttt;
        proxy_type<1, 1, 2> ttp;
        proxy_type<1, 2, 0> tps;
        proxy_type<1, 2, 1> tpt;
        proxy_type<1, 2, 2> tpp;
        proxy_type<2, 0, 0> pss;
        proxy_type<2, 0, 1> pst;
        proxy_type<2, 0, 2> psp;
        proxy_type<2, 1, 0> pts;
        proxy_type<2, 1, 1> ptt;
        proxy_type<2, 1, 2> ptp;
        proxy_type<2, 2, 0> pps;
        proxy_type<2, 2, 1> ppt;
        proxy_type<2, 2, 2> ppp;

        proxy_type<0, 0, 0, 0> ssss;
        proxy_type<0, 0, 0, 1> ssst;
        proxy_type<0, 0, 0, 2> sssp;
        proxy_type<0, 0, 1, 0> ssts;
        proxy_type<0, 0, 1, 1> sstt;
        proxy_type<0, 0, 1, 2> sstp;
        proxy_type<0, 0, 2, 0> ssps;
        proxy_type<0, 0, 2, 1> sspt;
        proxy_type<0, 0, 2, 2> sspp;
        proxy_type<0, 1, 0, 0> stss;
        proxy_type<0, 1, 0, 1> stst;
        proxy_type<0, 1, 0, 2> stsp;
        proxy_type<0, 1, 1, 0> stts;
        proxy_type<0, 1, 1, 1> sttt;
        proxy_type<0, 1, 1, 2> sttp;
        proxy_type<0, 1, 2, 0> stps;
        proxy_type<0, 1, 2, 1> stpt;
        proxy_type<0, 1, 2, 2> stpp;
        proxy_type<0, 2, 0, 0> spss;
        proxy_type<0, 2, 0, 1> spst;
        proxy_type<0, 2, 0, 2> spsp;
        proxy_type<0, 2, 1, 0> spts;
        proxy_type<0, 2, 1, 1> sptt;
        proxy_type<0, 2, 1, 2> sptp;
        proxy_type<0, 2, 2, 0> spps;
        proxy_type<0, 2, 2, 1> sppt;
        proxy_type<0, 2, 2, 2> sppp;
        proxy_type<1, 0, 0, 0> tsss;
        proxy_type<1, 0, 0, 1> tsst;
        proxy_type<1, 0, 0, 2> tssp;
        proxy_type<1, 0, 1, 0> tsts;
        proxy_type<1, 0, 1, 1> tstt;
        proxy_type<1, 0, 1, 2> tstp;
        proxy_type<1, 0, 2, 0> tsps;
        proxy_type<1, 0, 2, 1> tspt;
        proxy_type<1, 0, 2, 2> tspp;
        proxy_type<1, 1, 0, 0> ttss;
        proxy_type<1, 1, 0, 1> ttst;
        proxy_type<1, 1, 0, 2> ttsp;
        proxy_type<1, 1, 1, 0> ttts;
        proxy_type<1, 1, 1, 1> tttt;
        proxy_type<1, 1, 1, 2> tttp;
        proxy_type<1, 1, 2, 0> ttps;
        proxy_type<1, 1, 2, 1> ttpt;
        proxy_type<1, 1, 2, 2> ttpp;
        proxy_type<1, 2, 0, 0> tpss;
        proxy_type<1, 2, 0, 1> tpst;
        proxy_type<1, 2, 0, 2> tpsp;
        proxy_type<1, 2, 1, 0> tpts;
        proxy_type<1, 2, 1, 1> tptt;
        proxy_type<1, 2, 1, 2> tptp;
        proxy_type<1, 2, 2, 0> tpps;
        proxy_type<1, 2, 2, 1> tppt;
        proxy_type<1, 2, 2, 2> tppp;
        proxy_type<2, 0, 0, 0> psss;
        proxy_type<2, 0, 0, 1> psst;
        proxy_type<2, 0, 0, 2> pssp;
        proxy_type<2, 0, 1, 0> psts;
        proxy_type<2, 0, 1, 1> pstt;
        proxy_type<2, 0, 1, 2> pstp;
        proxy_type<2, 0, 2, 0> psps;
        proxy_type<2, 0, 2, 1> pspt;
        proxy_type<2, 0, 2, 2> pspp;
        proxy_type<2, 1, 0, 0> ptss;
        proxy_type<2, 1, 0, 1> ptst;
        proxy_type<2, 1, 0, 2> ptsp;
        proxy_type<2, 1, 1, 0> ptts;
        proxy_type<2, 1, 1, 1> pttt;
        proxy_type<2, 1, 1, 2> pttp;
        proxy_type<2, 1, 2, 0> ptps;
        proxy_type<2, 1, 2, 1> ptpt;
        proxy_type<2, 1, 2, 2> ptpp;
        proxy_type<2, 2, 0, 0> ppss;
        proxy_type<2, 2, 0, 1> ppst;
        proxy_type<2, 2, 0, 2> ppsp;
        proxy_type<2, 2, 1, 0> ppts;
        proxy_type<2, 2, 1, 1> pptt;
        proxy_type<2, 2, 1, 2> pptp;
        proxy_type<2, 2, 2, 0> ppps;
        proxy_type<2, 2, 2, 1> pppt;
        proxy_type<2, 2, 2, 2> pppp;
    };

    swizzle_impl()
        noexcept(std::is_nothrow_default_constructible<value_type>::value)
        : elems{}
    {
    }

    swizzle_impl(swizzle_impl const& other)
        noexcept(std::is_nothrow_copy_constructible<value_type>::value)
        : elems{other.elems[0], other.elems[1], other.elems[2]}
    {
    }

    swizzle_impl(swizzle_impl&& other)
        noexcept(std::is_nothrow_move_constructible<value_type>::value)
        : elems{std::move(other.elems[0]), std::move(other.elems[1]), std::move(other.elems[2])}
    {
    }

    template <typename X, typename Y, typename Z>
    swizzle_impl(X&& x, Y&& y, Z&& z)
        noexcept(ofxSwizzle::detail::conjunction_v<
            std::is_nothrow_move_constructible<value_type>,
            std::is_nothrow_constructible<value_type, X&&>,
            std::is_nothrow_constructible<value_type, Y&&>,
            std::is_nothrow_constructible<value_type, Z&&>>)
        : elems{
            static_cast<value_type>(std::forward<X>(x)),
            static_cast<value_type>(std::forward<Y>(y)),
            static_cast<value_type>(std::forward<Z>(z))}
    {
    }

    ~swizzle_impl()
        noexcept(std::is_nothrow_destructible<value_type>::value)
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i].~T();
        }
    }

    auto operator=(swizzle_impl const& other) &
        noexcept(std::is_nothrow_copy_assignable<value_type>::value)
        -> swizzle_impl&
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i] = other.elems[i];
        }
        return *this;
    }

    auto operator=(swizzle_impl&& other) &
        noexcept(std::is_nothrow_move_assignable<value_type>::value)
        -> swizzle_impl&
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i] = std::move(other.elems[i]);
        }
        return *this;
    }
};

template <typename T>
class swizzle_impl<T, 4>
{
private:
    using value_type = T;
    using size_type = std::size_t;
    static constexpr size_type vector_size = 4;

    template <std::size_t... Indices>
    using proxy_type = ofxSwizzle::detail::swizzle_proxy<
        value_type, vector_size, std::index_sequence<Indices...>,
        !ofxSwizzle::detail::has_duplicated(std::index_sequence<Indices...>())>;

protected:
    union
    {
        struct
        {
            value_type elems[vector_size];
        };

        proxy_type<0> x;
        proxy_type<1> y;
        proxy_type<2> z;
        proxy_type<3> w;

        proxy_type<0, 0> xx;
        proxy_type<0, 1> xy;
        proxy_type<0, 2> xz;
        proxy_type<0, 3> xw;
        proxy_type<1, 0> yx;
        proxy_type<1, 1> yy;
        proxy_type<1, 2> yz;
        proxy_type<1, 3> yw;
        proxy_type<2, 0> zx;
        proxy_type<2, 1> zy;
        proxy_type<2, 2> zz;
        proxy_type<2, 3> zw;
        proxy_type<3, 0> wx;
        proxy_type<3, 1> wy;
        proxy_type<3, 2> wz;
        proxy_type<3, 3> ww;

        proxy_type<0, 0, 0> xxx;
        proxy_type<0, 0, 1> xxy;
        proxy_type<0, 0, 2> xxz;
        proxy_type<0, 0, 3> xxw;
        proxy_type<0, 1, 0> xyx;
        proxy_type<0, 1, 1> xyy;
        proxy_type<0, 1, 2> xyz;
        proxy_type<0, 1, 3> xyw;
        proxy_type<0, 2, 0> xzx;
        proxy_type<0, 2, 1> xzy;
        proxy_type<0, 2, 2> xzz;
        proxy_type<0, 2, 3> xzw;
        proxy_type<0, 3, 0> xwx;
        proxy_type<0, 3, 1> xwy;
        proxy_type<0, 3, 2> xwz;
        proxy_type<0, 3, 3> xww;
        proxy_type<1, 0, 0> yxx;
        proxy_type<1, 0, 1> yxy;
        proxy_type<1, 0, 2> yxz;
        proxy_type<1, 0, 3> yxw;
        proxy_type<1, 1, 0> yyx;
        proxy_type<1, 1, 1> yyy;
        proxy_type<1, 1, 2> yyz;
        proxy_type<1, 1, 3> yyw;
        proxy_type<1, 2, 0> yzx;
        proxy_type<1, 2, 1> yzy;
        proxy_type<1, 2, 2> yzz;
        proxy_type<1, 2, 3> yzw;
        proxy_type<1, 3, 0> ywx;
        proxy_type<1, 3, 1> ywy;
        proxy_type<1, 3, 2> ywz;
        proxy_type<1, 3, 3> yww;
        proxy_type<2, 0, 0> zxx;
        proxy_type<2, 0, 1> zxy;
        proxy_type<2, 0, 2> zxz;
        proxy_type<2, 0, 3> zxw;
        proxy_type<2, 1, 0> zyx;
        proxy_type<2, 1, 1> zyy;
        proxy_type<2, 1, 2> zyz;
        proxy_type<2, 1, 3> zyw;
        proxy_type<2, 2, 0> zzx;
        proxy_type<2, 2, 1> zzy;
        proxy_type<2, 2, 2> zzz;
        proxy_type<2, 2, 3> zzw;
        proxy_type<2, 3, 0> zwx;
        proxy_type<2, 3, 1> zwy;
        proxy_type<2, 3, 2> zwz;
        proxy_type<2, 3, 3> zww;
        proxy_type<3, 0, 0> wxx;
        proxy_type<3, 0, 1> wxy;
        proxy_type<3, 0, 2> wxz;
        proxy_type<3, 0, 3> wxw;
        proxy_type<3, 1, 0> wyx;
        proxy_type<3, 1, 1> wyy;
        proxy_type<3, 1, 2> wyz;
        proxy_type<3, 1, 3> wyw;
        proxy_type<3, 2, 0> wzx;
        proxy_type<3, 2, 1> wzy;
        proxy_type<3, 2, 2> wzz;
        proxy_type<3, 2, 3> wzw;
        proxy_type<3, 3, 0> wwx;
        proxy_type<3, 3, 1> wwy;
        proxy_type<3, 3, 2> wwz;
        proxy_type<3, 3, 3> www;

        proxy_type<0, 0, 0, 0> xxxx;
        proxy_type<0, 0, 0, 1> xxxy;
        proxy_type<0, 0, 0, 2> xxxz;
        proxy_type<0, 0, 0, 3> xxxw;
        proxy_type<0, 0, 1, 0> xxyx;
        proxy_type<0, 0, 1, 1> xxyy;
        proxy_type<0, 0, 1, 2> xxyz;
        proxy_type<0, 0, 1, 3> xxyw;
        proxy_type<0, 0, 2, 0> xxzx;
        proxy_type<0, 0, 2, 1> xxzy;
        proxy_type<0, 0, 2, 2> xxzz;
        proxy_type<0, 0, 2, 3> xxzw;
        proxy_type<0, 0, 3, 0> xxwx;
        proxy_type<0, 0, 3, 1> xxwy;
        proxy_type<0, 0, 3, 2> xxwz;
        proxy_type<0, 0, 3, 3> xxww;
        proxy_type<0, 1, 0, 0> xyxx;
        proxy_type<0, 1, 0, 1> xyxy;
        proxy_type<0, 1, 0, 2> xyxz;
        proxy_type<0, 1, 0, 3> xyxw;
        proxy_type<0, 1, 1, 0> xyyx;
        proxy_type<0, 1, 1, 1> xyyy;
        proxy_type<0, 1, 1, 2> xyyz;
        proxy_type<0, 1, 1, 3> xyyw;
        proxy_type<0, 1, 2, 0> xyzx;
        proxy_type<0, 1, 2, 1> xyzy;
        proxy_type<0, 1, 2, 2> xyzz;
        proxy_type<0, 1, 2, 3> xyzw;
        proxy_type<0, 1, 3, 0> xywx;
        proxy_type<0, 1, 3, 1> xywy;
        proxy_type<0, 1, 3, 2> xywz;
        proxy_type<0, 1, 3, 3> xyww;
        proxy_type<0, 2, 0, 0> xzxx;
        proxy_type<0, 2, 0, 1> xzxy;
        proxy_type<0, 2, 0, 2> xzxz;
        proxy_type<0, 2, 0, 3> xzxw;
        proxy_type<0, 2, 1, 0> xzyx;
        proxy_type<0, 2, 1, 1> xzyy;
        proxy_type<0, 2, 1, 2> xzyz;
        proxy_type<0, 2, 1, 3> xzyw;
        proxy_type<0, 2, 2, 0> xzzx;
        proxy_type<0, 2, 2, 1> xzzy;
        proxy_type<0, 2, 2, 2> xzzz;
        proxy_type<0, 2, 2, 3> xzzw;
        proxy_type<0, 2, 3, 0> xzwx;
        proxy_type<0, 2, 3, 1> xzwy;
        proxy_type<0, 2, 3, 2> xzwz;
        proxy_type<0, 2, 3, 3> xzww;
        proxy_type<0, 3, 0, 0> xwxx;
        proxy_type<0, 3, 0, 1> xwxy;
        proxy_type<0, 3, 0, 2> xwxz;
        proxy_type<0, 3, 0, 3> xwxw;
        proxy_type<0, 3, 1, 0> xwyx;
        proxy_type<0, 3, 1, 1> xwyy;
        proxy_type<0, 3, 1, 2> xwyz;
        proxy_type<0, 3, 1, 3> xwyw;
        proxy_type<0, 3, 2, 0> xwzx;
        proxy_type<0, 3, 2, 1> xwzy;
        proxy_type<0, 3, 2, 2> xwzz;
        proxy_type<0, 3, 2, 3> xwzw;
        proxy_type<0, 3, 3, 0> xwwx;
        proxy_type<0, 3, 3, 1> xwwy;
        proxy_type<0, 3, 3, 2> xwwz;
        proxy_type<0, 3, 3, 3> xwww;
        proxy_type<1, 0, 0, 0> yxxx;
        proxy_type<1, 0, 0, 1> yxxy;
        proxy_type<1, 0, 0, 2> yxxz;
        proxy_type<1, 0, 0, 3> yxxw;
        proxy_type<1, 0, 1, 0> yxyx;
        proxy_type<1, 0, 1, 1> yxyy;
        proxy_type<1, 0, 1, 2> yxyz;
        proxy_type<1, 0, 1, 3> yxyw;
        proxy_type<1, 0, 2, 0> yxzx;
        proxy_type<1, 0, 2, 1> yxzy;
        proxy_type<1, 0, 2, 2> yxzz;
        proxy_type<1, 0, 2, 3> yxzw;
        proxy_type<1, 0, 3, 0> yxwx;
        proxy_type<1, 0, 3, 1> yxwy;
        proxy_type<1, 0, 3, 2> yxwz;
        proxy_type<1, 0, 3, 3> yxww;
        proxy_type<1, 1, 0, 0> yyxx;
        proxy_type<1, 1, 0, 1> yyxy;
        proxy_type<1, 1, 0, 2> yyxz;
        proxy_type<1, 1, 0, 3> yyxw;
        proxy_type<1, 1, 1, 0> yyyx;
        proxy_type<1, 1, 1, 1> yyyy;
        proxy_type<1, 1, 1, 2> yyyz;
        proxy_type<1, 1, 1, 3> yyyw;
        proxy_type<1, 1, 2, 0> yyzx;
        proxy_type<1, 1, 2, 1> yyzy;
        proxy_type<1, 1, 2, 2> yyzz;
        proxy_type<1, 1, 2, 3> yyzw;
        proxy_type<1, 1, 3, 0> yywx;
        proxy_type<1, 1, 3, 1> yywy;
        proxy_type<1, 1, 3, 2> yywz;
        proxy_type<1, 1, 3, 3> yyww;
        proxy_type<1, 2, 0, 0> yzxx;
        proxy_type<1, 2, 0, 1> yzxy;
        proxy_type<1, 2, 0, 2> yzxz;
        proxy_type<1, 2, 0, 3> yzxw;
        proxy_type<1, 2, 1, 0> yzyx;
        proxy_type<1, 2, 1, 1> yzyy;
        proxy_type<1, 2, 1, 2> yzyz;
        proxy_type<1, 2, 1, 3> yzyw;
        proxy_type<1, 2, 2, 0> yzzx;
        proxy_type<1, 2, 2, 1> yzzy;
        proxy_type<1, 2, 2, 2> yzzz;
        proxy_type<1, 2, 2, 3> yzzw;
        proxy_type<1, 2, 3, 0> yzwx;
        proxy_type<1, 2, 3, 1> yzwy;
        proxy_type<1, 2, 3, 2> yzwz;
        proxy_type<1, 2, 3, 3> yzww;
        proxy_type<1, 3, 0, 0> ywxx;
        proxy_type<1, 3, 0, 1> ywxy;
        proxy_type<1, 3, 0, 2> ywxz;
        proxy_type<1, 3, 0, 3> ywxw;
        proxy_type<1, 3, 1, 0> ywyx;
        proxy_type<1, 3, 1, 1> ywyy;
        proxy_type<1, 3, 1, 2> ywyz;
        proxy_type<1, 3, 1, 3> ywyw;
        proxy_type<1, 3, 2, 0> ywzx;
        proxy_type<1, 3, 2, 1> ywzy;
        proxy_type<1, 3, 2, 2> ywzz;
        proxy_type<1, 3, 2, 3> ywzw;
        proxy_type<1, 3, 3, 0> ywwx;
        proxy_type<1, 3, 3, 1> ywwy;
        proxy_type<1, 3, 3, 2> ywwz;
        proxy_type<1, 3, 3, 3> ywww;
        proxy_type<2, 0, 0, 0> zxxx;
        proxy_type<2, 0, 0, 1> zxxy;
        proxy_type<2, 0, 0, 2> zxxz;
        proxy_type<2, 0, 0, 3> zxxw;
        proxy_type<2, 0, 1, 0> zxyx;
        proxy_type<2, 0, 1, 1> zxyy;
        proxy_type<2, 0, 1, 2> zxyz;
        proxy_type<2, 0, 1, 3> zxyw;
        proxy_type<2, 0, 2, 0> zxzx;
        proxy_type<2, 0, 2, 1> zxzy;
        proxy_type<2, 0, 2, 2> zxzz;
        proxy_type<2, 0, 2, 3> zxzw;
        proxy_type<2, 0, 3, 0> zxwx;
        proxy_type<2, 0, 3, 1> zxwy;
        proxy_type<2, 0, 3, 2> zxwz;
        proxy_type<2, 0, 3, 3> zxww;
        proxy_type<2, 1, 0, 0> zyxx;
        proxy_type<2, 1, 0, 1> zyxy;
        proxy_type<2, 1, 0, 2> zyxz;
        proxy_type<2, 1, 0, 3> zyxw;
        proxy_type<2, 1, 1, 0> zyyx;
        proxy_type<2, 1, 1, 1> zyyy;
        proxy_type<2, 1, 1, 2> zyyz;
        proxy_type<2, 1, 1, 3> zyyw;
        proxy_type<2, 1, 2, 0> zyzx;
        proxy_type<2, 1, 2, 1> zyzy;
        proxy_type<2, 1, 2, 2> zyzz;
        proxy_type<2, 1, 2, 3> zyzw;
        proxy_type<2, 1, 3, 0> zywx;
        proxy_type<2, 1, 3, 1> zywy;
        proxy_type<2, 1, 3, 2> zywz;
        proxy_type<2, 1, 3, 3> zyww;
        proxy_type<2, 2, 0, 0> zzxx;
        proxy_type<2, 2, 0, 1> zzxy;
        proxy_type<2, 2, 0, 2> zzxz;
        proxy_type<2, 2, 0, 3> zzxw;
        proxy_type<2, 2, 1, 0> zzyx;
        proxy_type<2, 2, 1, 1> zzyy;
        proxy_type<2, 2, 1, 2> zzyz;
        proxy_type<2, 2, 1, 3> zzyw;
        proxy_type<2, 2, 2, 0> zzzx;
        proxy_type<2, 2, 2, 1> zzzy;
        proxy_type<2, 2, 2, 2> zzzz;
        proxy_type<2, 2, 2, 3> zzzw;
        proxy_type<2, 2, 3, 0> zzwx;
        proxy_type<2, 2, 3, 1> zzwy;
        proxy_type<2, 2, 3, 2> zzwz;
        proxy_type<2, 2, 3, 3> zzww;
        proxy_type<2, 3, 0, 0> zwxx;
        proxy_type<2, 3, 0, 1> zwxy;
        proxy_type<2, 3, 0, 2> zwxz;
        proxy_type<2, 3, 0, 3> zwxw;
        proxy_type<2, 3, 1, 0> zwyx;
        proxy_type<2, 3, 1, 1> zwyy;
        proxy_type<2, 3, 1, 2> zwyz;
        proxy_type<2, 3, 1, 3> zwyw;
        proxy_type<2, 3, 2, 0> zwzx;
        proxy_type<2, 3, 2, 1> zwzy;
        proxy_type<2, 3, 2, 2> zwzz;
        proxy_type<2, 3, 2, 3> zwzw;
        proxy_type<2, 3, 3, 0> zwwx;
        proxy_type<2, 3, 3, 1> zwwy;
        proxy_type<2, 3, 3, 2> zwwz;
        proxy_type<2, 3, 3, 3> zwww;
        proxy_type<3, 0, 0, 0> wxxx;
        proxy_type<3, 0, 0, 1> wxxy;
        proxy_type<3, 0, 0, 2> wxxz;
        proxy_type<3, 0, 0, 3> wxxw;
        proxy_type<3, 0, 1, 0> wxyx;
        proxy_type<3, 0, 1, 1> wxyy;
        proxy_type<3, 0, 1, 2> wxyz;
        proxy_type<3, 0, 1, 3> wxyw;
        proxy_type<3, 0, 2, 0> wxzx;
        proxy_type<3, 0, 2, 1> wxzy;
        proxy_type<3, 0, 2, 2> wxzz;
        proxy_type<3, 0, 2, 3> wxzw;
        proxy_type<3, 0, 3, 0> wxwx;
        proxy_type<3, 0, 3, 1> wxwy;
        proxy_type<3, 0, 3, 2> wxwz;
        proxy_type<3, 0, 3, 3> wxww;
        proxy_type<3, 1, 0, 0> wyxx;
        proxy_type<3, 1, 0, 1> wyxy;
        proxy_type<3, 1, 0, 2> wyxz;
        proxy_type<3, 1, 0, 3> wyxw;
        proxy_type<3, 1, 1, 0> wyyx;
        proxy_type<3, 1, 1, 1> wyyy;
        proxy_type<3, 1, 1, 2> wyyz;
        proxy_type<3, 1, 1, 3> wyyw;
        proxy_type<3, 1, 2, 0> wyzx;
        proxy_type<3, 1, 2, 1> wyzy;
        proxy_type<3, 1, 2, 2> wyzz;
        proxy_type<3, 1, 2, 3> wyzw;
        proxy_type<3, 1, 3, 0> wywx;
        proxy_type<3, 1, 3, 1> wywy;
        proxy_type<3, 1, 3, 2> wywz;
        proxy_type<3, 1, 3, 3> wyww;
        proxy_type<3, 2, 0, 0> wzxx;
        proxy_type<3, 2, 0, 1> wzxy;
        proxy_type<3, 2, 0, 2> wzxz;
        proxy_type<3, 2, 0, 3> wzxw;
        proxy_type<3, 2, 1, 0> wzyx;
        proxy_type<3, 2, 1, 1> wzyy;
        proxy_type<3, 2, 1, 2> wzyz;
        proxy_type<3, 2, 1, 3> wzyw;
        proxy_type<3, 2, 2, 0> wzzx;
        proxy_type<3, 2, 2, 1> wzzy;
        proxy_type<3, 2, 2, 2> wzzz;
        proxy_type<3, 2, 2, 3> wzzw;
        proxy_type<3, 2, 3, 0> wzwx;
        proxy_type<3, 2, 3, 1> wzwy;
        proxy_type<3, 2, 3, 2> wzwz;
        proxy_type<3, 2, 3, 3> wzww;
        proxy_type<3, 3, 0, 0> wwxx;
        proxy_type<3, 3, 0, 1> wwxy;
        proxy_type<3, 3, 0, 2> wwxz;
        proxy_type<3, 3, 0, 3> wwxw;
        proxy_type<3, 3, 1, 0> wwyx;
        proxy_type<3, 3, 1, 1> wwyy;
        proxy_type<3, 3, 1, 2> wwyz;
        proxy_type<3, 3, 1, 3> wwyw;
        proxy_type<3, 3, 2, 0> wwzx;
        proxy_type<3, 3, 2, 1> wwzy;
        proxy_type<3, 3, 2, 2> wwzz;
        proxy_type<3, 3, 2, 3> wwzw;
        proxy_type<3, 3, 3, 0> wwwx;
        proxy_type<3, 3, 3, 1> wwwy;
        proxy_type<3, 3, 3, 2> wwwz;
        proxy_type<3, 3, 3, 3> wwww;

        proxy_type<0> r;
        proxy_type<1> g;
        proxy_type<2> b;
        proxy_type<3> a;

        proxy_type<0, 0> rr;
        proxy_type<0, 1> rg;
        proxy_type<0, 2> rb;
        proxy_type<0, 3> ra;
        proxy_type<1, 0> gr;
        proxy_type<1, 1> gg;
        proxy_type<1, 2> gb;
        proxy_type<1, 3> ga;
        proxy_type<2, 0> br;
        proxy_type<2, 1> bg;
        proxy_type<2, 2> bb;
        proxy_type<2, 3> ba;
        proxy_type<3, 0> ar;
        proxy_type<3, 1> ag;
        proxy_type<3, 2> ab;
        proxy_type<3, 3> aa;

        proxy_type<0, 0, 0> rrr;
        proxy_type<0, 0, 1> rrg;
        proxy_type<0, 0, 2> rrb;
        proxy_type<0, 0, 3> rra;
        proxy_type<0, 1, 0> rgr;
        proxy_type<0, 1, 1> rgg;
        proxy_type<0, 1, 2> rgb;
        proxy_type<0, 1, 3> rga;
        proxy_type<0, 2, 0> rbr;
        proxy_type<0, 2, 1> rbg;
        proxy_type<0, 2, 2> rbb;
        proxy_type<0, 2, 3> rba;
        proxy_type<0, 3, 0> rar;
        proxy_type<0, 3, 1> rag;
        proxy_type<0, 3, 2> rab;
        proxy_type<0, 3, 3> raa;
        proxy_type<1, 0, 0> grr;
        proxy_type<1, 0, 1> grg;
        proxy_type<1, 0, 2> grb;
        proxy_type<1, 0, 3> gra;
        proxy_type<1, 1, 0> ggr;
        proxy_type<1, 1, 1> ggg;
        proxy_type<1, 1, 2> ggb;
        proxy_type<1, 1, 3> gga;
        proxy_type<1, 2, 0> gbr;
        proxy_type<1, 2, 1> gbg;
        proxy_type<1, 2, 2> gbb;
        proxy_type<1, 2, 3> gba;
        proxy_type<1, 3, 0> gar;
        proxy_type<1, 3, 1> gag;
        proxy_type<1, 3, 2> gab;
        proxy_type<1, 3, 3> gaa;
        proxy_type<2, 0, 0> brr;
        proxy_type<2, 0, 1> brg;
        proxy_type<2, 0, 2> brb;
        proxy_type<2, 0, 3> bra;
        proxy_type<2, 1, 0> bgr;
        proxy_type<2, 1, 1> bgg;
        proxy_type<2, 1, 2> bgb;
        proxy_type<2, 1, 3> bga;
        proxy_type<2, 2, 0> bbr;
        proxy_type<2, 2, 1> bbg;
        proxy_type<2, 2, 2> bbb;
        proxy_type<2, 2, 3> bba;
        proxy_type<2, 3, 0> bar;
        proxy_type<2, 3, 1> bag;
        proxy_type<2, 3, 2> bab;
        proxy_type<2, 3, 3> baa;
        proxy_type<3, 0, 0> arr;
        proxy_type<3, 0, 1> arg;
        proxy_type<3, 0, 2> arb;
        proxy_type<3, 0, 3> ara;
        proxy_type<3, 1, 0> agr;
        proxy_type<3, 1, 1> agg;
        proxy_type<3, 1, 2> agb;
        proxy_type<3, 1, 3> aga;
        proxy_type<3, 2, 0> abr;
        proxy_type<3, 2, 1> abg;
        proxy_type<3, 2, 2> abb;
        proxy_type<3, 2, 3> aba;
        proxy_type<3, 3, 0> aar;
        proxy_type<3, 3, 1> aag;
        proxy_type<3, 3, 2> aab;
        proxy_type<3, 3, 3> aaa;

        proxy_type<0, 0, 0, 0> rrrr;
        proxy_type<0, 0, 0, 1> rrrg;
        proxy_type<0, 0, 0, 2> rrrb;
        proxy_type<0, 0, 0, 3> rrra;
        proxy_type<0, 0, 1, 0> rrgr;
        proxy_type<0, 0, 1, 1> rrgg;
        proxy_type<0, 0, 1, 2> rrgb;
        proxy_type<0, 0, 1, 3> rrga;
        proxy_type<0, 0, 2, 0> rrbr;
        proxy_type<0, 0, 2, 1> rrbg;
        proxy_type<0, 0, 2, 2> rrbb;
        proxy_type<0, 0, 2, 3> rrba;
        proxy_type<0, 0, 3, 0> rrar;
        proxy_type<0, 0, 3, 1> rrag;
        proxy_type<0, 0, 3, 2> rrab;
        proxy_type<0, 0, 3, 3> rraa;
        proxy_type<0, 1, 0, 0> rgrr;
        proxy_type<0, 1, 0, 1> rgrg;
        proxy_type<0, 1, 0, 2> rgrb;
        proxy_type<0, 1, 0, 3> rgra;
        proxy_type<0, 1, 1, 0> rggr;
        proxy_type<0, 1, 1, 1> rggg;
        proxy_type<0, 1, 1, 2> rggb;
        proxy_type<0, 1, 1, 3> rgga;
        proxy_type<0, 1, 2, 0> rgbr;
        proxy_type<0, 1, 2, 1> rgbg;
        proxy_type<0, 1, 2, 2> rgbb;
        proxy_type<0, 1, 2, 3> rgba;
        proxy_type<0, 1, 3, 0> rgar;
        proxy_type<0, 1, 3, 1> rgag;
        proxy_type<0, 1, 3, 2> rgab;
        proxy_type<0, 1, 3, 3> rgaa;
        proxy_type<0, 2, 0, 0> rbrr;
        proxy_type<0, 2, 0, 1> rbrg;
        proxy_type<0, 2, 0, 2> rbrb;
        proxy_type<0, 2, 0, 3> rbra;
        proxy_type<0, 2, 1, 0> rbgr;
        proxy_type<0, 2, 1, 1> rbgg;
        proxy_type<0, 2, 1, 2> rbgb;
        proxy_type<0, 2, 1, 3> rbga;
        proxy_type<0, 2, 2, 0> rbbr;
        proxy_type<0, 2, 2, 1> rbbg;
        proxy_type<0, 2, 2, 2> rbbb;
        proxy_type<0, 2, 2, 3> rbba;
        proxy_type<0, 2, 3, 0> rbar;
        proxy_type<0, 2, 3, 1> rbag;
        proxy_type<0, 2, 3, 2> rbab;
        proxy_type<0, 2, 3, 3> rbaa;
        proxy_type<0, 3, 0, 0> rarr;
        proxy_type<0, 3, 0, 1> rarg;
        proxy_type<0, 3, 0, 2> rarb;
        proxy_type<0, 3, 0, 3> rara;
        proxy_type<0, 3, 1, 0> ragr;
        proxy_type<0, 3, 1, 1> ragg;
        proxy_type<0, 3, 1, 2> ragb;
        proxy_type<0, 3, 1, 3> raga;
        proxy_type<0, 3, 2, 0> rabr;
        proxy_type<0, 3, 2, 1> rabg;
        proxy_type<0, 3, 2, 2> rabb;
        proxy_type<0, 3, 2, 3> raba;
        proxy_type<0, 3, 3, 0> raar;
        proxy_type<0, 3, 3, 1> raag;
        proxy_type<0, 3, 3, 2> raab;
        proxy_type<0, 3, 3, 3> raaa;
        proxy_type<1, 0, 0, 0> grrr;
        proxy_type<1, 0, 0, 1> grrg;
        proxy_type<1, 0, 0, 2> grrb;
        proxy_type<1, 0, 0, 3> grra;
        proxy_type<1, 0, 1, 0> grgr;
        proxy_type<1, 0, 1, 1> grgg;
        proxy_type<1, 0, 1, 2> grgb;
        proxy_type<1, 0, 1, 3> grga;
        proxy_type<1, 0, 2, 0> grbr;
        proxy_type<1, 0, 2, 1> grbg;
        proxy_type<1, 0, 2, 2> grbb;
        proxy_type<1, 0, 2, 3> grba;
        proxy_type<1, 0, 3, 0> grar;
        proxy_type<1, 0, 3, 1> grag;
        proxy_type<1, 0, 3, 2> grab;
        proxy_type<1, 0, 3, 3> graa;
        proxy_type<1, 1, 0, 0> ggrr;
        proxy_type<1, 1, 0, 1> ggrg;
        proxy_type<1, 1, 0, 2> ggrb;
        proxy_type<1, 1, 0, 3> ggra;
        proxy_type<1, 1, 1, 0> gggr;
        proxy_type<1, 1, 1, 1> gggg;
        proxy_type<1, 1, 1, 2> gggb;
        proxy_type<1, 1, 1, 3> ggga;
        proxy_type<1, 1, 2, 0> ggbr;
        proxy_type<1, 1, 2, 1> ggbg;
        proxy_type<1, 1, 2, 2> ggbb;
        proxy_type<1, 1, 2, 3> ggba;
        proxy_type<1, 1, 3, 0> ggar;
        proxy_type<1, 1, 3, 1> ggag;
        proxy_type<1, 1, 3, 2> ggab;
        proxy_type<1, 1, 3, 3> ggaa;
        proxy_type<1, 2, 0, 0> gbrr;
        proxy_type<1, 2, 0, 1> gbrg;
        proxy_type<1, 2, 0, 2> gbrb;
        proxy_type<1, 2, 0, 3> gbra;
        proxy_type<1, 2, 1, 0> gbgr;
        proxy_type<1, 2, 1, 1> gbgg;
        proxy_type<1, 2, 1, 2> gbgb;
        proxy_type<1, 2, 1, 3> gbga;
        proxy_type<1, 2, 2, 0> gbbr;
        proxy_type<1, 2, 2, 1> gbbg;
        proxy_type<1, 2, 2, 2> gbbb;
        proxy_type<1, 2, 2, 3> gbba;
        proxy_type<1, 2, 3, 0> gbar;
        proxy_type<1, 2, 3, 1> gbag;
        proxy_type<1, 2, 3, 2> gbab;
        proxy_type<1, 2, 3, 3> gbaa;
        proxy_type<1, 3, 0, 0> garr;
        proxy_type<1, 3, 0, 1> garg;
        proxy_type<1, 3, 0, 2> garb;
        proxy_type<1, 3, 0, 3> gara;
        proxy_type<1, 3, 1, 0> gagr;
        proxy_type<1, 3, 1, 1> gagg;
        proxy_type<1, 3, 1, 2> gagb;
        proxy_type<1, 3, 1, 3> gaga;
        proxy_type<1, 3, 2, 0> gabr;
        proxy_type<1, 3, 2, 1> gabg;
        proxy_type<1, 3, 2, 2> gabb;
        proxy_type<1, 3, 2, 3> gaba;
        proxy_type<1, 3, 3, 0> gaar;
        proxy_type<1, 3, 3, 1> gaag;
        proxy_type<1, 3, 3, 2> gaab;
        proxy_type<1, 3, 3, 3> gaaa;
        proxy_type<2, 0, 0, 0> brrr;
        proxy_type<2, 0, 0, 1> brrg;
        proxy_type<2, 0, 0, 2> brrb;
        proxy_type<2, 0, 0, 3> brra;
        proxy_type<2, 0, 1, 0> brgr;
        proxy_type<2, 0, 1, 1> brgg;
        proxy_type<2, 0, 1, 2> brgb;
        proxy_type<2, 0, 1, 3> brga;
        proxy_type<2, 0, 2, 0> brbr;
        proxy_type<2, 0, 2, 1> brbg;
        proxy_type<2, 0, 2, 2> brbb;
        proxy_type<2, 0, 2, 3> brba;
        proxy_type<2, 0, 3, 0> brar;
        proxy_type<2, 0, 3, 1> brag;
        proxy_type<2, 0, 3, 2> brab;
        proxy_type<2, 0, 3, 3> braa;
        proxy_type<2, 1, 0, 0> bgrr;
        proxy_type<2, 1, 0, 1> bgrg;
        proxy_type<2, 1, 0, 2> bgrb;
        proxy_type<2, 1, 0, 3> bgra;
        proxy_type<2, 1, 1, 0> bggr;
        proxy_type<2, 1, 1, 1> bggg;
        proxy_type<2, 1, 1, 2> bggb;
        proxy_type<2, 1, 1, 3> bgga;
        proxy_type<2, 1, 2, 0> bgbr;
        proxy_type<2, 1, 2, 1> bgbg;
        proxy_type<2, 1, 2, 2> bgbb;
        proxy_type<2, 1, 2, 3> bgba;
        proxy_type<2, 1, 3, 0> bgar;
        proxy_type<2, 1, 3, 1> bgag;
        proxy_type<2, 1, 3, 2> bgab;
        proxy_type<2, 1, 3, 3> bgaa;
        proxy_type<2, 2, 0, 0> bbrr;
        proxy_type<2, 2, 0, 1> bbrg;
        proxy_type<2, 2, 0, 2> bbrb;
        proxy_type<2, 2, 0, 3> bbra;
        proxy_type<2, 2, 1, 0> bbgr;
        proxy_type<2, 2, 1, 1> bbgg;
        proxy_type<2, 2, 1, 2> bbgb;
        proxy_type<2, 2, 1, 3> bbga;
        proxy_type<2, 2, 2, 0> bbbr;
        proxy_type<2, 2, 2, 1> bbbg;
        proxy_type<2, 2, 2, 2> bbbb;
        proxy_type<2, 2, 2, 3> bbba;
        proxy_type<2, 2, 3, 0> bbar;
        proxy_type<2, 2, 3, 1> bbag;
        proxy_type<2, 2, 3, 2> bbab;
        proxy_type<2, 2, 3, 3> bbaa;
        proxy_type<2, 3, 0, 0> barr;
        proxy_type<2, 3, 0, 1> barg;
        proxy_type<2, 3, 0, 2> barb;
        proxy_type<2, 3, 0, 3> bara;
        proxy_type<2, 3, 1, 0> bagr;
        proxy_type<2, 3, 1, 1> bagg;
        proxy_type<2, 3, 1, 2> bagb;
        proxy_type<2, 3, 1, 3> baga;
        proxy_type<2, 3, 2, 0> babr;
        proxy_type<2, 3, 2, 1> babg;
        proxy_type<2, 3, 2, 2> babb;
        proxy_type<2, 3, 2, 3> baba;
        proxy_type<2, 3, 3, 0> baar;
        proxy_type<2, 3, 3, 1> baag;
        proxy_type<2, 3, 3, 2> baab;
        proxy_type<2, 3, 3, 3> baaa;
        proxy_type<3, 0, 0, 0> arrr;
        proxy_type<3, 0, 0, 1> arrg;
        proxy_type<3, 0, 0, 2> arrb;
        proxy_type<3, 0, 0, 3> arra;
        proxy_type<3, 0, 1, 0> argr;
        proxy_type<3, 0, 1, 1> argg;
        proxy_type<3, 0, 1, 2> argb;
        proxy_type<3, 0, 1, 3> arga;
        proxy_type<3, 0, 2, 0> arbr;
        proxy_type<3, 0, 2, 1> arbg;
        proxy_type<3, 0, 2, 2> arbb;
        proxy_type<3, 0, 2, 3> arba;
        proxy_type<3, 0, 3, 0> arar;
        proxy_type<3, 0, 3, 1> arag;
        proxy_type<3, 0, 3, 2> arab;
        proxy_type<3, 0, 3, 3> araa;
        proxy_type<3, 1, 0, 0> agrr;
        proxy_type<3, 1, 0, 1> agrg;
        proxy_type<3, 1, 0, 2> agrb;
        proxy_type<3, 1, 0, 3> agra;
        proxy_type<3, 1, 1, 0> aggr;
        proxy_type<3, 1, 1, 1> aggg;
        proxy_type<3, 1, 1, 2> aggb;
        proxy_type<3, 1, 1, 3> agga;
        proxy_type<3, 1, 2, 0> agbr;
        proxy_type<3, 1, 2, 1> agbg;
        proxy_type<3, 1, 2, 2> agbb;
        proxy_type<3, 1, 2, 3> agba;
        proxy_type<3, 1, 3, 0> agar;
        proxy_type<3, 1, 3, 1> agag;
        proxy_type<3, 1, 3, 2> agab;
        proxy_type<3, 1, 3, 3> agaa;
        proxy_type<3, 2, 0, 0> abrr;
        proxy_type<3, 2, 0, 1> abrg;
        proxy_type<3, 2, 0, 2> abrb;
        proxy_type<3, 2, 0, 3> abra;
        proxy_type<3, 2, 1, 0> abgr;
        proxy_type<3, 2, 1, 1> abgg;
        proxy_type<3, 2, 1, 2> abgb;
        proxy_type<3, 2, 1, 3> abga;
        proxy_type<3, 2, 2, 0> abbr;
        proxy_type<3, 2, 2, 1> abbg;
        proxy_type<3, 2, 2, 2> abbb;
        proxy_type<3, 2, 2, 3> abba;
        proxy_type<3, 2, 3, 0> abar;
        proxy_type<3, 2, 3, 1> abag;
        proxy_type<3, 2, 3, 2> abab;
        proxy_type<3, 2, 3, 3> abaa;
        proxy_type<3, 3, 0, 0> aarr;
        proxy_type<3, 3, 0, 1> aarg;
        proxy_type<3, 3, 0, 2> aarb;
        proxy_type<3, 3, 0, 3> aara;
        proxy_type<3, 3, 1, 0> aagr;
        proxy_type<3, 3, 1, 1> aagg;
        proxy_type<3, 3, 1, 2> aagb;
        proxy_type<3, 3, 1, 3> aaga;
        proxy_type<3, 3, 2, 0> aabr;
        proxy_type<3, 3, 2, 1> aabg;
        proxy_type<3, 3, 2, 2> aabb;
        proxy_type<3, 3, 2, 3> aaba;
        proxy_type<3, 3, 3, 0> aaar;
        proxy_type<3, 3, 3, 1> aaag;
        proxy_type<3, 3, 3, 2> aaab;
        proxy_type<3, 3, 3, 3> aaaa;

        proxy_type<0> s;
        proxy_type<1> t;
        proxy_type<2> p;
        proxy_type<3> q;

        proxy_type<0, 0> ss;
        proxy_type<0, 1> st;
        proxy_type<0, 2> sp;
        proxy_type<0, 3> sq;
        proxy_type<1, 0> ts;
        proxy_type<1, 1> tt;
        proxy_type<1, 2> tp;
        proxy_type<1, 3> tq;
        proxy_type<2, 0> ps;
        proxy_type<2, 1> pt;
        proxy_type<2, 2> pp;
        proxy_type<2, 3> pq;
        proxy_type<3, 0> qs;
        proxy_type<3, 1> qt;
        proxy_type<3, 2> qp;
        proxy_type<3, 3> qq;

        proxy_type<0, 0, 0> sss;
        proxy_type<0, 0, 1> sst;
        proxy_type<0, 0, 2> ssp;
        proxy_type<0, 0, 3> ssq;
        proxy_type<0, 1, 0> sts;
        proxy_type<0, 1, 1> stt;
        proxy_type<0, 1, 2> stp;
        proxy_type<0, 1, 3> stq;
        proxy_type<0, 2, 0> sps;
        proxy_type<0, 2, 1> spt;
        proxy_type<0, 2, 2> spp;
        proxy_type<0, 2, 3> spq;
        proxy_type<0, 3, 0> sqs;
        proxy_type<0, 3, 1> sqt;
        proxy_type<0, 3, 2> sqp;
        proxy_type<0, 3, 3> sqq;
        proxy_type<1, 0, 0> tss;
        proxy_type<1, 0, 1> tst;
        proxy_type<1, 0, 2> tsp;
        proxy_type<1, 0, 3> tsq;
        proxy_type<1, 1, 0> tts;
        proxy_type<1, 1, 1> ttt;
        proxy_type<1, 1, 2> ttp;
        proxy_type<1, 1, 3> ttq;
        proxy_type<1, 2, 0> tps;
        proxy_type<1, 2, 1> tpt;
        proxy_type<1, 2, 2> tpp;
        proxy_type<1, 2, 3> tpq;
        proxy_type<1, 3, 0> tqs;
        proxy_type<1, 3, 1> tqt;
        proxy_type<1, 3, 2> tqp;
        proxy_type<1, 3, 3> tqq;
        proxy_type<2, 0, 0> pss;
        proxy_type<2, 0, 1> pst;
        proxy_type<2, 0, 2> psp;
        proxy_type<2, 0, 3> psq;
        proxy_type<2, 1, 0> pts;
        proxy_type<2, 1, 1> ptt;
        proxy_type<2, 1, 2> ptp;
        proxy_type<2, 1, 3> ptq;
        proxy_type<2, 2, 0> pps;
        proxy_type<2, 2, 1> ppt;
        proxy_type<2, 2, 2> ppp;
        proxy_type<2, 2, 3> ppq;
        proxy_type<2, 3, 0> pqs;
        proxy_type<2, 3, 1> pqt;
        proxy_type<2, 3, 2> pqp;
        proxy_type<2, 3, 3> pqq;
        proxy_type<3, 0, 0> qss;
        proxy_type<3, 0, 1> qst;
        proxy_type<3, 0, 2> qsp;
        proxy_type<3, 0, 3> qsq;
        proxy_type<3, 1, 0> qts;
        proxy_type<3, 1, 1> qtt;
        proxy_type<3, 1, 2> qtp;
        proxy_type<3, 1, 3> qtq;
        proxy_type<3, 2, 0> qps;
        proxy_type<3, 2, 1> qpt;
        proxy_type<3, 2, 2> qpp;
        proxy_type<3, 2, 3> qpq;
        proxy_type<3, 3, 0> qqs;
        proxy_type<3, 3, 1> qqt;
        proxy_type<3, 3, 2> qqp;
        proxy_type<3, 3, 3> qqq;

        proxy_type<0, 0, 0, 0> ssss;
        proxy_type<0, 0, 0, 1> ssst;
        proxy_type<0, 0, 0, 2> sssp;
        proxy_type<0, 0, 0, 3> sssq;
        proxy_type<0, 0, 1, 0> ssts;
        proxy_type<0, 0, 1, 1> sstt;
        proxy_type<0, 0, 1, 2> sstp;
        proxy_type<0, 0, 1, 3> sstq;
        proxy_type<0, 0, 2, 0> ssps;
        proxy_type<0, 0, 2, 1> sspt;
        proxy_type<0, 0, 2, 2> sspp;
        proxy_type<0, 0, 2, 3> sspq;
        proxy_type<0, 0, 3, 0> ssqs;
        proxy_type<0, 0, 3, 1> ssqt;
        proxy_type<0, 0, 3, 2> ssqp;
        proxy_type<0, 0, 3, 3> ssqq;
        proxy_type<0, 1, 0, 0> stss;
        proxy_type<0, 1, 0, 1> stst;
        proxy_type<0, 1, 0, 2> stsp;
        proxy_type<0, 1, 0, 3> stsq;
        proxy_type<0, 1, 1, 0> stts;
        proxy_type<0, 1, 1, 1> sttt;
        proxy_type<0, 1, 1, 2> sttp;
        proxy_type<0, 1, 1, 3> sttq;
        proxy_type<0, 1, 2, 0> stps;
        proxy_type<0, 1, 2, 1> stpt;
        proxy_type<0, 1, 2, 2> stpp;
        proxy_type<0, 1, 2, 3> stpq;
        proxy_type<0, 1, 3, 0> stqs;
        proxy_type<0, 1, 3, 1> stqt;
        proxy_type<0, 1, 3, 2> stqp;
        proxy_type<0, 1, 3, 3> stqq;
        proxy_type<0, 2, 0, 0> spss;
        proxy_type<0, 2, 0, 1> spst;
        proxy_type<0, 2, 0, 2> spsp;
        proxy_type<0, 2, 0, 3> spsq;
        proxy_type<0, 2, 1, 0> spts;
        proxy_type<0, 2, 1, 1> sptt;
        proxy_type<0, 2, 1, 2> sptp;
        proxy_type<0, 2, 1, 3> sptq;
        proxy_type<0, 2, 2, 0> spps;
        proxy_type<0, 2, 2, 1> sppt;
        proxy_type<0, 2, 2, 2> sppp;
        proxy_type<0, 2, 2, 3> sppq;
        proxy_type<0, 2, 3, 0> spqs;
        proxy_type<0, 2, 3, 1> spqt;
        proxy_type<0, 2, 3, 2> spqp;
        proxy_type<0, 2, 3, 3> spqq;
        proxy_type<0, 3, 0, 0> sqss;
        proxy_type<0, 3, 0, 1> sqst;
        proxy_type<0, 3, 0, 2> sqsp;
        proxy_type<0, 3, 0, 3> sqsq;
        proxy_type<0, 3, 1, 0> sqts;
        proxy_type<0, 3, 1, 1> sqtt;
        proxy_type<0, 3, 1, 2> sqtp;
        proxy_type<0, 3, 1, 3> sqtq;
        proxy_type<0, 3, 2, 0> sqps;
        proxy_type<0, 3, 2, 1> sqpt;
        proxy_type<0, 3, 2, 2> sqpp;
        proxy_type<0, 3, 2, 3> sqpq;
        proxy_type<0, 3, 3, 0> sqqs;
        proxy_type<0, 3, 3, 1> sqqt;
        proxy_type<0, 3, 3, 2> sqqp;
        proxy_type<0, 3, 3, 3> sqqq;
        proxy_type<1, 0, 0, 0> tsss;
        proxy_type<1, 0, 0, 1> tsst;
        proxy_type<1, 0, 0, 2> tssp;
        proxy_type<1, 0, 0, 3> tssq;
        proxy_type<1, 0, 1, 0> tsts;
        proxy_type<1, 0, 1, 1> tstt;
        proxy_type<1, 0, 1, 2> tstp;
        proxy_type<1, 0, 1, 3> tstq;
        proxy_type<1, 0, 2, 0> tsps;
        proxy_type<1, 0, 2, 1> tspt;
        proxy_type<1, 0, 2, 2> tspp;
        proxy_type<1, 0, 2, 3> tspq;
        proxy_type<1, 0, 3, 0> tsqs;
        proxy_type<1, 0, 3, 1> tsqt;
        proxy_type<1, 0, 3, 2> tsqp;
        proxy_type<1, 0, 3, 3> tsqq;
        proxy_type<1, 1, 0, 0> ttss;
        proxy_type<1, 1, 0, 1> ttst;
        proxy_type<1, 1, 0, 2> ttsp;
        proxy_type<1, 1, 0, 3> ttsq;
        proxy_type<1, 1, 1, 0> ttts;
        proxy_type<1, 1, 1, 1> tttt;
        proxy_type<1, 1, 1, 2> tttp;
        proxy_type<1, 1, 1, 3> tttq;
        proxy_type<1, 1, 2, 0> ttps;
        proxy_type<1, 1, 2, 1> ttpt;
        proxy_type<1, 1, 2, 2> ttpp;
        proxy_type<1, 1, 2, 3> ttpq;
        proxy_type<1, 1, 3, 0> ttqs;
        proxy_type<1, 1, 3, 1> ttqt;
        proxy_type<1, 1, 3, 2> ttqp;
        proxy_type<1, 1, 3, 3> ttqq;
        proxy_type<1, 2, 0, 0> tpss;
        proxy_type<1, 2, 0, 1> tpst;
        proxy_type<1, 2, 0, 2> tpsp;
        proxy_type<1, 2, 0, 3> tpsq;
        proxy_type<1, 2, 1, 0> tpts;
        proxy_type<1, 2, 1, 1> tptt;
        proxy_type<1, 2, 1, 2> tptp;
        proxy_type<1, 2, 1, 3> tptq;
        proxy_type<1, 2, 2, 0> tpps;
        proxy_type<1, 2, 2, 1> tppt;
        proxy_type<1, 2, 2, 2> tppp;
        proxy_type<1, 2, 2, 3> tppq;
        proxy_type<1, 2, 3, 0> tpqs;
        proxy_type<1, 2, 3, 1> tpqt;
        proxy_type<1, 2, 3, 2> tpqp;
        proxy_type<1, 2, 3, 3> tpqq;
        proxy_type<1, 3, 0, 0> tqss;
        proxy_type<1, 3, 0, 1> tqst;
        proxy_type<1, 3, 0, 2> tqsp;
        proxy_type<1, 3, 0, 3> tqsq;
        proxy_type<1, 3, 1, 0> tqts;
        proxy_type<1, 3, 1, 1> tqtt;
        proxy_type<1, 3, 1, 2> tqtp;
        proxy_type<1, 3, 1, 3> tqtq;
        proxy_type<1, 3, 2, 0> tqps;
        proxy_type<1, 3, 2, 1> tqpt;
        proxy_type<1, 3, 2, 2> tqpp;
        proxy_type<1, 3, 2, 3> tqpq;
        proxy_type<1, 3, 3, 0> tqqs;
        proxy_type<1, 3, 3, 1> tqqt;
        proxy_type<1, 3, 3, 2> tqqp;
        proxy_type<1, 3, 3, 3> tqqq;
        proxy_type<2, 0, 0, 0> psss;
        proxy_type<2, 0, 0, 1> psst;
        proxy_type<2, 0, 0, 2> pssp;
        proxy_type<2, 0, 0, 3> pssq;
        proxy_type<2, 0, 1, 0> psts;
        proxy_type<2, 0, 1, 1> pstt;
        proxy_type<2, 0, 1, 2> pstp;
        proxy_type<2, 0, 1, 3> pstq;
        proxy_type<2, 0, 2, 0> psps;
        proxy_type<2, 0, 2, 1> pspt;
        proxy_type<2, 0, 2, 2> pspp;
        proxy_type<2, 0, 2, 3> pspq;
        proxy_type<2, 0, 3, 0> psqs;
        proxy_type<2, 0, 3, 1> psqt;
        proxy_type<2, 0, 3, 2> psqp;
        proxy_type<2, 0, 3, 3> psqq;
        proxy_type<2, 1, 0, 0> ptss;
        proxy_type<2, 1, 0, 1> ptst;
        proxy_type<2, 1, 0, 2> ptsp;
        proxy_type<2, 1, 0, 3> ptsq;
        proxy_type<2, 1, 1, 0> ptts;
        proxy_type<2, 1, 1, 1> pttt;
        proxy_type<2, 1, 1, 2> pttp;
        proxy_type<2, 1, 1, 3> pttq;
        proxy_type<2, 1, 2, 0> ptps;
        proxy_type<2, 1, 2, 1> ptpt;
        proxy_type<2, 1, 2, 2> ptpp;
        proxy_type<2, 1, 2, 3> ptpq;
        proxy_type<2, 1, 3, 0> ptqs;
        proxy_type<2, 1, 3, 1> ptqt;
        proxy_type<2, 1, 3, 2> ptqp;
        proxy_type<2, 1, 3, 3> ptqq;
        proxy_type<2, 2, 0, 0> ppss;
        proxy_type<2, 2, 0, 1> ppst;
        proxy_type<2, 2, 0, 2> ppsp;
        proxy_type<2, 2, 0, 3> ppsq;
        proxy_type<2, 2, 1, 0> ppts;
        proxy_type<2, 2, 1, 1> pptt;
        proxy_type<2, 2, 1, 2> pptp;
        proxy_type<2, 2, 1, 3> pptq;
        proxy_type<2, 2, 2, 0> ppps;
        proxy_type<2, 2, 2, 1> pppt;
        proxy_type<2, 2, 2, 2> pppp;
        proxy_type<2, 2, 2, 3> pppq;
        proxy_type<2, 2, 3, 0> ppqs;
        proxy_type<2, 2, 3, 1> ppqt;
        proxy_type<2, 2, 3, 2> ppqp;
        proxy_type<2, 2, 3, 3> ppqq;
        proxy_type<2, 3, 0, 0> pqss;
        proxy_type<2, 3, 0, 1> pqst;
        proxy_type<2, 3, 0, 2> pqsp;
        proxy_type<2, 3, 0, 3> pqsq;
        proxy_type<2, 3, 1, 0> pqts;
        proxy_type<2, 3, 1, 1> pqtt;
        proxy_type<2, 3, 1, 2> pqtp;
        proxy_type<2, 3, 1, 3> pqtq;
        proxy_type<2, 3, 2, 0> pqps;
        proxy_type<2, 3, 2, 1> pqpt;
        proxy_type<2, 3, 2, 2> pqpp;
        proxy_type<2, 3, 2, 3> pqpq;
        proxy_type<2, 3, 3, 0> pqqs;
        proxy_type<2, 3, 3, 1> pqqt;
        proxy_type<2, 3, 3, 2> pqqp;
        proxy_type<2, 3, 3, 3> pqqq;
        proxy_type<3, 0, 0, 0> qsss;
        proxy_type<3, 0, 0, 1> qsst;
        proxy_type<3, 0, 0, 2> qssp;
        proxy_type<3, 0, 0, 3> qssq;
        proxy_type<3, 0, 1, 0> qsts;
        proxy_type<3, 0, 1, 1> qstt;
        proxy_type<3, 0, 1, 2> qstp;
        proxy_type<3, 0, 1, 3> qstq;
        proxy_type<3, 0, 2, 0> qsps;
        proxy_type<3, 0, 2, 1> qspt;
        proxy_type<3, 0, 2, 2> qspp;
        proxy_type<3, 0, 2, 3> qspq;
        proxy_type<3, 0, 3, 0> qsqs;
        proxy_type<3, 0, 3, 1> qsqt;
        proxy_type<3, 0, 3, 2> qsqp;
        proxy_type<3, 0, 3, 3> qsqq;
        proxy_type<3, 1, 0, 0> qtss;
        proxy_type<3, 1, 0, 1> qtst;
        proxy_type<3, 1, 0, 2> qtsp;
        proxy_type<3, 1, 0, 3> qtsq;
        proxy_type<3, 1, 1, 0> qtts;
        proxy_type<3, 1, 1, 1> qttt;
        proxy_type<3, 1, 1, 2> qttp;
        proxy_type<3, 1, 1, 3> qttq;
        proxy_type<3, 1, 2, 0> qtps;
        proxy_type<3, 1, 2, 1> qtpt;
        proxy_type<3, 1, 2, 2> qtpp;
        proxy_type<3, 1, 2, 3> qtpq;
        proxy_type<3, 1, 3, 0> qtqs;
        proxy_type<3, 1, 3, 1> qtqt;
        proxy_type<3, 1, 3, 2> qtqp;
        proxy_type<3, 1, 3, 3> qtqq;
        proxy_type<3, 2, 0, 0> qpss;
        proxy_type<3, 2, 0, 1> qpst;
        proxy_type<3, 2, 0, 2> qpsp;
        proxy_type<3, 2, 0, 3> qpsq;
        proxy_type<3, 2, 1, 0> qpts;
        proxy_type<3, 2, 1, 1> qptt;
        proxy_type<3, 2, 1, 2> qptp;
        proxy_type<3, 2, 1, 3> qptq;
        proxy_type<3, 2, 2, 0> qpps;
        proxy_type<3, 2, 2, 1> qppt;
        proxy_type<3, 2, 2, 2> qppp;
        proxy_type<3, 2, 2, 3> qppq;
        proxy_type<3, 2, 3, 0> qpqs;
        proxy_type<3, 2, 3, 1> qpqt;
        proxy_type<3, 2, 3, 2> qpqp;
        proxy_type<3, 2, 3, 3> qpqq;
        proxy_type<3, 3, 0, 0> qqss;
        proxy_type<3, 3, 0, 1> qqst;
        proxy_type<3, 3, 0, 2> qqsp;
        proxy_type<3, 3, 0, 3> qqsq;
        proxy_type<3, 3, 1, 0> qqts;
        proxy_type<3, 3, 1, 1> qqtt;
        proxy_type<3, 3, 1, 2> qqtp;
        proxy_type<3, 3, 1, 3> qqtq;
        proxy_type<3, 3, 2, 0> qqps;
        proxy_type<3, 3, 2, 1> qqpt;
        proxy_type<3, 3, 2, 2> qqpp;
        proxy_type<3, 3, 2, 3> qqpq;
        proxy_type<3, 3, 3, 0> qqqs;
        proxy_type<3, 3, 3, 1> qqqt;
        proxy_type<3, 3, 3, 2> qqqp;
        proxy_type<3, 3, 3, 3> qqqq;
    };

    swizzle_impl()
        noexcept(std::is_nothrow_default_constructible<value_type>::value)
        : elems{}
    {
    }

    swizzle_impl(swizzle_impl const& other)
        noexcept(std::is_nothrow_copy_constructible<value_type>::value)
        : elems{other.elems[0], other.elems[1], other.elems[2], other.elems[3]}
    {
    }

    swizzle_impl(swizzle_impl&& other)
        noexcept(std::is_nothrow_move_constructible<value_type>::value)
        : elems{
            std::move(other.elems[0]), std::move(other.elems[1]),
            std::move(other.elems[2]), std::move(other.elems[3])}
    {
    }

    template <typename X, typename Y, typename Z, typename W>
    swizzle_impl(X&& x, Y&& y, Z&& z, W&& w)
        noexcept(ofxSwizzle::detail::conjunction_v<
            std::is_nothrow_move_constructible<value_type>,
            std::is_nothrow_constructible<value_type, X&&>,
            std::is_nothrow_constructible<value_type, Y&&>,
            std::is_nothrow_constructible<value_type, Z&&>,
            std::is_nothrow_constructible<value_type, W&&>>)
        : elems{
            static_cast<value_type>(std::forward<X>(x)),
            static_cast<value_type>(std::forward<Y>(y)),
            static_cast<value_type>(std::forward<Z>(z)),
            static_cast<value_type>(std::forward<W>(w))}
    {
    }

    ~swizzle_impl()
        noexcept(std::is_nothrow_destructible<value_type>::value)
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i].~T();
        }
    }

    auto operator=(swizzle_impl const& other) &
        noexcept(std::is_nothrow_copy_assignable<value_type>::value)
        -> swizzle_impl&
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i] = other.elems[i];
        }
        return *this;
    }

    auto operator=(swizzle_impl&& other) &
        noexcept(std::is_nothrow_move_assignable<value_type>::value)
        -> swizzle_impl&
    {
        for (size_type i = 0; i < vector_size; ++i)
        {
            elems[i] = std::move(other.elems[i]);
        }
        return *this;
    }
};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_SWIZZLE_IMPL_HPP
