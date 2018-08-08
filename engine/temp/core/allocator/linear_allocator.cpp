#include "temp/core/allocator/linear_allocator.h"
#include "temp/core/assertion.h"

namespace temp {

LinearAllocator::LinearAllocator(Size size, void* start)
    : AllocatorBase<LinearAllocator>(size, start), current_pos_(start) {
  TEMP_ASSERT(size > 0, "size must be greater than 0!");
}

LinearAllocator::~LinearAllocator() { current_pos_ = nullptr; }

void* LinearAllocator::Allocate(Size size, UInt8 alignment) {
  TEMP_ASSERT(size != 0, "size must be greater than 0!");
  UInt8 adjustment = AlignForwardAdjustment(current_pos_, alignment);

  if (used_memory_ + adjustment + size > size_) return nullptr;

  UIntPtr aligned_address = (UIntPtr)current_pos_ + adjustment;
  current_pos_ = (void*)(aligned_address + size);
  used_memory_ += size + adjustment;
  num_allocations_++;

  return (void*)aligned_address;
}

void LinearAllocator::Deallocate(void* p) {
  TEMP_ASSERT(false, "Use clear() instead");
}

void LinearAllocator::Clear() {
  num_allocations_ = 0;
  used_memory_ = 0;
  current_pos_ = start_;
}

}  // namespace temp