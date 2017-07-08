#include "temp/resource/mesh.h"

#include "temp/resource/file_parser/tmsh.h"

namespace temp {
namespace resource {

temp::graphics::Device::SPtr Mesh::s_graphics_device;

const temp::String Mesh::kTypeName = "Mesh";

void Mesh::initialize(const system::ThreadPool::SPtr& loading_thread,
                      const graphics::Device::SPtr&   device) {
    Super::initialize(loading_thread);
    s_graphics_device = device;
}

void Mesh::terminate() {
    Super::terminate();
    s_graphics_device = nullptr;
}

Mesh::Mesh(const system::Path& path) : Super(path) {}

void Mesh::loginImpl() {
    auto meshData = tmsh::Tmsh(byte_data_);
    // index_buffer_ = s_graphics_device->createIndexBuffer();
    // vertex_buffer_table_;
}

Mesh::IndexBufferSPtr Mesh::indexBuffer() const { return index_buffer_; }

Mesh::VertexBufferSPtr Mesh::vertexBuffer(graphics::VertexAttribute attribute) const {
    auto iter = vertex_buffer_table_.find(attribute);
    if (iter == vertex_buffer_table_.end()) {
        return nullptr;
    }
    return iter->second;
}

const Mesh::VertexBufferTable& Mesh::vertexBufferTable() const {
    return vertex_buffer_table_;
}
}
}
