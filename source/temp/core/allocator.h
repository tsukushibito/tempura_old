#pragma once
#include <iostream>
#include <memory>

namespace temp {
namespace core {

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

}  // namespace core
}  // namespace temp