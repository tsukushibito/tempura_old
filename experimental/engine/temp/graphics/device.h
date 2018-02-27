#pragma once
#include "temp/common/type.h"

namespace temp {
namespace graphics {

class IndexBuffer;
using IndexBufferSPtr = std::shared_ptr<IndexBuffer>;
class PixelShader;
using PixelShaderSPtr = std::shared_ptr<PixelShader>;
class RenderTarget;
using RenderTargetSPtr = std::shared_ptr<RenderTarget>;
class Texture;
using TextureSPtr = std::shared_ptr<Texture>;
class VertexBuffer;
using VertexBufferSPtr = std::shared_ptr<VertexBuffer>;
class VertexShader;
using VertexShaderSPtr = std::shared_ptr<VertexShader>;

class Device : Uncopyable {
 public:
  using SPtr = std::shared_ptr<Device>;
  using WPtr = std::weak_ptr<Device>;
  using UPtr = std::unique_ptr<Device>;

  virtual ~Device() = default;

  virtual RenderTargetSPtr createRenderTarget(const RenderTargetDesc& desc) = 0;

  virtual TextureSPtr createTexture(const TextureDesc& desc,
                                    const void* data) = 0;

  virtual VertexBufferSPtr createVertexBuffer(const VertexBufferDesc& desc,
                                              const void* data) = 0;

  virtual IndexBufferSPtr createIndexBuffer(const IndexBufferDesc& desc,
                                            const void* data) = 0;

  virtual PixelShaderSPtr createPixelShader(const ShaderCode& code) = 0;

  virtual VertexShaderSPtr createVertexShader(const ShaderCode& code) = 0;

  virtual GraphicsAPI api() const = 0;
};

class IndexBuffer : Uncopyable {
 public:
  using SPtr = std::shared_ptr<IndexBuffer>;
  using WPtr = std::weak_ptr<IndexBuffer>;
  using UPtr = std::unique_ptr<IndexBuffer>;

 protected:
  IndexBuffer() = default;

 public:
  virtual ~IndexBuffer() = default;

  const IndexBufferDesc& desc() const { return desc_; }

  virtual const ByteData data() = 0;

 protected:
  IndexBufferDesc desc_;
};

class PixelShader : Uncopyable {
 public:
  using SPtr = std::shared_ptr<PixelShader>;
  using WPtr = std::weak_ptr<PixelShader>;
  using UPtr = std::unique_ptr<PixelShader>;

 protected:
  PixelShader() = default;

 public:
  virtual ~PixelShader() = default;

  const ShaderCode& code() const { return code_; }

 protected:
  ShaderCode code_;
};

class RenderTarget : Uncopyable {
 public:
  using SPtr = std::shared_ptr<RenderTarget>;
  using WPtr = std::weak_ptr<RenderTarget>;
  using UPtr = std::unique_ptr<RenderTarget>;

 protected:
  RenderTarget() = default;

 public:
  virtual ~RenderTarget() = default;

  const RenderTargetDesc& desc() const { return desc_; }

 protected:
  RenderTargetDesc desc_;
};

class Texture : Uncopyable {
 public:
  using SPtr = std::shared_ptr<Texture>;
  using WPtr = std::weak_ptr<Texture>;
  using UPtr = std::unique_ptr<Texture>;

 protected:
  Texture() = default;

 public:
  virtual ~Texture() = default;

  const TextureDesc& desc() const { return desc_; }

 protected:
  TextureDesc desc_;
};

class VertexBuffer : Uncopyable {
 public:
  using SPtr = std::shared_ptr<VertexBuffer>;
  using WPtr = std::weak_ptr<VertexBuffer>;
  using UPtr = std::unique_ptr<VertexBuffer>;

 protected:
  VertexBuffer() = default;

 public:
  virtual ~VertexBuffer() = default;

  const VertexBufferDesc& desc() const { return desc_; }

  virtual const ByteData data() = 0;

 protected:
  VertexBufferDesc desc_;
};

class VertexShader : Uncopyable {
 public:
  using SPtr = std::shared_ptr<VertexShader>;
  using WPtr = std::weak_ptr<VertexShader>;
  using UPtr = std::unique_ptr<VertexShader>;

 protected:
  VertexShader() = default;

 public:
  virtual ~VertexShader() = default;

  const ShaderCode& code() const { return code_; }

 protected:
  ShaderCode code_;
};

}  // namespace graphics
}  // namespace temp