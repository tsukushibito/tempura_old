#pragma once
#include <cstddef>
#include <cstdint>

#include <memory>

namespace temp {

using Float32 = float;
using Float64 = double;

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

  template <typename... Args>
  static SPtr MakeShared(Args &&... args) {
    struct Creator : public T {
      Creator(Args &&... args) : T(std::forward<Args>(args)...) {}
    };

    return std::make_shared<Creator>(std::forward<Args>(args)...);
  }

  template <typename Allocator, typename... Args>
  static SPtr AllocateShared(const Allocator &allocator, Args &&... args) {
    struct Creator : public T {
      Creator(Args &&... args) : T(std::forward<Args>(args)...) {}
    };

    return std::allocate_shared<Creator>(allocator,
                                         std::forward<Args>(args)...);
  }

  template <typename... Args>
  static UPtr MakeUnique(Args &&... args) {
    struct Creator : public T {
      Creator(Args &&... args) : T(std::forward<Args>(args)...) {}
    };
    return std::unique_ptr<T>(new Creator(std::forward<Args>(args)...));
  }

  template <typename Allocator, typename... Args>
  static UPtr AllocateUnique(const Allocator &allocator, Args &&... args) {
    struct Creator : public T {
      Creator(Args &&... args) : T(std::forward<Args>(args)...) {}

      static void *operator new(std::size_t size) {
        typename Allocator::template rebind<std::uint8_t>::other allocator;
        return allocator.allocate(size);
      }
      static void operator delete(void *p, std::size_t size) {
        typename Allocator::template rebind<std::uint8_t>::other allocator;
        allocator.deallocate(reinterpret_cast<std::uint8_t *>(p), size);
      }
    };
    return std::unique_ptr<T>(new Creator(std::forward<Args>(args)...));
  }

 protected:
  SmartPointerType() = default;
};
}  // namespace temp
