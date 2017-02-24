/**
 * @file render_texture.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-02-09
 */
#pragma once
#ifndef GUARD_7dc195c916574df58a8d407361ab3c22
#define GUARD_7dc195c916574df58a8d407361ab3c22

#include "temp/type.h"

namespace temp {
namespace render {

struct RenderTexture;
using RenderTextureHandle = Handle<RenderTexture>;

struct RenderTexture {
    RenderTextureHandle handle_;
};
}
}

#endif  // GUARD_7dc195c916574df58a8d407361ab3c22
