//
// Created by Peter Cong on 9/6/21.
//

#include "Static_map.hpp"

int main()
{
    auto map = std::array{std::pair{1,2},std::pair{3,4}, std::pair{5,6}};
    Static_map smap(std::array<std::pair<int,int>, 3>{std::pair{1,2},std::pair{3,4}, std::pair{5,6}});
}