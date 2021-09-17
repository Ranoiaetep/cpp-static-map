//
// Created by Peter Cong on 10/2/21.
//
#ifndef SM_NO_THROW
#define SM_NO_THROW
#endif

#include "Static_map.hpp"

static_assert(make_static_map(1,2).size() == 1U);
static_assert(make_static_map(1,2,3,4,5,6).size() == 3U);
static_assert(make_static_map(1,2,3,4,5,6).at(1) == 2);
static_assert(make_static_map(1,2,3,4,5,6).at(3) == 4);
static_assert(make_static_map(1,2,3,4,5,6)[1] == 2);
static_assert(make_static_map(1,2,3,4,5,6)[2] == std::nullopt);
static_assert(make_static_map(1,2,3,4,5,6).at_or_default(1, 0) == 2);
static_assert(make_static_map(1,2,3,4,5,6).at_or_default(2, 0) == 0);
static_assert(make_static_map({1,2},{3,4}).size() == 2U);