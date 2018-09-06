#pragma once
#include "temp/resource/resource_base.h"

#include "temp/graphics/fragment_shader.h"

namespace temp {
namespace resource {
class FragmentShader : public ResourceBase,
                       public ResourcePointer<FragmentShader> {
  friend class ResourcePointer<FragmentShader>;

 public:
  static const std::string& type_name() {
    static std::string type_name("FragmentShader");
    return type_name;
  }

 private:
  FragmentShader(const filesystem::path& path, ResourceManager* manager,
                 std::function<void(const ResourceId&)> on_destroy);

 public:
  ~FragmentShader() = default;

  graphics::FragmentShaderSPtr fragment_shader() const {
    return fragment_shader_;
  }

 private:
  ByteData Serialize() const override;
  void Deserialize(const ByteData& byte_data) override;

 private:
  graphics::FragmentShaderSPtr fragment_shader_;
};
}  // namespace resource
}  // namespace temp