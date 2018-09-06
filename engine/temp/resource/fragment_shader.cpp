#include "temp/resource/fragment_shader.h"
#include "temp/graphics/graphics.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

FragmentShader::FragmentShader(
    const filesystem::path& path, ResourceManager* manager,
    std::function<void(const ResourceId&)> on_destroy)
    : ResourceBase(type_name(), path, manager, on_destroy) {}

ByteData FragmentShader::Serialize() const { return ByteData(); }

void FragmentShader::Deserialize(const ByteData& byte_data) {
  fragment_shader_ =
      manager().graphics_device()->CreateFragmentShader(byte_data);
}

}  // namespace resource
}  // namespace temp
