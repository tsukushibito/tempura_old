#include "temp/resource/vertex_shader.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {
VertexShader::SPtr VertexShader::makeShared(
    const filesystem::path& path, ResourceManager* manager,
    std::function<void(void)> on_destroy) {
  struct Creator : VertexShader {
    Creator(const filesystem::path& path, ResourceManager* manager,
            std::function<void(void)> on_destroy)
        : VertexShader(path, manager, on_destroy) {}
  };

  return std::make_shared<Creator>(path, manager, on_destroy);
}

VertexShader::VertexShader(const filesystem::path& path,
                           ResourceManager* manager,
                           std::function<void(void)> on_destroy)
    : ResourceObject(path, manager, on_destroy) {}

VertexShader::~VertexShader() {}

ByteData VertexShader::serialize() { return ByteData(); }

void VertexShader::deserialize(const ByteData& byte_data) {
  auto&& graphicsDevice = manager()->graphicsDevice();
  graphics::ShaderCode code;
  code.code = ByteData(byte_data.begin(), byte_data.end());
  code.is_binary = false;
  vertex_shader_ = graphicsDevice->createVertexShader(code);
}
}  // namespace resource
}  // namespace temp