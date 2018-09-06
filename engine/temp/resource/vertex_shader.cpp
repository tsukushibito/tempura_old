#include "temp/resource/vertex_shader.h"
#include "temp/graphics/graphics.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

VertexShader::VertexShader(const filesystem::path& path,
                           ResourceManager* manager,
                           std::function<void(const ResourceId&)> on_destroy)
    : ResourceBase(type_name(), path, manager, on_destroy) {}

ByteData VertexShader::Serialize() const { return ByteData(); }

void VertexShader::Deserialize(const ByteData& byte_data) {
  vertex_shader_ = manager().graphics_device()->CreateVertexShader(byte_data);
}

}  // namespace resource
}  // namespace temp
