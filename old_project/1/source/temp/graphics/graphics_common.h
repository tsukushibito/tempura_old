﻿#pragma once
#include "temp/common/container.h"
#include "temp/common/define.h"
#include "temp/common/type.h"

#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace temp {
namespace graphics {

#if defined(TEMP_PLATFORM_MAC)
using WindowHandle = void*;
#elif defined(TEMP_PLATFORM_WINDOWS)
using WindowHandle = HWND;
#endif

using ByteData = Vector<Int8>;

enum class GraphicsAPI {
  kOpenGL,
  kVulkan,
  kD3D11,
  kD3D12,
  kMetal,
};

enum class RenderTargetFormat {
  kRGBA32,    // 各チャネル8ビット整数のRGBA4チャネル
  kRGBA64F,   // 各チャネル16ビット浮動小数のRGBA4チャネル
  kRGBA128F,  // 各チャネル32ビット浮動小数のRGBA4チャネル
};

struct RenderTargetDesc {
  RenderTargetFormat format;
  Size width;
  Size height;
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
  PrimitiveType primitive_type;
  Size size;
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

enum class VertexFormat {
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
  kBlendWeight,
  kTexCoord0,
  kTexCoord1,
  kTexCoord2,
  kTexCoord3,

  COUNT,
};

struct VertexAttributeHash {
  std::size_t operator()(const VertexAttribute& x) const {
    using Underlying = std::underlying_type<VertexAttribute>::type;
    return std::hash<Underlying>()(static_cast<Underlying>(x));
  }
};

struct VertexElementDesc {
  VertexFormat format;
  VertexAttribute attribute;
};

struct VertexBufferDesc {
  Size element_count;
  VertexElementDesc element_descs[8];
  Size size;
};

template <typename T = VertexFormat>
Size vertexFormatSize(VertexFormat format) {
  switch (format) {
    case VertexFormat::kUInt8x4:
      return 4;
    case VertexFormat::kFloat16x2:
      return 4;
    case VertexFormat::kFloat16x4:
      return 8;
    case VertexFormat::kFloat32x2:
      return 8;
    case VertexFormat::kFloat32x4:
      return 16;
    default:
      return 0;
  }
}

template <typename T = VertexAttribute>
String vertexAttributeString(VertexAttribute attribute) {
  switch (attribute) {
    case VertexAttribute::kPosition:
      return "Position";
    case VertexAttribute::kNormal:
      return "Normal";
    case VertexAttribute::kTangent:
      return "Tangent";
    case VertexAttribute::kBinormal:
      return "Binormal";
    case VertexAttribute::kColor:
      return "Color";
    case VertexAttribute::kBlendIndices:
      return "BlendIndices";
    case VertexAttribute::kBlendWeight:
      return "BlendWeight";
    case VertexAttribute::kTexCoord0:
      return "TexCoord0";
    case VertexAttribute::kTexCoord1:
      return "TexCoord1";
    case VertexAttribute::kTexCoord2:
      return "TexCoord2";
    case VertexAttribute::kTexCoord3:
      return "TexCoord3";
    case VertexAttribute::COUNT:
      return "";
  }

  return "";
}

enum class SamplerFilter {
  kNearest,
  kLinear,

  COUNT,
};

enum class SamplerAddressMode {
  kWrap,
  kMirror,
  kClamp,
  kBorder,

  COUNT,
};

struct SamplerDesc {
  SamplerFilter filter;
  SamplerAddressMode address_mode;
};

struct ShaderCode {
  ByteData code;
  Bool is_binary = false;
};

struct Viewport {
  Float32 top;
  Float32 left;
  Float32 bottom;
  Float32 right;

  Viewport() : top(0.0f), left(0.0f), bottom(1.0f), right(1.0f) {}
};

enum class TextureFormat {
  kRGBX32,
  kRGBA32,
  kAlpha8,
  kBC1,
  kBC3,
  kBC7,
};

template <typename T = TextureFormat>
Size textureFormatBitPerPixel(TextureFormat format) {
  switch (format) {
    case TextureFormat::kRGBX32:
      return 32;
    case TextureFormat::kRGBA32:
      return 32;
    case TextureFormat::kAlpha8:
      return 8;
    case TextureFormat::kBC1:
      return 4;
    case TextureFormat::kBC3:
      return 8;
    case TextureFormat::kBC7:
      return 8;
    default:
      return 0;
  }
}

struct TextureDesc {
  TextureFormat format;
  Size width;
  Size height;
  Int32 mipLevel;
};

enum class TextureAttribute {
  kAlbedoMap,
  kRoughnessMap,
  kMetalicMap,
  kNormalMap,

  COUNT,
};

template <typename T = TextureAttribute>
String textureAttributeString(TextureAttribute attribute) {
  switch (attribute) {
    case TextureAttribute::kAlbedoMap:
      return "AlbedoMap";
    case TextureAttribute::kRoughnessMap:
      return "RoughnessMap";
    case TextureAttribute::kMetalicMap:
      return "MetalicMap";
    case TextureAttribute::kNormalMap:
      return "NormalMap";
    case TextureAttribute::COUNT:
      TEMP_ASSERT(false, "Invalid TextureAttribute!");
      return "";
  }

  TEMP_ASSERT(false, "Invalid TextureAttribute!");
  return "";
}
}
}  // namespace temp
