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

#include "temp/graphics/graphics.h"
namespace temp {
namespace graphics {

class Texture;
using TextureHandle = Handle<Texture>;

class Texture : public SmartPointerObject<Texture> {
    friend class Device;

private:
    Texture(const TextureDesc& desc);

public:
    ~Texture();

    TextureHandle handle() const { return handle_; }
}
}
}

#endif  // GUARD_70686145556f45efb5ba565866b86464
