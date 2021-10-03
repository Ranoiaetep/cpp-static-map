//
// Created by Peter Cong on 9/30/21.
//

#pragma once

#include <functional>
#include <ranges>

namespace sm
{
    template<std::ranges::input_range Range, typename Projection = std::identity>
    constexpr bool has_duplicate(Range &&range, Projection projection = {})
    {
        for (auto it = range.cbegin(); const auto &obj_1: range)
        {
            for (const auto &obj_2: std::ranges::subrange(range.cbegin(), it++))
            {
                if (std::invoke(projection, obj_1) == std::invoke(projection, obj_2))
                {
                    return true;
                }
            }
        }
        return false;
    }
}