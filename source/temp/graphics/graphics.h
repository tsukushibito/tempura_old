/**
 * @file graphics.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-02-27
 */
#pragma once
#ifndef GUARD_06ee30f321684357842780bfa43ecbf1
#define GUARD_06ee30f321684357842780bfa43ecbf1

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/opengl/opengl_device.h"

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

using Device = opengl::OpenGLDevice;
}
}

#endif  // GUARD_06ee30f321684357842780bfa43ecbf1
