#pragma once
#include <memory>
#include "temp/common/common.h"
#include "temp/graphics/device.h"
#include "temp/resource/resource_object.h"
#include "temp/resource/texture.h"

namespace temp {
namespace resource {
class Material : public ResourceObject {
  friend class ResourceManager;

 public:
  using UPtr = std::unique_ptr<Material>;
  using SPtr = std::shared_ptr<Material>;
  using WPtr = std::weak_ptr<Material>;

 private:
  static SPtr makeShared(const filesystem::path& path, ResourceManager* manager,
                         std::function<void(const ResourceId&)> on_destroy);

  Material(const filesystem::path& path, ResourceManager* manager,
           std::function<void(const ResourceId&)> on_destroy);

 public:
  ~Material();

  const Color& baseColor() const { return base_color_; }
  Float32 roughness() const { return roughness_; }
  Float32 metalic() const { return metalic_; }
  const Texture::SPtr albedoMap() const { return albedo_map_; }
  const Texture::SPtr roughnessMap() const { return roughness_map_; }
  const Texture::SPtr metalicMap() const { return metalic_map_; }
  const Texture::SPtr normalMap() const { return normal_map_; }

  void replaceBaseColor(const Color& color) { base_color_ = color; }
  void replaceRoughness(Float32 roughness) { roughness_ = roughness; }
  void replaceMetalic(Float32 metalic) { metalic_ = metalic; }
  void replaceAlbedoMap(const Texture::SPtr& tex) { albedo_map_ = tex; }
  void replaceRoughnessMap(const Texture::SPtr& tex) { roughness_map_ = tex; }
  void replaceMetalicMap(const Texture::SPtr& tex) { metalic_map_ = tex; }
  void replaceNormalMap(const Texture::SPtr& tex) { normal_map_ = tex; }

 private:
  ByteData serialize() override;
  void deserialize(const ByteData& byte_data) override;

 private:
  Color base_color_;
  Float32 roughness_;
  Float32 metalic_;

  Texture::SPtr albedo_map_;
  Texture::SPtr roughness_map_;
  Texture::SPtr metalic_map_;
  Texture::SPtr normal_map_;
};
}  // namespace resource
}  // namespace temp
