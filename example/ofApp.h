#pragma once

#include "ofMain.h"
#include "ofxSwizzle.hpp"

class ofApp : public ofBaseApp
{
public:
    void setup()
    {
        // ofxSwizzle::vec is same size as array
        static_assert(sizeof(ofxSwizzle::vec<double, 2>) == sizeof(double[2]), "");
        static_assert(sizeof(ofxSwizzle::vec<double, 3>) == sizeof(double[3]), "");
        static_assert(sizeof(ofxSwizzle::vec<double, 4>) == sizeof(double[4]), "");


        { // construct
            ofxSwizzle::vec<double, 2> a(1., 2.);

            ofxSwizzle::vec<double, 2> b(1.); // == vec<double, 2>(1., 1.)

            ofxSwizzle::vec<double, 4> c = {0., a, b[1]}; // == vec<double, 2>(0., 1., 2., 1.);

            // nesting
            ofxSwizzle::vec<ofxSwizzle::vec<double, 2>, 2> d = {{0., 1.}, {2., 3.}};

            // factory function
            auto e = ofxSwizzle::make_vector(1., 2., 3.); // == vec<double, 3>(1., 2., 3.)

            // scalar swizzling
            using ofxSwizzle::literals::operator""_xxxx;
            auto f = 0.5_xxxx; // == vec<long double, 4>(0.5, 0.5, 0.5, 0.5);

            // convert from ofVecNf
            ofxSwizzle::vec<double, 2> g = ofVec2f(0., 0.);

            // ocnvert to ofVecNf
            ofVec3f h = ofxSwizzle<float, 3>(1., 2., 3.).zyx;

            // move construct
            ofxSwizzle::vec<double, 2> i = std::move(a);
        }


        { // swizzling
            ofxSwizzle::vec<double, 4> a(1., 2., 3., 4.);

            ofxSwizzle::vec<double, 2> b = a.xy; // == vec<double, 2>(1., 2.)

            a.wzyx = a.xzyy;
            // a == vec<double, 4>(2., 2., 3., 1.)

            a.xy = ofVec2f(0., 0.);
            // a == vec<double, 4>(0., 0., 3., 1.)

            a = a.zzzz;
            // a == vec<double, 4>(3., 3., 3., 3.)

            // not allowed because `x` is duplicated in lhs
            // a.xx = a.yz;
        }


        { // comparison
            ofxSwizzle::vec<double, 2> a = {1., 3};
            ofxSwizzle::vec<double, 2> b = {2., 3};
            ofxSwizzle::vec<double, 2> c = {2., 3};

            a == b; // == false
            b == c; // == true
            a != b; // == true

            ofxSwizzle::equal_to(a, b); // == vec<bool, 2>(false, true)
            ofxSwizzle::not_equal_to(b, c); // == vec<bool, 2>(false, false)

            ofxSwizzle::less(a, b); // == vec<bool, 2>(true, false)
            ofxSwizzle::greater_equal(b, c); // == vec<bool, 2>(true, true);
        }


        { // operators
            ofxSwizzle::vec<int, 2> a = {0, 1};
            ofxSwizzle::vec<bool, 2> b = {true, false};

            // assignment
            a += 2;
            a /= ofxSwizzle::vec<double, 2>(1., 2.);

            // arithmetric
            3 + a;
            a / 2.;

            // bitwise
            a << 2;
            a & ofxSwizzle::vec<int, 2>(2, 3);

            // logical
            b || true;
            !b;

            // increment / decrement
            ++a;
            a--;
        }


        { // iterator interface
            ofxSwizzle::vec<double, 4> a = {1., 2., 3., 4.};

            // range-based for
            for (auto&& i : a) {}
            for (auto&& i : a.xxxx) {}

            // copy to STL container
            std::vector<double> v(a.begin(), a.end());
            std::vector<double> w(a.yxzz.begin(), a.yxzz.end());

            // STL algorithm
            std::transform(a.begin(), a.end(), v.begin(), std::negate<>());
            std::transform(a.xy.begin(), a.xy.end(), a.begin(), std::negate<>());
        }


        { // math function
            ofxSwizzle::vec<double, 2> a = {1., 2.};

            auto b = ofxSwizzle::sin(a); // == vec<double, 2>(sin(1.), sin(2.))

            // call via ADL
            auto c = exp(a); // == vec<double, 2>(exp(1.), exp(2.))

            // nesting
            auto d = ofxSwizzle::log(ofxSwizzle::make_vector(b, c));
        }


        { // utility
            ofxSwizzle::vec<double, 2> a = {1., 2.};

            // map a function over all component
            auto b = ofxSwizzle::apply([](auto x) { return x * 2.; }, a);

            // map a binary function
            auto c = ofxSwizzle::apply([](auto x, auto y) { return x + y; }, a, b);

            // apply a function for each component
            ofxSwizzle::for_each(a, [](auto x) { std::cout << x << ','; });

            // apply a binary function
            ofxSwizzle::for_each(a, b, [](auto x, auto y) { std::cout << (x - y) << ','; });
        }


        { // tuple interface
            using v = ofxSwizzle::vec<double, 3>;

            static_assert(std::tuple_size<v>::value == 3, "");
            static_assert(std::is_same<
                std::tuple_element<2, v const>::type, double const>::value, "");

            ofxSwizzle::vec<double, 2> a = {0., 1.};
            std::get<0>(a); // == a[0];
            std::get<1>(a); // == a[1];
        }
    }
};
