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
#include "temp/temp_math.h"

#include "temp/resource/resource_base.h"

#include "temp/graphics/graphics.h"

namespace temp {
namespace resource {

class Mesh : public ResourceBase<Mesh> {
    friend class ResourceBase<Mesh>;

    using Super = ResourceBase<Mesh>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread,
                           const graphics::Device::SPtr&   device);

    static void terminate();

private:
    static temp::graphics::Device::SPtr s_graphics_device;

    static const temp::String kTypeName;

public:
    enum class VertexAttribute {
        kPosition,
        kNormal,
        kTangent,
        kBinormal,
        kColor,
        kBlendIndices,
        kBlendWight,
        kTexCoord0,
        kTexCoord1,
        kTexCoord2,
        kTexCoord3,
    };

    struct VertexAttributeHash {
        std::size_t operator()(const VertexAttribute& x) const {
            using Underlying =
                typename std::underlying_type<VertexAttribute>::type;
            return std::hash<Underlying>()(static_cast<Underlying>(x));
        }
    };

    using Vector3F32   = math::Vector3;
    using Vector4UInt8 = math::Vector4Base<UInt8>;
    using Vector2F32   = math::Vector2;

    using IndexBufferSPtr  = temp::graphics::IndexBuffer::SPtr;
    using VertexBufferSPtr = temp::graphics::VertexBuffer::SPtr;

    using VertexBufferTable
        = HashMap<VertexAttribute, VertexBufferSPtr, VertexAttributeHash>;

    Bool intereaved() const { return intereaved_; }

private:
    Mesh(const system::Path& path);

    void loginImpl();

public:
    IndexBufferSPtr  indexBuffer() const;
    VertexBufferSPtr vertexBuffer(VertexAttribute attribute) const;
    const VertexBufferTable& vertexBufferTable() const;

private:
    Bool intereaved_ = false;

    IndexBufferSPtr   index_buffer_;
    VertexBufferTable vertex_buffer_table_;
};

String vertexAttributeString(Mesh::VertexAttribute attribute);
}
}

#endif  // GUARD_a46caba6fcdc4b88befb703ce714426b
