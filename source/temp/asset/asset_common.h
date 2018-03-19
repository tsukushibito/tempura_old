#pragma once
#include "temp/common/common.h"
namespace temp {
namespace asset {

struct ImageData {
  Int32 width;
  Int32 height;
  Int32 bytes_per_pixel;
  void* bitmap_data;
};

}  // namespace asset
}  // namespace temp
