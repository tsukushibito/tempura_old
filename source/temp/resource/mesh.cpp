#include "temp/resource/mesh.h"

#include "temp/resource/file_parser/tmsh.h"

namespace temp {
namespace resource {

namespace {
const Int32 kVersion         = 1;
const Int32 kSignatureLength = 4;
const Char* kMeshSignature   = "TMSH";
const Char* kVertexSignature = "TVRT";
const Char* kIndexSignature  = "TIDX";
}

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

void Mesh::deserialize(std::ifstream& ifs) {
    Char signature[kSignatureLength];
    ifs.read(signature, kSignatureLength);
    if (String(signature) != String(kMeshSignature)) {
        // シグネチャが違う
        return;
    }
    Int32 version;
    ifs.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (version != kVersion) {
        // バージョン違いのときの処理
    }
    decltype(vertex_buffer_table_.size()) vertex_chunk_count;
    ifs.read(reinterpret_cast<char*>(&vertex_chunk_count),
             sizeof(vertex_chunk_count));

    ifs.read(signature, kSignatureLength);
    if (String(signature) != String(kIndexSignature)) {
        // シグネチャが違う
        return;
    }

    temp::graphics::IndexBufferDesc ib_desc;
    ifs.read(reinterpret_cast<char*>(ib_desc.format), sizeof(ib_desc.format));
    ifs.read(reinterpret_cast<char*>(ib_desc.primitive_type),
             sizeof(ib_desc.primitive_type));
    ifs.read(reinterpret_cast<char*>(ib_desc.size), sizeof(ib_desc.size));
    ByteData data;
    data.resize(ib_desc.size);
    ifs.read(reinterpret_cast<char*>(&data[0]), data.size());

    index_buffer_ = s_graphics_device->createIndexBuffer(ib_desc, &data[0]);

    for (Int32 i = 0; i < vertex_chunk_count; ++i) {
        ifs.read(signature, kSignatureLength);
        if (String(signature) != String(kVertexSignature)) {
            // シグネチャが違う
            return;
        }
        temp::graphics::VertexBufferDesc vb_desc;
        ifs.read(reinterpret_cast<char*>(vb_desc.format),
                 sizeof(vb_desc.format));
        ifs.read(reinterpret_cast<char*>(vb_desc.attribute),
                 sizeof(vb_desc.attribute));
        ifs.read(reinterpret_cast<char*>(vb_desc.size), sizeof(vb_desc.size));
        ByteData data;
        data.resize(vb_desc.size);
        ifs.read(reinterpret_cast<char*>(&data[0]), data.size());

        vertex_buffer_table_[vb_desc.attribute]
            = s_graphics_device->createVertexBuffer(vb_desc, &data[0]);
    }
}

void Mesh::serialize(std::ofstream& ofs) {
    ofs.write(kMeshSignature, kSignatureLength);
    ofs.write(reinterpret_cast<const char*>(&kVersion), sizeof(kVersion));
    auto vertex_chunk_count = vertex_buffer_table_.size();
    ofs.write(reinterpret_cast<char*>(&vertex_chunk_count),
              sizeof(vertex_chunk_count));

    if (index_buffer_ != nullptr) {
        ofs.write(kIndexSignature, kSignatureLength);
        auto&& desc = index_buffer_->desc();
        ofs.write(reinterpret_cast<const char*>(&desc.format), sizeof(desc.format));
        ofs.write(reinterpret_cast<const char*>(&desc.primitive_type),
                  sizeof(desc.primitive_type));
        ofs.write(reinterpret_cast<const char*>(&desc.size), sizeof(desc.size));
        auto&& data = index_buffer_->data();
        ofs.write(reinterpret_cast<const char*>(&data[0]), data.size());
    }

    for (auto&& key_value : vertex_buffer_table_) {
        ofs.write(kVertexSignature, kSignatureLength);
        auto&  attr = key_value.first;
        auto&  vb   = key_value.second;
        auto&& desc = vb->desc();
        ofs.write(reinterpret_cast<const char*>(&desc.format), sizeof(desc.format));
        ofs.write(reinterpret_cast<const char*>(&desc.attribute),
                  sizeof(desc.attribute));
        ofs.write(reinterpret_cast<const char*>(&desc.size), sizeof(desc.size));
        auto&& data = vb->data();
        ofs.write(reinterpret_cast<const char*>(&data[0]), data.size());
    }
}

Mesh::IndexBufferSPtr Mesh::indexBuffer() const { return index_buffer_; }

Mesh::VertexBufferSPtr Mesh::vertexBuffer(
    graphics::VertexAttribute attribute) const {
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
