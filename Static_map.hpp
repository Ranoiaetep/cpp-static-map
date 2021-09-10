//
// Created by Peter Cong on 9/6/21.
//

#pragma once

#include <cstdint>
#include <array>
#include <optional>

template<typename Key, typename Value, std::size_t N>
struct Static_map {
    using Data = std::array<std::pair<Key, Value>, N>;

    explicit constexpr Static_map(Data&& data);
    explicit constexpr operator const Data& () const noexcept { return _data; }
    constexpr auto size() const noexcept { return _data.size(); }

    constexpr auto at(Key&& key) const;
    constexpr auto operator[](Key&& key) const noexcept -> std::optional<const Value>;
    constexpr auto at_or_default(Key&& key, Value default_value) const noexcept;

private:
    constexpr auto has_dup_key() const noexcept;

    const Data _data;
};

//template<typename Key, typename Value, typename ... Items>
//constexpr auto make_static_map(Key&& key, Value&& value, Items&& ... items);

#include "Static_map.tpp"