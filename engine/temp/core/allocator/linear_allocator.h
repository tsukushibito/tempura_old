#pragma once

#include "temp/core/allocator/allocator_base.h"

namespace temp {
class LinearAllocator : public AllocatorBase<LinearAllocator> {
 public:
  LinearAllocator(Size size, void* start);
  ~LinearAllocator();

  void* Allocate(Size size, UInt8 alignment);
  void Deallocate(void* p);
  void Clear();

 private:
  LinearAllocator(const LinearAllocator&);

  LinearAllocator& operator=(const LinearAllocator&);

  void* current_pos_;
};
};  // namespace temp