#include "temp/asset/import.h"
#include "temp/resource/resource_manager.h"
#ifdef TEMP_PLATFORM_MAC
#include "temp/asset/mac/mac_image.h"
namespace temp {
namespace {
std::unique_ptr<asset::Image> createImage(const filesystem::path& path) {
  return std::unique_ptr<asset::Image>(new temp::asset::mac::MacImage(path));
}
}  // namespace
}  // namespace temp
#elif
#endif

namespace temp {
namespace asset {

resource::Texture::SPtr importTexture(const filesystem::path& path) {
  using namespace resource;
  auto image = createImage(path);
  return nullptr;
}
}  // namespace asset
}  // namespace temp
