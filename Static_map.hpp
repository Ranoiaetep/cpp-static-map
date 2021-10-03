//
// Created by Peter Cong on 9/6/21.
//

#pragma once

#include <cstdint>
#include <array>
#include <optional>

namespace sm
{
/// Compile time key-value map that uses array<pair<Key,Value>,N> as the underlying structure.
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
        /// \return The length of the map.
        constexpr auto size() const noexcept
        { return N; }

        /// Return paired value from given key. Throw if key was not found.
        /// \param key
        /// \return Paired value from given key.
        /// \Throw `std::out_of_range`
        constexpr auto at(Key &&key) const;

        /// Return paired value in the format of `std::optional<const Value>`. Returns `std::nullopt` if key was not found.
        /// \param key
        /// \return Optional value paired from given key.
        constexpr auto operator[](Key &&key) const noexcept -> std::optional<const Value>;

        /// Return paired value from given key. If key was not found a defaulted value will be returned.
        /// \param key
        /// \param default_value Default value to return if key was not found. Will return `Value{}` if not assigned.
        /// \return Paired value from given key, or a defaulted value if key was not found.
        constexpr auto at_or_default(Key &&key, Value default_value = Value{}) const noexcept;

    private:
        constexpr auto has_dup_key() const noexcept;

        const Data _data;
    };

    template<typename Key, typename Value, std::size_t N>
    Static_map(std::array<std::pair<Key, Value>, N> &&) -> Static_map<Key, Value, N>;

/// Create a Static_map using the syntax: <br>`make_static_map(key1, value1, key2, value2, ...)`
/// \param key First key for Static_map
/// \param value First value for Static_map
/// \param items... Remaining key and value for Static_map
    template<typename Key, typename Value, typename ... Items>
    constexpr auto make_static_map(Key &&key, Value &&value, Items &&... items);

/// Create a Static_map using the syntax: <br>`make_static_map({key1, value1}, {key2, value2}, ...)`
/// \Notice This only works if `Key` and `Value` are the same type.
/// \param key_value... Key-Value pairs written in brackets.
    template<typename ... Key_Value>
    constexpr auto make_static_map(std::initializer_list<Key_Value> ... key_value);
}

#include "./Static_map.tpp"