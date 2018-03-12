#include "temp/resource/texture.h"
#include "temp/core/logger.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

namespace {
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
  return ByteData();
}

void Texture::deserialize(const ByteData& byte_data) {
  using namespace temp::graphics;
}

}  // namespace resource
}  // namespace temp
