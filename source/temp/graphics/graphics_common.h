/**
 * @file graphics_common.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-25
 */
#pragma once
#ifndef GUARD_5f2aa8b3fe094bc1bc7bea6c0607781a
#define GUARD_5f2aa8b3fe094bc1bc7bea6c0607781a

#include <functional>

#include "temp/container.h"
#include "temp/define.h"
#include "temp/type.h"

#if defined(TEMP_GRAPHICS_OPENGL)
#include "temp/graphics/opengl/opengl_define.h"
#endif

namespace temp {
namespace graphics {

#if defined(TEMP_GRAPHICS_OPENGL)
namespace opengl {
class OpenGLDevice;
class OpenGLTexture;
class OpenGLVertexShader;
class OpenGLPixelShader;
class OpenGLVertexBuffer;
class OpenGLIndexBuffer;
}
using Device       = opengl::OpenGLDevice;
using Texture      = opengl::OpenGLTexture;
using VertexShader = opengl::OpenGLVertexShader;
using PixelShader  = opengl::OpenGLPixelShader;
using VertexBuffer = opengl::OpenGLVertexBuffer;
using IndexBuffer  = opengl::OpenGLIndexBuffer;
#endif
using DeviceSPtr       = std::shared_ptr<Device>;
using TextureSPtr      = std::shared_ptr<Texture>;
using VertexShaderSPtr = std::shared_ptr<VertexShader>;
using PixelShaderSPtr  = std::shared_ptr<PixelShader>;
using VertexBufferSPtr = std::shared_ptr<VertexBuffer>;
using IndexBufferSPtr  = std::shared_ptr<IndexBuffer>;

using ByteData = Vector<Int8>;

enum class TextureFormat {
    DXT1,
    DXT5,
    RGB16,
    RGB24,
    Alpha8,
    RGBA16,
    RGBA32,
};

struct TextureDesc {
    TextureFormat format;
    Size          width;
    Size          height;
    Int32         mipLevel;

    TextureDesc() {}
    explicit TextureDesc(TextureFormat fmt, Size w, Size h, Int32 mipLv)
        : format(fmt), width(w), height(h), mipLevel(mipLv) {}
};

struct ShaderCode {
    String code_;
    Bool   is_binary_ = false;
};
}
}

#endif  // GUARD_5f2aa8b3fe094bc1bc7bea6c0607781a
