//
// Created by Peter Cong on 9/30/21.
//

#pragma once

#include <functional>
#include <array>
#include <string_view>
#include <type_traits>

namespace sm
{
    namespace helper
    {
        template<typename tuple_t>
        constexpr auto get_array_from_tuple(tuple_t &&tuple)
        {
            constexpr auto get_array =
                    [](auto &&... x)
                    {
                        return std::array{std::forward<decltype(x)>(x) ...};
                    };
            auto temp = std::apply(get_array, std::forward<tuple_t>(tuple));
            return temp;
        }

        template<typename T>
        constexpr auto try_char_array_to_string_view(T t)
        {
            if constexpr(std::is_same_v<T, const char*>)
            {
                return std::string_view(t);
            }
            else
            {
                return t;
            }
        }
    }
}