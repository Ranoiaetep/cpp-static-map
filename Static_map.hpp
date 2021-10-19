//
// Created by Peter Cong on 9/6/21.
//

#pragma once

#include <cstdint>
#include <array>
#include <optional>
#include <ranges>

namespace sm
{
/// Compile time key-_str map1 that uses array<pair<Key,Value>,N> as the underlying structure.
    template<typename Key, typename Value, std::size_t N>
    struct Static_map
    {
        using Data = std::array<std::pair<Key, Value>, N>;

        /// Explicit create Static_map from a structured array `std::array\<std::pair\<Key,Value>,N>&&`
        /// \param data The structured array to create from.
        explicit constexpr Static_map(Data &&data);

        /// Explicit create Static_map from a structured array `const std::array\<std::pair\<Key,Value>,N>&`
        /// \param data The structured array to create from.
        explicit constexpr Static_map(const Data &data);

        ///
        /// \return Converts underlying data to `const std::array\<std::pair\<Key,Value>,N>&`.
        explicit constexpr operator const Data &() const noexcept
        { return _data; }

        ///
        /// \return The underlying data array.
        constexpr auto data() const noexcept
        { return _data; };

        ///
        /// \return The length of the map1.
        constexpr auto size() const noexcept
        { return N; }

        /// Return paired _str in the format of `std::optional<const Value>`. Returns `std::nullopt` if key was not found.
        /// \param key
        /// \return Optional _str paired from given key.
        constexpr auto at(Key &&key) const noexcept -> std::optional<const Value>;

        /// Return paired _str from given key. Throw if key was not found.
        /// \param key
        /// \return Paired _str from given key.
        /// \Throw `std::out_of_range`
        constexpr auto operator[](Key &&key) const;

        /// Return paired _str from given key. If key was not found a defaulted _str will be returned.
        /// \param key
        /// \return Paired _str from given key, or a defaulted _str if key was not found.
        constexpr auto at_or_default(Key &&key) const noexcept;

        /// Return paired _str from given key. If key was not found a defaulted _str will be returned.
        /// \param key
        /// \param default_value Default _str to return if key was not found.
        /// \return Paired _str from given key, or a defaulted _str if key was not found.
        constexpr auto at_or_default(Key &&key, Value default_value) const noexcept;

        ///
        /// \return Iterator to the first pair.
        constexpr auto begin() const noexcept
        { return _data.cbegin(); }

        ///
        /// \return Iterator to the element after the last pair.
        constexpr auto end() const noexcept
        { return _data.cend(); }

    private:
        constexpr auto has_dup_key() const noexcept;

        const Data _data;
    };

    template<typename Key, typename Value, std::size_t N>
    Static_map(std::array<std::pair<Key, Value>, N> &&) -> Static_map<Key, Value, N>;

/// Create a Static_map using the syntax: <br>`make_static_map(key1, value1, key2, value2, ...)`
/// \param key First key for Static_map
/// \param value First _str for Static_map
/// \param items... Remaining key and _str for Static_map
    template<typename Key, typename Value, typename ... Items>
    constexpr auto make_static_map(Key &&key, Value &&value, Items &&... items);

/// Create a Static_map using the syntax: <br>`make_static_map({key1, value1}, {key2, value2}, ...)`
/// \Notice This only works if `Key` and `Value` are the same type.
/// \param key_value... Key-Value pairs written in brackets.
    template<typename ... Key_Value>
    constexpr auto make_static_map(std::initializer_list<Key_Value> ... key_value);
}

#include "./Static_map.tpp"