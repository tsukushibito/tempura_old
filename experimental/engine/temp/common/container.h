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

#include "temp/common/type.h"

namespace temp {

template <typename T>
class AllocatorForStl {
 public:
  using value_type = T;

  AllocatorForStl(){};

  template <class U>
  AllocatorForStl(const AllocatorForStl<U> &) {}

  T *allocate(std::size_t n) {
    return reinterpret_cast<T *>(std::malloc(sizeof(T) * n));
  }

  void deallocate(T *p, std::size_t n) {
    static_cast<void>(n);
    std::free(p);
  }
};

template <class T, class U>
bool operator==(const AllocatorForStl<T> &, const AllocatorForStl<U> &) {
  return true;
}

template <class T, class U>
bool operator!=(const AllocatorForStl<T> &, const AllocatorForStl<U> &) {
  return false;
}

using String =
    std::basic_string<char, std::char_traits<char>, AllocatorForStl<char>>;
using StringStream =
    std::basic_stringstream<String::value_type, String::traits_type,
                            String::allocator_type>;

template <typename T>
using Vector = std::vector<T, AllocatorForStl<T>>;

template <typename T>
using Deque = std::deque<T, AllocatorForStl<T>>;

template <typename T>
using Queue = std::queue<T, Deque<T>>;

template <typename Key, typename Type, typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>>
using HashMap = std::unordered_map<Key, Type, Hash, Pred,
                                   AllocatorForStl<std::pair<const Key, Type>>>;
}  // namespace temp