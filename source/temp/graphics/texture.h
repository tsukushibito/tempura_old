/**
 * @file texture.h
 * @brief テクスチャGPUリソース
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-17
 */
#pragma once
#ifndef GUARD_70686145556f45efb5ba565866b86464
#define GUARD_70686145556f45efb5ba565866b86464

#include "temp/type.h"

namespace temp {
namespace graphics {

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


class Texture : public SmartPointerObject<Texture> {
    friend class Device;

private:
    Texture(const TextureDesc& desc);

public:
    ~Texture();

};

}
}

#endif  // GUARD_70686145556f45efb5ba565866b86464
