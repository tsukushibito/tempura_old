#pragma once
#include <memory>
#include "temp/common/common.h"
#include "temp/graphics/device.h"
#include "temp/resource/resource_object.h"

namespace temp {
namespace resource {
class Texture : public ResourceObject {
  friend class ResourceManager;

 public:
  using UPtr = std::unique_ptr<Texture>;
  using SPtr = std::shared_ptr<Texture>;
  using WPtr = std::weak_ptr<Texture>;

 private:
  static SPtr makeShared(const filesystem::path& path, ResourceManager* manager,
                         std::function<void(const ResourceId&)> on_destroy);

  Texture(const filesystem::path& path, ResourceManager* manager,
          std::function<void(const ResourceId&)> on_destroy);

 public:
  ~Texture();

  const graphics::Texture::SPtr graphicsTexture() const { return gx_texture_; }

  void replaceGraphicsTexture(const graphics::Texture::SPtr& texture) {
    gx_texture_ = texture;
  }

 private:
  ByteData serialize() override;
  void deserialize(const ByteData& byte_data) override;

 private:
  graphics::Texture::SPtr gx_texture_;
};
}  // namespace resource
}  // namespace temp
