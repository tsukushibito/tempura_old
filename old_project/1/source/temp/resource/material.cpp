#include "temp/resource/material.h"
#include "temp/core/logger.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

namespace {
const Char kMaterialSignature[] = "TMAT";
}  // namespace

Material::SPtr Material::makeShared(
    const filesystem::path& path, ResourceManager* manager,
    std::function<void(const ResourceId&)> on_destroy) {
  struct Creator : Material {
    Creator(const filesystem::path& path, ResourceManager* manager,
            std::function<void(const ResourceId&)> on_destroy)
        : Material(path, manager, on_destroy) {}
  };

  return std::make_shared<Creator>(path, manager, on_destroy);
}

Material::Material(const filesystem::path& path, ResourceManager* manager,
                   std::function<void(const ResourceId&)> on_destroy)
    : ResourceObject(path, manager, on_destroy) {}

Material::~Material() {}

ByteData Material::serialize() {
  using namespace temp::graphics;
  return ByteData();
}

void Material::deserialize(const ByteData& byte_data) {
  using namespace temp::graphics;
}

}  // namespace resource
}  // namespace temp
