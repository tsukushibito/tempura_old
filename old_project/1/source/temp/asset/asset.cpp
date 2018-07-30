#include "temp/asset/asset.h"
#ifdef TEMP_PLATFORM_MAC
#include "temp/asset/mac/mac_image.h"
namespace temp {
namespace {
std::unique_ptr<asset::Image> createImage(const filesystem::path& path) {
  return std::move(
      std::unique_ptr<asset::Image>(new temp::asset::mac::MacImage(path)));
}
}  // namespace
}  // namespace temp
#elif
#endif

namespace temp {
namespace asset {

AssetManager::AssetManager(
    const resource::ResourceManager::SPtr& resource_manager,
    const filesystem::path& asset_root)
    : resource_manager_(resource_manager), asset_root_(asset_root) {
  asset_root_ = filesystem::absolute(asset_root_);
  asset_root_ = filesystem::canonical(asset_root_);
  filesystem::current_path(asset_root);
}

void AssetManager::importImage(const filesystem::path& asset_path) {
  using namespace resource;
  auto image = createImage(asset_path);
  auto&& image_data = image->imageData();

  graphics::TextureDesc texture_desc;
  texture_desc.format = graphics::TextureFormat::kRGBA32;
  texture_desc.width = image_data.width;
  texture_desc.height = image_data.height;
  texture_desc.mipLevel = 0;

  auto graphics_device = resource_manager_->graphicsDevice();
  auto graphics_texture =
      graphics_device->createTexture(texture_desc, image_data.bitmap_data);

  auto texture_resource_path = asset_path;
  texture_resource_path.replace_extension(".ttex");
  auto texture_resource =
      resource_manager_->create<Texture>(texture_resource_path);
  texture_resource->replaceGraphicsTexture(graphics_texture);
  texture_resource->save();
}
}  // namespace asset
}  // namespace temp
