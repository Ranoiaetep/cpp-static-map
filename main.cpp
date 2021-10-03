//
// Created by Peter Cong on 9/6/21.
//
#include <iostream>
#include "Static_map.hpp"

using namespace std::string_view_literals;

int main()
{
    constexpr auto number_word_map =
            sm::make_static_map(1, "One", 2, "Two", 3, "Three");
    return 0;
}