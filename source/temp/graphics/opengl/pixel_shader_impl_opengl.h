/**
 * @file pixel_shader_impl_opengl.h
 * @brief OpenGL pixel shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */
#pragma once
#ifndef GUARD_20c2ec6370ae44c09a4ef3ec8fb6b83c
#define GUARD_20c2ec6370ae44c09a4ef3ec8fb6b83c

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/pixel_shader.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class PixelShader::Impl {
    friend class PixelShader;
public:
    Impl(PixelShader &pixel_shader);
    ~Impl();

    Impl &operator=(const Impl&) = delete;
private:
    PixelShader &pixel_shader_;
};
    
} // namespace graphics
} // namespace temp

#endif

#endif // GUARD_20c2ec6370ae44c09a4ef3ec8fb6b83c
