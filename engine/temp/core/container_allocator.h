#pragma once
#include <iostream>
#include <memory>

namespace temp {

template <typename T>
class ContainerAllocator {
 public:
  using value_type = T;

  ContainerAllocator(){};

  template <class U>
  ContainerAllocator(const ContainerAllocator<U> &) {}

  T *allocate(std::size_t n) {
    return reinterpret_cast<T *>(std::malloc(sizeof(T) * n));
  }

  void deallocate(T *p, std::size_t n) {
    static_cast<void>(n);
    std::free(p);
  }
};

template <class T, class U>
bool operator==(const ContainerAllocator<T> &, const ContainerAllocator<U> &) {
  return true;
}

template <class T, class U>
bool operator!=(const ContainerAllocator<T> &, const ContainerAllocator<U> &) {
  return false;
}

}  // namespace temp
