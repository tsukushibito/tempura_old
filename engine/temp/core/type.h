#pragma once
#include <cstddef>
#include <cstdint>

namespace temp {

using Int8 = std::int8_t;
using Int16 = std::int16_t;
using Int32 = std::int32_t;
using Int64 = std::int64_t;

using UInt8 = std::uint8_t;
using UInt16 = std::uint16_t;
using UInt32 = std::uint32_t;
using UInt64 = std::uint64_t;

using Float32 = float;
using Float64 = double;

using Bool = bool;
using Char = char;
using Size = size_t;

using IntPtr = intptr_t;
using UIntPtr = uintptr_t;

struct Color {
  Float32 red;
  Float32 green;
  Float32 blue;
  Float32 alpha;
};

class Uncopyable {
 protected:
  Uncopyable() = default;
  ~Uncopyable() = default;

 private:
  Uncopyable(const Uncopyable &) = delete;
  Uncopyable &operator=(const Uncopyable &) = delete;
};

template <typename T>
class Singleton : Uncopyable {
 protected:
  Singleton() = default;
  virtual ~Singleton() = default;

 public:
  static T &instance() {
    static T instance;
    return instance;
  }
};

template <typename T>
class Optional {
 public:
  Optional() : is_engaged_(false), value_() {}

  explicit Optional(const T &value) : is_engaged_(true), value_(value) {}

  Optional &operator=(const T &value) {
    value_ = value;
    is_engaged_ = true;
    return *this;
  }

  operator bool() const { return is_engaged_; }

  T const &operator*() const { return value_; }
  T &operator*() { return value_; }

 private:
  bool is_engaged_;
  T value_;
};

template <typename T>
class SmartPointerType : private Uncopyable {
 public:
  using UPtr = std::unique_ptr<T>;
  using SPtr = std::shared_ptr<T>;
  using WPtr = std::weak_ptr<T>;

  template <typename Allocator, typename... Args>
  static SPtr AllocateShared(const Allocator &allocator, Args... args) {
    struct Creator : public T {
      Creator(Args... args) : T(args...) {}
    };

    return std::allocate_shared<Creator>(allocator, args...);
  }

  template <typename... Args>
  static UPtr MakeUnique(Args &&... args) {
    struct Creator : public T {
      Creator(Args &&... args) : T(args...) {}
    };
    return std::unique_ptr<T>(new Creator(args...));
  }

  template <typename Allocator, typename... Args>
  static UPtr AllocateUnique(const Allocator &allocator, Args... args) {
    struct Creator : public T {
      Creator(Args... args) : T(args...) {}

      static void *operator new(std::size_t size) {
        typename Allocator::template rebind<UInt8>::other allocator;
        return allocator.allocate(size);
      }
      static void operator delete(void *p, std::size_t size) {
        typename Allocator::template rebind<UInt8>::other allocator;
        allocator.deallocate(reinterpret_cast<UInt8 *>(p), size);
      }
    };
    return std::unique_ptr<T>(new Creator(args...));
  }

 protected:
  SmartPointerType() = default;
};
}  // namespace temp
