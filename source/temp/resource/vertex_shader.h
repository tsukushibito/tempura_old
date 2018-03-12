#pragma once
#include "temp/graphics/device.h"
#include "temp/resource/resource_object.h"

namespace temp {
namespace resource {
class VertexShader : public ResourceObject {
  friend class ResourceManager;

 public:
  using UPtr = std::unique_ptr<VertexShader>;
  using SPtr = std::shared_ptr<VertexShader>;
  using WPtr = std::weak_ptr<VertexShader>;

 private:
  static SPtr makeShared(const filesystem::path& path, ResourceManager* manager,
                         std::function<void(const ResourceId&)> on_destroy);

  VertexShader(const filesystem::path& path, ResourceManager* manager,
               std::function<void(const ResourceId&)> on_destroy);

 public:
  ~VertexShader();

  graphics::VertexShader::SPtr graphicsVertexShader() const {
    return vertex_shader_;
  }

 private:
  ByteData serialize() override;
  void deserialize(const ByteData& byte_data) override;

 private:
  graphics::VertexShader::SPtr vertex_shader_;
};
}  // namespace resource
}  // namespace temp
