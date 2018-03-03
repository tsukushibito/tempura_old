#pragma once
#include "temp/graphics/device.h"
#include "temp/resource/resource_object.h"

namespace temp {
namespace resource {
class PixelShader : public ResourceObject {
  friend class ResourceManager;

 public:
  using UPtr = std::unique_ptr<PixelShader>;
  using SPtr = std::shared_ptr<PixelShader>;
  using WPtr = std::weak_ptr<PixelShader>;

 private:
  static SPtr makeShared(const filesystem::path& path, ResourceManager* manager,
                         std::function<void(void)> on_destroy);

  PixelShader(const filesystem::path& path, ResourceManager* manager,
              std::function<void(void)> on_destroy);

 public:
  ~PixelShader();

 private:
  void prepare(const ByteData& byte_data) override;

 private:
  graphics::PixelShader::SPtr pixel_shader_;
};
}  // namespace resource
}  // namespace temp