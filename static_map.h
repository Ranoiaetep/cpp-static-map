//
// Created by Peter Cong on 9/6/21.
//

#ifndef CPP_STATIC_MAP_STATIC_MAP_H
#define CPP_STATIC_MAP_STATIC_MAP_H

#include <functional>
#include <utility>
#include <array>

template<typename Key, typename T, std::size_t N>
struct static_map {
//    static_map(std::pair<Key, T> pairs ...);

//private:
    std::array<std::pair<Key, T>, N> _data;
};

template<typename ... Pair>
static_map(Pair...) ->
static_map<
        typename std::common_type_t<Pair...>::first_type,
        typename std::common_type_t<Pair...>::second_type,
        sizeof...(Pair)>;


#endif //CPP_STATIC_MAP_STATIC_MAP_H
