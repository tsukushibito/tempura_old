/**
 * @file context.h
 * @brief graphics context
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-30
 */
#pragma once
#ifndef GUARD_74a86bf4fe844001ba72abbdec3d8fdd
#define GUARD_74a86bf4fe844001ba72abbdec3d8fdd

#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class Device;
class BlendState;
class DepthStencileState;
class RasterizeState;
class SamplerState;
class VertexShader;
class PixelShader;
class ConstantBuffer;
class ShaderProgram;
class VertexBuffer;
class IndexBuffer;
class Texture;

class Context : public SmartPointerObject< Context >, public FastPImpl {
    friend class Device;
private:
    using DeviceSPtr = std::shared_ptr<Device>;
    using BlendStateSPtr = std::shared_ptr<BlendState>;
    using DepthStencileStateSPtr = std::shared_ptr<DepthStencileState>;
    using RasterizeStateSPtr = std::shared_ptr<RasterizeState>;
    using SamplerStateSPtr = std::shared_ptr<SamplerState>;
    using VertexShaderSPtr = std::shared_ptr<VertexShader>;
    using PixelShaderSPtr = std::shared_ptr<PixelShader>;
    using ConstantBufferSPtr = std::shared_ptr<ConstantBuffer>;
    using ShaderProgramSPtr = std::shared_ptr<ShaderProgram>;
    using VertexBufferSPtr = std::shared_ptr<VertexBuffer>;
    using IndexBufferSPtr = std::shared_ptr<IndexBuffer>;
    using TextureSPtr = std::shared_ptr<Texture>;

    Context(const DeviceSPtr &device);

public:
    ~Context();

    void setVertexBuffer(UInt32 slotNum, const VertexBufferSPtr &vertex_buffer);
    void setIndexBuffer(const IndexBufferSPtr &index_buffer);
    void setVertexShader(const VertexShaderSPtr &vertex_shader);
    void setPixelShader(const PixelShaderSPtr &pixel_shader);
    void setConstantBuffer(const String &name, const ConstantBufferSPtr &constant_buffer);
    void setTexture(const String &name, const TextureSPtr &texture);

private:
    class Impl;
    Impl *impl_;
};

} // namespace graphics
} // namespace temp

#endif // GUARD_74a86bf4fe844001ba72abbdec3d8fdd
