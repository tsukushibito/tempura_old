#include "temp/resource/texture.h"
#include "temp/core/logger.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

namespace {
const Char kTextureTag[] = "Texture";
const Char kTextureSignature[] = "TTEX";
}  // namespace

Texture::SPtr Texture::makeShared(
    const filesystem::path& path, ResourceManager* manager,
    std::function<void(const ResourceId&)> on_destroy) {
  struct Creator : Texture {
    Creator(const filesystem::path& path, ResourceManager* manager,
            std::function<void(const ResourceId&)> on_destroy)
        : Texture(path, manager, on_destroy) {}
  };

  return std::make_shared<Creator>(path, manager, on_destroy);
}

Texture::Texture(const filesystem::path& path, ResourceManager* manager,
                 std::function<void(const ResourceId&)> on_destroy)
    : ResourceObject(path, manager, on_destroy) {}

Texture::~Texture() {}

ByteData Texture::serialize() {
  using namespace temp::graphics;
  if (gx_texture_ == nullptr) {
    TEMP_LOG_WARN(
        kTextureTag,
        fmt::format("graphics texture is null. path: {0}", path().string()));
    return ByteData();
  }

  auto&& desc = gx_texture_->desc();
  Size size = (sizeof(kTextureSignature) - 1) + sizeof(TextureDesc);
  auto data_size =
      desc.width * desc.height * textureFormatBitPerPixel(desc.format);
  size += data_size;
  auto byte_data = ByteData(size);

  // Texture signature
  Size index = 0;
  for (auto i = 0; i < sizeof(kTextureSignature) - 1; ++i) {
    byte_data[index + i] = kTextureSignature[i];
  }
  index += sizeof(kTextureSignature) - 1;

  // desc
  *reinterpret_cast<TextureDesc*>(&byte_data[index]) = desc;
  index += sizeof(TextureDesc);

  // data
  auto data = gx_texture_->data();
  memcpy(&byte_data[index], &gx_texture_->data()[0], data_size);
  index += data_size;
  return byte_data;
}

void Texture::deserialize(const ByteData& byte_data) {
  using namespace temp::graphics;
}

}  // namespace resource
}  // namespace temp
