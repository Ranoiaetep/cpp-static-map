//
// Created by Peter Cong on 9/6/21.
//

#pragma once

#include <cstdint>
#include <array>
#include <optional>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <functional>
#include <ranges>
#include <string_view>
#include <type_traits>

// Declarations
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

// Utilities
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

// Helpers
namespace sm
{
    namespace helper
    {
        template<typename tuple_t>
        constexpr auto get_array_from_tuple(tuple_t &&tuple)
        {
            constexpr auto get_array =
                    [](auto &&... x)
                    {
                        return std::array{std::forward<decltype(x)>(x) ...};
                    };
            auto temp = std::apply(get_array, std::forward<tuple_t>(tuple));
            return temp;
        }

        template<typename T>
        constexpr auto try_char_array_to_string_view(T t)
        {
            if constexpr(std::is_same_v<T, const char*>)
            {
                return std::string_view(t);
            }
            else
            {
                return t;
            }
        }
    }
}

// Definitions
namespace sm
{
    template<typename Key, typename Value, std::size_t N>
    constexpr Static_map<Key, Value, N>::Static_map(Static_map::Data &&data)
            : _data(std::forward<Data &&>(data))
    {
#ifdef SM_NO_DUPLICATE
        if (has_dup_key())
        {
            throw std::invalid_argument("Duplicate keys detected, please check your input.");
        }
#endif
    }

    template<typename Key, typename Value, std::size_t N>
    constexpr Static_map<Key, Value, N>::Static_map(const Static_map::Data &data)
            : _data(data)
    {
#ifdef SM_NO_DUPLICATE
        if (has_dup_key())
        {
            throw std::invalid_argument("Duplicate keys detected, please check your input.");
        }
#endif
    }

    template<typename Key, typename Value, std::size_t N>
    constexpr auto Static_map<Key, Value, N>::at(Key &&key) const
    {
        auto it = std::ranges::find(_data, key, &Data::value_type::first);
        if (it == _data.end())
        {
            throw std::out_of_range("Key does not exist");
        }
        return it->second;
    }

    template<typename Key, typename Value, std::size_t N>
    constexpr auto Static_map<Key, Value, N>::operator[](Key &&key) const noexcept -> std::optional<const Value>
    {
        auto it = std::ranges::find(_data, key, &Data::value_type::first);
        return it == _data.end() ? std::nullopt : std::optional<const Value>{it->second};
    }

    template<typename Key, typename Value, std::size_t N>
    constexpr auto Static_map<Key, Value, N>::at_or_default(Key &&key, Value default_value) const noexcept
    {
        return operator[](std::forward<Key &&>(key)).value_or(default_value);
    }

    template<typename Key, typename Value, std::size_t N>
    constexpr auto Static_map<Key, Value, N>::has_dup_key() const noexcept
    {
        return has_duplicate(_data, &Data::value_type::first);
    }

    template<typename Key, typename Value, typename ... Items>
    constexpr auto make_static_map(Key &&key, Value &&value, Items &&... items)
    {
        auto key_mod = helper::try_char_array_to_string_view(key);
        auto value_mod = helper::try_char_array_to_string_view(value);
        if constexpr(sizeof...(Items) > 1U)
        {
            return Static_map<decltype(key_mod), decltype(value_mod), sizeof...(Items) / 2U + 1U>(
                    helper::get_array_from_tuple(std::tuple_cat(
                            std::make_tuple(std::make_pair(key_mod, value_mod)),
                            static_cast<const std::array<std::pair<decltype(key_mod), decltype(value_mod)>, sizeof...(Items) / 2U> &>(
                                    make_static_map((std::forward<Items &&>(items))...)))));
        } else
        {
            return Static_map<decltype(key_mod), decltype(value_mod), 1U>({std::make_pair(key_mod, value_mod)});
        }
    }

    template<typename ... Key_Value>
    constexpr auto make_static_map(std::initializer_list<Key_Value> ... key_value)
    {
        return Static_map(std::array{(std::make_pair(*std::begin(key_value), *std::rbegin(key_value)))...});
    }
}