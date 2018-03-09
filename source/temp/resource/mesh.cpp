#include "temp/resource/mesh.h"

namespace temp {
namespace resource {

Mesh::SPtr Mesh::makeShared(const filesystem::path& path,
                            ResourceManager* manager,
                            std::function<void(void)> on_destroy) {
  struct Creator : Mesh {
    Creator(const filesystem::path& path, ResourceManager* manager,
            std::function<void(void)> on_destroy)
        : Mesh(path, manager, on_destroy) {}
  };

  return std::make_shared<Creator>(path, manager, on_destroy);
}

Mesh::Mesh(const filesystem::path& path, ResourceManager* manager,
           std::function<void(void)> on_destroy)
    : ResourceObject(path, manager, on_destroy) {}

Mesh::~Mesh() {}

ByteData Mesh::serialize() { return ByteData(); }

void Mesh::deserialize(const ByteData& byte_data) {
  // TODO: implemant
}

}  // namespace resource
}  // namespace temp