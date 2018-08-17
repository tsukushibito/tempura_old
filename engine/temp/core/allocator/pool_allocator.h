#include "temp/core/allocator/allocator_base.h"

namespace temp {
class PoolAllocator : public AllocatorBase<PoolAllocator> {
 public:
  PoolAllocator(Size object_size, UInt8 object_alignment, Size size, void* mem);
  ~PoolAllocator();
  void* Allocate(Size size, UInt8 alignment);
  void Deallocate(void* p);

 private:
  Size object_size_;

  UInt8 object_alignment_;
  void** free_list_;
};
}