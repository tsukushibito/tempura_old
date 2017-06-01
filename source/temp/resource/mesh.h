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

#include "temp/resource/resource_base.h"

#include "temp/graphics/graphics.h"

namespace temp {
namespace resource {

enum class VertexFormat
{
    kSimple,
    kStatic,
    kSkinning,
};

class Mesh : public ResourceBase<Mesh> {
    friend class ResourceBase<Mesh>;

    using Super = ResourceBase<Mesh>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread,
                           const graphics::Device::SPtr&     device);

    static void terminate();

private:
    static temp::graphics::Device::SPtr s_graphics_device;

    static const temp::String kTypeName;

private:
    Mesh(const system::Path& path);

    void loginImpl();

    temp::graphics::IndexBuffer::SPtr  index_buffer_;
    temp::graphics::VertexBuffer::SPtr vertex_buffer_;
};
}
}

#endif  // GUARD_a46caba6fcdc4b88befb703ce714426b
