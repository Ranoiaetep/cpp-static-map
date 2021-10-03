#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include "./util.hpp"
#include "./helper.hpp"

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