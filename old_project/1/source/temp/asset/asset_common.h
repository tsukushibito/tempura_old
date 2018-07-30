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

class Image {
 public:
  virtual ~Image() {}

  virtual const ImageData& imageData() const = 0;
};

}  // namespace asset
}  // namespace temp
