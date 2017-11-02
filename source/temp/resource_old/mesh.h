/**
 * @file mesh.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-06-01
 */
#pragma once
#ifndef GUARD_a46caba6fcdc4b88befb703ce714426b
#define GUARD_a46caba6fcdc4b88befb703ce714426b

#include "temp/container.h"

#include "temp/resource_old/resource_base.h"

#include "temp/graphics_/graphics.h"

namespace temp {
namespace resource_old {

class Mesh : public ResourceBase<Mesh> {
    friend class ResourceBase<Mesh>;

    using Super = ResourceBase<Mesh>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread,
                           const graphics_::Device::SPtr&   device);

    static void terminate();

    static ::temp::graphics_::Device::SPtr graphicsDevice() {
        return s_graphics_device;
    }

private:
    static ::temp::graphics_::Device::SPtr s_graphics_device;

    static const ::temp::String kTypeName;

public:
    using IndexBufferSPtr  = ::temp::graphics_::IndexBuffer::SPtr;
    using VertexBufferSPtr = ::temp::graphics_::VertexBuffer::SPtr;

    using VertexBufferTable
        = HashMap<graphics_::VertexAttribute, VertexBufferSPtr,
                  graphics_::VertexAttributeHash>;

private:
    Mesh(const system::Path& path);

    void deserialize(std::ifstream& ifs);
    void serialize(std::ofstream& ofs);

public:
    IndexBufferSPtr  indexBuffer() const;
    VertexBufferSPtr vertexBuffer(graphics_::VertexAttribute attribute) const;
    const VertexBufferTable& vertexBufferTable() const;

    void replaceIndexBuffer(const IndexBufferSPtr& ib);
    void replaceVertexBufferTable(const VertexBufferTable& vb_table);

private:
    IndexBufferSPtr   index_buffer_;
    VertexBufferTable vertex_buffer_table_;
};
}
}

#endif  // GUARD_a46caba6fcdc4b88befb703ce714426b
