//
// Created by Peter Cong on 9/30/21.
//

#pragma once

#include <functional>
#include <array>

namespace helper
{
    template<typename tuple_t>
    constexpr auto get_array_from_tuple(tuple_t &&tuple)
    {
        constexpr auto get_array =
                [](auto &&... x){
                    return std::array{std::forward<decltype(x)>(x) ...};
        };
        auto temp = std::apply(get_array, std::forward<tuple_t>(tuple));
        return temp;
    }
}