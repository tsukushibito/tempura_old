#pragma once
#include <new>

#include "temp/core/assertion.h"
#include "temp/core/type.h"

namespace temp {
template <class T>
class AllocatorBase : private Uncopyable {
  static const int kDefaultAlignment = 8;

 public:
  AllocatorBase(Size size, void* start)
      : start_(start), size_(size), used_memory_(0), num_allocations_(0) {}

  virtual ~AllocatorBase() {
    TEMP_ASSERT(num_allocations_ == 0 && used_memory_ == 0, "");
    start_ = nullptr;
    size_ = 0;
  }

  void* Allocate(Size size, UInt8 alignment = kDefaultAlignment) {
    return static_cast<T*>(this)->Allocate(size, alignment);
  }
  void Deallocate(void* p) { static_cast<T*>(this)->Deallocate(p); }

  void* start() const { return start_; }
  Size size() const { return size_; }
  Size used_memory() const { return used_memory_; }
  Size num_allocations() const { return num_allocations_; }

 protected:
  void* start_;
  Size size_;
  Size used_memory_;
  Size num_allocations_;
};

template <typename T, typename U>
T* AllocateNew(AllocatorBase<U>& allocator) {
  return new (allocator.Allocate(sizeof(T), alignof(T))) T;
}

template <typename T, typename U>
T* AllocateNew(AllocatorBase<U>& allocator, const T& t) {
  return new (allocator.Allocate(sizeof(T), alignof(T))) T(t);
}

template <typename T, typename U>
void DeallocateDelete(AllocatorBase<U>& allocator, T& object) {
  object.~T();
  allocator.Deallocate(&object);
}

template <typename T, typename U>
T* AllocateArray(AllocatorBase<U>& allocator, Size length) {
  TEMP_ASSERT(length != 0, "lenght must be greater than zero!");
  UInt8 header_size = sizeof(Size) / sizeof(T);

  if (sizeof(Size) % sizeof(T) > 0) header_size += 1;

  // Allocate extra space to store array length in the bytes before the array
  T* p =
      ((T*)allocator.Allocate(sizeof(T) * (length + header_size), alignof(T))) +
      header_size;
  *(((Size*)p) - 1) = length;

  for (Size i = 0; i < length; i++) {
    new (&p) T;
  }

  return p;
}

template <typename T, typename U>
void DeallocateArray(AllocatorBase<U>& allocator, T* array) {
  TEMP_ASSERT(array != nullptr, "array must not be null!");
  Size length = *(((Size*)array) - 1);

  for (Size i = 0; i < length; i++) array.~T();

  // Calculate how much extra memory was allocated to store the length before
  // the array
  UInt8 header_size = sizeof(Size) / sizeof(T);
  if (sizeof(Size) % sizeof(T) > 0) header_size += 1;
  allocator.Deallocate(array - header_size);
}

inline void* AlignForward(void* address, UInt8 alignment) {
  return (void*)((reinterpret_cast<UIntPtr>(address) +
                  static_cast<UIntPtr>(alignment - 1)) &
                 static_cast<UIntPtr>(~(alignment - 1)));
}

inline UInt8 AlignForwardAdjustment(const void* address, UInt8 alignment) {
  UInt8 adjustment = alignment - (reinterpret_cast<const UIntPtr>(address) &
                                  static_cast<UIntPtr>(alignment - 1));

  if (adjustment == alignment) return 0;

  // already aligned
  return adjustment;
}

inline UInt8 AlignForwardAdjustmentWithHeader(const void* address,
                                              UInt8 alignment,
                                              UInt8 headerSize) {
  UInt8 adjustment = AlignForwardAdjustment(address, alignment);
  UInt8 neededSpace = headerSize;

  if (adjustment < neededSpace) {
    neededSpace -= adjustment;

    // Increase adjustment to fit header
    adjustment += alignment * (neededSpace / alignment);

    if (neededSpace % alignment > 0) adjustment += alignment;
  }

  return adjustment;
}

inline void* AddPointer(void* p, Size x) {
  return (void*)(reinterpret_cast<UIntPtr>(p) + x);
}

inline const void* AddPointer(const void* p, Size x) {
  return (const void*)(reinterpret_cast<UIntPtr>(p) + x);
}
}  // namespace temp
