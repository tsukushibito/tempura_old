#pragma once
#include "temp/asset/asset_common.h"
#include "temp/core/filesystem.h"

namespace temp {
namespace asset {
namespace mac {

class MacImage {
 public:
  explicit MacImage(const filesystem::path& path);
  explicit MacImage(const void* data, Size size);
  ~MacImage();

  const ImageData& imageData() const { return image_data_; }

 private:
  ImageData image_data_;
  void* ns_image_;
};

}  // namespace mac
}  // namespace asset
}  // namespace temp
