#pragma once
#include "temp/resource/resource_base.h"

#include "temp/graphics/vertex_shader.h"

namespace temp {
namespace resource {
class VertexShader : public ResourceBase, public ResourcePointer<VertexShader> {
  friend class ResourcePointer<VertexShader>;

 public:
  static const std::string& type_name() {
    static std::string type_name("VertexShader");
    return type_name;
  }

 private:
  VertexShader(const filesystem::path& path, ResourceManager* manager,
               std::function<void(const ResourceId&)> on_destroy);

 public:
  ~VertexShader() = default;

  graphics::VertexShaderSPtr vertex_shader() const { return vertex_shader_; }

 private:
  ByteData Serialize() const override;
  void Deserialize(const ByteData& byte_data) override;

 private:
  graphics::VertexShaderSPtr vertex_shader_;
};
}  // namespace resource
}  // namespace temp