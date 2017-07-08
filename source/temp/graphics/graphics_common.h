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

enum class PrimitiveType {
    kTriangleList,
    kTriangleStrip,
};

struct IndexBufferDesc {
    IndexBufferFormat format;
    Size              size;
    PrimitiveType     primitive_type;
};

template <typename T = IndexBufferFormat>
Size indexBufferFormatSize(IndexBufferFormat format) {
    switch (format) {
    case IndexBufferFormat::kUInt16:
        return 2;
    case IndexBufferFormat::kUInt32:
        return 4;
    default:
        return 0;
    }
}

enum class VertexBufferFormat {
    kUInt8x4,
    kFloat16x2,
    kFloat16x4,
    kFloat32x2,
    kFloat32x4,
};

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
        using Underlying = typename std::underlying_type<VertexAttribute>::type;
        return std::hash<Underlying>()(static_cast<Underlying>(x));
    }
};

struct VertexBufferDesc {
    VertexBufferFormat format;
    VertexAttribute    attribute;
    Size               size;
};

template <typename T = VertexBufferFormat>
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

template <typename T = VertexAttribute>
String vertexAttributeString(VertexAttribute attribute) {
    switch (attribute) {
    case graphics::VertexAttribute::kPosition:
        return "POSITION";
        break;
    case graphics::VertexAttribute::kNormal:
        return "NORMAL";
        break;
    case graphics::VertexAttribute::kTangent:
        return "TANGENT";
        break;
    case graphics::VertexAttribute::kBinormal:
        return "BINORMAL";
        break;
    case graphics::VertexAttribute::kColor:
        return "COLOR";
        break;
    case graphics::VertexAttribute::kBlendIndices:
        return "BLENDINDICES";
        break;
    case graphics::VertexAttribute::kBlendWight:
        return "BLENDWIGHT";
        break;
    case graphics::VertexAttribute::kTexCoord0:
        return "TEXCOORD0";
        break;
    case graphics::VertexAttribute::kTexCoord1:
        return "TEXCOORD1";
        break;
    case graphics::VertexAttribute::kTexCoord2:
        return "TEXCOORD2";
        break;
    case graphics::VertexAttribute::kTexCoord3:
        return "TEXCOORD3";
        break;
    }

    return "";
}


struct ShaderCode {
    String code_;
    Bool   is_binary_ = false;
};
}
}

#endif  // GUARD_5f2aa8b3fe094bc1bc7bea6c0607781a
