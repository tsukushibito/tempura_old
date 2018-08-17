#include "temp/core/allocator/pool_allocator.h"

namespace temp {
PoolAllocator::PoolAllocator(Size object_size, UInt8 object_alignment,
                             Size size, void* mem)
    : AllocatorBase<PoolAllocator>(size, mem),
      object_size_(object_size),
      object_alignment_(object_alignment) {
  TEMP_ASSERT(object_size_ >= sizeof(void*),
              "object_size must be greater than size of void*.");

  // Calculate adjustment needed to keep object correctly aligned
  UInt8 adjustment = AlignForwardAdjustment(mem, object_alignment_);
  free_list_ = (void**)AddPointer(mem, adjustment);
  Size num_objects = (size - adjustment) / object_size_;
  void** p = free_list_;

  // Initialize free blocks list
  for (size_t i = 0; i < num_objects - 1; i++) {
    *p = AddPointer(p, object_size_);
    p = (void**)*p;
  }

  *p = nullptr;
}

PoolAllocator::~PoolAllocator() { free_list_ = nullptr; }

void* PoolAllocator::Allocate(Size size, UInt8 alignment) {
  TEMP_ASSERT(size == object_size_ && alignment == object_alignment_, "");
  if (free_list_ == nullptr) return nullptr;
  void* p = free_list_;
  free_list_ = (void**)(*free_list_);
  used_memory_ += size;
  ++num_allocations_;
  return p;
}

void PoolAllocator::Deallocate(void* p) {
  *((void**)p) = free_list_;
  free_list_ = (void**)p;
  used_memory_ -= object_size_;
  --num_allocations_;
}
}  // namespace temp