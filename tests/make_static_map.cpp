//
// Created by Peter Cong on 10/2/21.
//

#include <string_view>
#include <Static_map.hpp>

using namespace sm;
static_assert(make_static_map(1,2).size() == 1U);
static_assert(make_static_map(1,2,3,4,5,6).size() == 3U);
static_assert(make_static_map(1,2,3,4,5,6).at(1) == 2);
static_assert(make_static_map(1,2,3,4,5,6).at(3) == 4);
static_assert(make_static_map(1,2,3,4,5,6)[1] == 2);
static_assert(make_static_map(1,2,3,4,5,6)[2] == std::nullopt);
static_assert(make_static_map(1,2,3,4,5,6).at_or_default(1, 1) == 2);
static_assert(make_static_map(1,2,3,4,5,6).at_or_default(1) == 2);
static_assert(make_static_map(1,2,3,4,5,6).at_or_default(2, 1) == 1);
static_assert(make_static_map(1,2,3,4,5,6).at_or_default(2) == 0);
static_assert(make_static_map({1,2},{3,4}).size() == 2U);
static_assert(make_static_map({1,2},{3,4}).at(1) == 2);

using std::literals::string_view_literals::operator""sv;

static_assert(make_static_map(1, "One"sv).size() == 1U);
static_assert(make_static_map(1,"One"sv,2,"Two"sv,3,"Three"sv).size() == 3U);
static_assert(make_static_map(1,"One"sv,2,"Two"sv,3,"Three"sv).at(1) == "One"sv);
static_assert(make_static_map(1,2,3,4,5,6)[1] == 2);

static_assert(make_static_map("One"sv, 1).size() == 1U);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3).size() == 3U);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3).at("One"sv) == 1);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3).at("One") == 1);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3)["One"] == 1);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3)["Zero"] == std::nullopt);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3).at_or_default("One", 1) == 1);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3).at_or_default("Zero", 1) == 1);
static_assert(make_static_map("One"sv,1,"Two"sv,2,"Three"sv,3).at_or_default("Zero") == 0);

static_assert(make_static_map("1"sv, "One"sv).size() == 1U);
static_assert(make_static_map("1"sv,"One"sv,"2"sv,"Two"sv,"3"sv,"Three"sv).size() == 3U);
static_assert(make_static_map("1"sv,"One"sv,"2"sv,"Two"sv,"3"sv,"Three"sv).at("1"sv) == "One"sv);

static_assert(make_static_map("1","One","2","Two","3","Three").at("1"sv) == "One"sv);

static_assert(make_static_map({"1"sv,"One"sv},{"2"sv,"Two"sv}).size() == 2U);
static_assert(make_static_map({"1"sv,"One"sv},{"2"sv,"Two"sv}).at("1"sv) == "One"sv);
static_assert(make_static_map({"1"sv,"One"sv},{"2"sv,"Two"sv}).at("1") == "One");
static_assert(make_static_map({"1"sv,"One"sv},{"2"sv,"Two"sv}).at_or_default("1", "One") == "One");
static_assert(make_static_map({"1"sv,"One"sv},{"2"sv,"Two"sv}).at_or_default("0", "One") == "One");
static_assert(make_static_map({"1"sv,"One"sv},{"2"sv,"Two"sv}).at_or_default("0") == "");

int main() {}