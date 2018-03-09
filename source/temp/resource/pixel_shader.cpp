#include "temp/resource/pixel_shader.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {
PixelShader::SPtr PixelShader::makeShared(
    const filesystem::path& path, ResourceManager* manager,
    std::function<void(void)> on_destroy) {
  struct Creator : PixelShader {
    Creator(const filesystem::path& path, ResourceManager* manager,
            std::function<void(void)> on_destroy)
        : PixelShader(path, manager, on_destroy) {}
  };

  return std::make_shared<Creator>(path, manager, on_destroy);
}

PixelShader::PixelShader(const filesystem::path& path, ResourceManager* manager,
                         std::function<void(void)> on_destroy)
    : ResourceObject(path, manager, on_destroy) {}

PixelShader::~PixelShader() {}

ByteData PixelShader::serialize() { return ByteData(); }

void PixelShader::deserialize(const ByteData& byte_data) {
  auto&& graphicsDevice = manager()->graphicsDevice();
  graphics::ShaderCode code;
  code.code = ByteData(byte_data.begin(), byte_data.end());
  code.is_binary = false;
  pixel_shader_ = graphicsDevice->createPixelShader(code);
}
}  // namespace resource
}  // namespace temp