#pragma once
#include <memory>
#include "temp/common/common.h"
#include "temp/graphics/device.h"
#include "temp/resource/resource_object.h"

namespace temp {
namespace resource {
class Mesh : public ResourceObject {
  friend class ResourceManager;

 public:
  using UPtr = std::unique_ptr<Mesh>;
  using SPtr = std::shared_ptr<Mesh>;
  using WPtr = std::weak_ptr<Mesh>;

 private:
  static SPtr makeShared(const filesystem::path& path, ResourceManager* manager,
                         std::function<void(void)> on_destroy);

  Mesh(const filesystem::path& path, ResourceManager* manager,
       std::function<void(void)> on_destroy);

 public:
  ~Mesh();

  graphics::VertexBuffer::SPtr graphicsVertexBuffer() const {
    return vartex_buffer_;
  }

  graphics::IndexBuffer::SPtr graphicsIndexBuffer() const {
    return index_buffer_;
  }

 private:
  void prepare(const ByteData& byte_data) override;

 private:
  graphics::VertexBuffer::SPtr vertex_buffer_;
  graphics::IndexBuffer::SPtr index_buffer_;
};
}  // namespace resource
}  // namespace temp