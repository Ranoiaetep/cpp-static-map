//
// Created by Peter Cong on 10/3/21.
//
#include <Static_map.hpp>

using namespace sm;
static_assert(Static_map(std::array<std::pair<int,int>,3U>{
    std::pair{1,2},
    std::pair{3,4},
    std::pair{5,6}}).size() == 3U);
static_assert(Static_map(std::array<std::pair<int,int>,3U>{
    std::pair{1,2},
    std::pair{3,4},
    std::pair{5,6}}).data() ==
    std::array<std::pair<int,int>,3U>{
    std::pair{1,2},
    std::pair{3,4},
    std::pair{5,6}});
static_assert(static_cast<const std::array<std::pair<int,int>,3U>>(
        Static_map(std::array<std::pair<int,int>,3U>{
            std::pair{1,2},
            std::pair{3,4},
            std::pair{5,6}}).data()) ==
            std::array<std::pair<int,int>,3U>{
    std::pair{1,2},
    std::pair{3,4},
    std::pair{5,6}});

int main() {}