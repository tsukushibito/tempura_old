#include "temp/graphics/mesh.h"

namespace temp {
namespace resource {

namespace {

struct MeshHeader {
    Char   magic[4];
    UInt32 version;
};

struct VertexHeader {
    Char   signature[4];
    UInt32 format;
    UInt32 vertex_count;
};

struct IndexHeader {
    Char   signature[4];
    UInt32 format;
    UInt32 index_count;
};
}

temp::graphics::DeviceSPtr Mesh::s_graphics_device;

void Mesh::initialize(const system::ThreadPool::SPtr& loading_thread,
                      const graphics::DeviceSPtr&     device) {
    Super::initialize(loading_thread);
    s_graphics_device = device;
}

void Mesh::terminate() {
    Super::terminate();
    s_graphics_device = nullptr;
}

Mesh::Mesh(const system::Path& path) : Super(path) {}

void Mesh::loginImpl() { auto&& byte_data = byteData(); }
}
}
