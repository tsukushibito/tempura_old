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

enum class TextureFormat {
    kDXT1,
    kDXT5,
    kRGB16,
    kRGB24,
    kAlpha8,
    kRGBA16,
    kRGBA32,
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

enum class IndexBufferFormat {
    kUInt16,
    kUInt32,
};


struct IndexBufferDesc {
    IndexBufferFormat format;
    Size              size;
};

enum class VertexBufferFormat {
    kUInt8x4,
    kFloat16x2,
    kFloat16x4,
    kFloat32x2,
    kFloat32x4,
};

struct VertexBufferDesc {
    VertexBufferFormat format;
    Size               size;
};

template<typename T = VertexBufferFormat>
Size vertexBufferFormatSize(VertexBufferFormat format) {
    switch (format) {
    case VertexBufferFormat::kUInt8x4:
        return 2;
    case VertexBufferFormat::kFloat16x2:
        return 4;
    case VertexBufferFormat::kFloat16x4:
        return 8;
    case VertexBufferFormat::kFloat32x2:
        return 8;
    case VertexBufferFormat::kFloat32x4:
        return 16;
    default:
        return 0;
    }
}

enum class PrimitiveType {
    kTriangleList,
    kTriangleStrip,
};


struct ShaderCode {
    String code_;
    Bool   is_binary_ = false;
};
}
}

#endif  // GUARD_5f2aa8b3fe094bc1bc7bea6c0607781a
