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
                         std::function<void(const ResourceId&)> on_destroy);

  Mesh(const filesystem::path& path, ResourceManager* manager,
       std::function<void(const ResourceId&)> on_destroy);

 public:
  ~Mesh();

  graphics::VertexBuffer::SPtr vertexBuffer() const { return vertex_buffer_; }

  graphics::IndexBuffer::SPtr indexBuffer() const { return index_buffer_; }

  void replaceVertexBuffer(const graphics::VertexBuffer::SPtr& vertex_buffer) {
    vertex_buffer_ = vertex_buffer;
  }

  void replaceIndexBuffer(const graphics::IndexBuffer::SPtr& index_buffer) {
    index_buffer_ = index_buffer;
  }

 private:
  ByteData serialize() override;
  void deserialize(const ByteData& byte_data) override;

 private:
  graphics::VertexBuffer::SPtr vertex_buffer_;
  graphics::IndexBuffer::SPtr index_buffer_;
};
}  // namespace resource
}  // namespace temp
