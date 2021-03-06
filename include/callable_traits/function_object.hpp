/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FUNCTION_OBJECT_HPP
#define CALLABLE_TRAITS_FUNCTION_OBJECT_HPP

#include <callable_traits/general.hpp>
#include <callable_traits/pmf.hpp>
#include <callable_traits/has_normal_call_operator.hpp>
#include <callable_traits/tags.hpp>

#include <tuple>

namespace callable_traits {

    namespace ctdetail {

        template<typename General>
        struct ambiguous_function_object {
            using arg_types = std::tuple<ambiguous_type>;
            using return_type = ambiguous_type;
            using has_varargs = std::false_type;
        };

        template<typename General>
        struct function_object
            : public std::conditional<
                has_normal_call_operator<typename General::type>::value,
                pmf<decltype(&default_normal_callable<typename General::type>::operator())>,
                ambiguous_function_object<General>
            >::type {

            using type = typename General::original_type;
            using general_type = typename General::type;
            
            static constexpr const bool value = std::is_class<type>::value;
            using is_ambiguous = std::integral_constant<bool, !has_normal_call_operator<type>::value>;
            using traits = function_object;
            using class_type = invalid_type;
            using invoke_type = invalid_type;

            using is_function_object = std::integral_constant<bool,
                std::is_class<general_type>::value>;

            using is_member_pointer = std::false_type;
            using is_member_function_pointer = std::false_type;
            using is_function_reference = std::false_type;
            using is_function_pointer = std::false_type;
            using is_function = std::false_type;
            using is_function_general = std::false_type;
            using remove_member_pointer = type;
            using remove_varargs = invalid_type;
            using add_varargs = invalid_type;

            template<typename>
            using add_member_pointer = invalid_type;

            template<typename>
            using apply_return = invalid_type;

            using remove_reference = invalid_type;
            using add_lvalue_reference = invalid_type;
            using add_rvalue_reference = invalid_type;
            using add_const = invalid_type;
            using add_volatile = invalid_type;
            using add_cv = invalid_type;
            using remove_const = invalid_type;
            using remove_volatile = invalid_type;
            using remove_cv = invalid_type;
        };

        template<typename T, typename U>
        struct function_object <general<T U::*> > {
            static constexpr const bool value = false;
            using traits = function_object;
        };
    }
}

#endif