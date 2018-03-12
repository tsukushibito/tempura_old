#include "temp/resource/mesh.h"
#include "temp/core/logger.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

namespace {
const Char kMeshSignature[] = "TMSH";
const Char kVBSignature[] = "VBUF";
const Char kIBSignature[] = "IBUF";
const Char kMeshTag[] = "Mesh";
}  // namespace

Mesh::SPtr Mesh::makeShared(const filesystem::path& path,
                            ResourceManager* manager,
                            std::function<void(const ResourceId&)> on_destroy) {
  struct Creator : Mesh {
    Creator(const filesystem::path& path, ResourceManager* manager,
            std::function<void(const ResourceId&)> on_destroy)
        : Mesh(path, manager, on_destroy) {}
  };

  return std::make_shared<Creator>(path, manager, on_destroy);
}

Mesh::Mesh(const filesystem::path& path, ResourceManager* manager,
           std::function<void(const ResourceId&)> on_destroy)
    : ResourceObject(path, manager, on_destroy) {}

Mesh::~Mesh() {}

ByteData Mesh::serialize() {
  using namespace temp::graphics;
  if (vertex_buffer_ == nullptr) {
    TEMP_LOG_WARN(kMeshTag, fmt::format("vertex buffer is null. path: {0}",
                                        path().string()));
    return ByteData();
  }

  auto&& vb_desc = vertex_buffer_->desc();
  auto&& ib_desc = index_buffer->desc();
  Size size = (sizeof(kMeshSignature) - 1) + (sizeof(kVerticesSignature) - 1) +
              sizeof(VertexBufferDesc) + vb_desc.size +
              (sizeof(kIndicesSignature) - 1) + sizeof(IndexBufferDesc) +
              ib_desc.size;
  auto byte_data = ByteData(size);

  // Mesh signature
  Size index = 0;
  for (auto i = index; i < sizeof(kMeshSignature) - 1; ++i) {
    byte_data[i] = kMeshSignature[i];
  }
  index += sizeof(kMeshSignature) - 1;

  // VB signature
  for (auto i = index; i < sizeof(kVBSignature) - 1; ++i) {
    byte_data[i] = kVBSignature[i];
  }
  index += sizeof(kVBSignature) - 1;

  // VB desc
  *reinterpret_cast<VertexBufferDesc*>(&byte_data[index]) = vb_desc;
  index += sizeof(VertexBufferDesc);

  // VB data
  memcpy(&byte_data[index], &vertex_buffer_->data()[0], vb_desc.size);
  index += vb_desc.size;

  // IB signature
  for (auto i = 0; i < sizeof(kIBSignature) - 1; ++i) {
    byte_data[i] = kIBSignature[i];
  }
  index += sizeof(kIBSignature) - 1;

  // IB desc
  *reinterpret_cast<IndexBufferDesc*>(&byte_data[index]) = ib_desc;
  index += sizeof(IndexBufferDesc);

  // IB data
  memcpy(&byte_data[index], &index_buffer->data()[0], ib_desc.size);
  index += ib_desc.size;

  return byte_data;
}

void Mesh::deserialize(const ByteData& byte_data) {
  using namespace temp::graphics;
  Size index = 0;
  auto result = std::memcmp(&byte_data[index], kMeshSignature,
                            sizeof(kMeshSignature) - 1);
  if (result != 0) {
    TEMP_LOG_ERROR(kMeshTag,
                   fmt::format("Not mesh file: {0}", path().string()));
    return;
  }

  index += sizeof(kMeshSignature) - 1;
  auto desc = *reinterpret_cast<const VertexBufferDesc*>(&byte_data[index]);
  index += sizeof(VertexBufferDesc);
  if (desc.size > byte_data.size() - index) {
    TEMP_LOG_ERROR(kMeshTag,
                   fmt::format("Invalid data. file: {0}", path().string()));
    return;
  }

  auto&& device = manager()->graphicsDevice();
  vertex_buffer_ = device->createVertexBuffer(desc, &byte_data[index]);
}

}  // namespace resource
}  // namespace temp
