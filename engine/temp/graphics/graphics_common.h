#pragma once
#include <vector>
#include <string>
#include "temp/core/core.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace temp {
namespace graphics {

using ByteData = std::vector<std::uint8_t>;

enum class GraphicsApi {
  kOpenGl,
  kVulkan,
  kD3d11,
  kD3d12,
};

enum class RenderTargetFormat {
  kRGBA32,    // 各チャネル8ビット整数のRGBA4チャネル
  kRGBA64F,   // 各チャネル16ビット浮動小数のRGBA4チャネル
  kRGBA128F,  // 各チャネル32ビット浮動小数のRGBA4チャネル
};

struct RenderTargetDesc {
  RenderTargetFormat format;
  std::size_t width;
  std::size_t height;
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
  std::size_t size;
};

template <typename T = IndexBufferFormat>
std::size_t IndexBufferFormatSize(IndexBufferFormat format) {
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
  std::size_t element_count;
  VertexElementDesc element_descs[8];
  std::size_t size;
};

template <typename T = VertexFormat>
std::size_t VertexFormatSize(VertexFormat format) {
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
std::string VertexAttributeString(VertexAttribute attribute) {
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
  bool is_binary = false;
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
std::size_t TextureFormatBitPerPixel(TextureFormat format) {
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
  std::size_t width;
  std::size_t height;
  std::int32_t mipLevel;
};

enum class TextureAttribute {
  kAlbedoMap,
  kRoughnessMap,
  kMetalicMap,
  kNormalMap,

  COUNT,
};

template <typename T = TextureAttribute>
std::string TextureAttributeString(TextureAttribute attribute) {
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
}  // namespace graphics
}  // namespace temp
