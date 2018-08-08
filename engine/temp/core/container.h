#pragma once
#include <array>
#include <deque>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "temp/core/container_allocator.h"
#include "temp/core/type.h"

namespace temp {

using String =
    std::basic_string<char, std::char_traits<char>, ContainerAllocator<char>>;
using StringStream =
    std::basic_stringstream<String::value_type, String::traits_type,
                            String::allocator_type>;

template <typename T, Size N>
using Array = std::array<T, N>;

template <typename T>
using Vector = std::vector<T, ContainerAllocator<T>>;

template <typename T>
using Deque = std::deque<T, ContainerAllocator<T>>;

template <typename T>
using Queue = std::queue<T, Deque<T>>;

template <typename Key, typename Type, typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>>
using HashTable =
    std::unordered_map<Key, Type, Hash, Pred,
                       ContainerAllocator<std::pair<const Key, Type>>>;
}  // namespace temp