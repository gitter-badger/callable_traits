/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef MEMBER_POINTER_UTILITIES_HPP
#define MEMBER_POINTER_UTILITIES_HPP

#include <callable_traits/tags.hpp>

namespace callable_traits {

    namespace ctdetail {

        template<typename T, typename Class>
        using add_member_pointer = T Class::*;

        namespace mpdetail {

            template<typename T>
            struct remove_member_pointer_t {
                using type = T;
            };

            template<typename T, typename U>
            struct remove_member_pointer_t<T U::*>{
                using type = T;
            };
        }

        template<typename T>
        using remove_member_pointer =
            typename mpdetail::remove_member_pointer_t<T>::type;
    }
}


#endif