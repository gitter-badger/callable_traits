/*

Copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <type_traits>
#include <cstdint>
#include <memory>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo1 {
    int bar(char, float&, int = 0) { return{}; }
};

struct foo2 {
     int bar(char, float&, int = 0, ...) { return{}; }
};

struct foo3 {
    int operator()(char, float&, int = 0) { return{}; }
};

struct foo4 {
    int operator()(char, float&, int = 0, ...) { return{}; }
};

int foo5(char, float&, int = 0) { return{}; }

int foo6(char, float&, int = 0, ...) { return{}; }

namespace ct = callable_traits;
using std::is_same;

int main() {

    {
        using pmf = decltype(&foo1::bar);
        CT_ASSERT(!decltype(ct::has_varargs(&foo1::bar)){});
        CT_ASSERT(!decltype(ct::has_varargs<pmf>()){});
    } {
        using pmf = decltype(&foo2::bar);
        CT_ASSERT(decltype(ct::has_varargs(&foo2::bar)){});
        CT_ASSERT(decltype(ct::has_varargs<pmf>()){});
    } {
        CT_ASSERT(!decltype(ct::has_varargs(foo3{})){});
        CT_ASSERT(!decltype(ct::has_varargs<foo3>()){});
    } {
        CT_ASSERT(decltype(ct::has_varargs(foo4{})){});
        CT_ASSERT(decltype(ct::has_varargs<foo4>()){});
    } {
        CT_ASSERT(!decltype(ct::has_varargs(&foo5)){});
        CT_ASSERT(!decltype(ct::has_varargs<decltype(foo5)>()){});
    } {
        CT_ASSERT(decltype(ct::has_varargs(&foo6)){});
        CT_ASSERT(decltype(ct::has_varargs<decltype(foo6)>()){});
    }

    return 0;
}