/**
 * @file device.h
 * @brief graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */
#pragma once
#ifndef GUARD_0a9808d4fbc94cccacebb5e8b0091b80
#define GUARD_0a9808d4fbc94cccacebb5e8b0091b80

#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace system {
class ThreadPool;
class Window;
}
}

namespace temp {
namespace graphics {

class Context;
class BlendState;
class DepthState;
class RasterizeState;
class SamplerState;
class VertexShader;
class PixelShader;
class ConstantBuffer;
class ShaderProgram;
class VertexBuffer;
class IndexBuffer;
class Texture;

struct DeviceParameter {
    std::shared_ptr<system::Window> window;
    std::shared_ptr<system::ThreadPool> main_thread;
    std::shared_ptr<system::ThreadPool> render_thread;
    std::shared_ptr<system::ThreadPool> load_thread;
    std::shared_ptr<system::ThreadPool> worker_thread;
};

class Device : public SmartPointerObject<Device> , public FastPImpl {
public:
    using ContextSPtr = std::shared_ptr<Context>;
    using BlendStateSPtr = std::shared_ptr<BlendState>;
    using DepthStateSPtr = std::shared_ptr<DepthState>;
    using RasterizeStateSPtr = std::shared_ptr<RasterizeState>;
    using SamplerStateSPtr = std::shared_ptr<SamplerState>;
    using VertexShaderSPtr = std::shared_ptr<VertexShader>;
    using PixelShaderSPtr = std::shared_ptr<PixelShader>;
    using ConstantBufferSPtr = std::shared_ptr<ConstantBuffer>;
    using ShaderProgramSPtr = std::shared_ptr<ShaderProgram>;
    using VertexBufferSPtr = std::shared_ptr<VertexBuffer>;
    using IndexBufferSPtr = std::shared_ptr<IndexBuffer>;
    using TextureSPtr = std::shared_ptr<Texture>;

    static SPtr create(const DeviceParameter &parameter);

private:
    Device(const DeviceParameter &parameter);

public:
    ~Device();

public:
    ContextSPtr createContext();

    VertexBufferSPtr createVertexBuffer(Size buffer_size);

    IndexBufferSPtr createIndexBuffer(Size buffer_size);

    ConstantBufferSPtr createConstantBuffer(Size buffer_size);
 
    VertexShaderSPtr createVertexShaderFromSource(const String &source);
    VertexShaderSPtr createVertexShaderFromBinary(const String &binary);

    PixelShaderSPtr createPixelShaderFromSource(const String &source);
    PixelShaderSPtr createPixelShaderFromBinary(const String &binary);

    void executeCommands(const ContextSPtr &context);
    void present();

	const NativeHandle &getNativeHandle() const { return native_handle_; }
private:
    class Impl;
    Impl *impl_;

    DeviceParameter parameter_;
	NativeHandle native_handle_;
};
    
} // namespace graphics
} // namespace temp

#endif // GUARD_0a9808d4fbc94cccacebb5e8b0091b80
