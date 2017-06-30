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

Mesh::VertexBufferSPtr Mesh::vertexBuffer(VertexAttribute attribute) const {
    auto iter = vertex_buffer_table_.find(attribute);
    if (iter == vertex_buffer_table_.end()) {
        return nullptr;
    }
    return iter->second;
}

const Mesh::VertexBufferTable& Mesh::vertexBufferTable() const {
    return vertex_buffer_table_;
}

String vertexAttributeString(Mesh::VertexAttribute attribute) {
    switch (attribute) {
    case Mesh::VertexAttribute::kPosition:
        return "POSITION";
        break;
    case Mesh::VertexAttribute::kNormal:
        return "NORMAL";
        break;
    case Mesh::VertexAttribute::kTangent:
        return "TANGENT";
        break;
    case Mesh::VertexAttribute::kBinormal:
        return "BINORMAL";
        break;
    case Mesh::VertexAttribute::kColor:
        return "COLOR";
        break;
    case Mesh::VertexAttribute::kBlendIndices:
        return "BLENDINDICES";
        break;
    case Mesh::VertexAttribute::kBlendWight:
        return "BLENDWIGHT";
        break;
    case Mesh::VertexAttribute::kTexCoord0:
        return "TEXCOORD0";
        break;
    case Mesh::VertexAttribute::kTexCoord1:
        return "TEXCOORD1";
        break;
    case Mesh::VertexAttribute::kTexCoord2:
        return "TEXCOORD2";
        break;
    case Mesh::VertexAttribute::kTexCoord3:
        return "TEXCOORD3";
        break;
    }

    return "";
}
}
}
