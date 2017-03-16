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
#include "temp/graphics_old/pixel_shader.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

class PixelShader::Impl {
    friend class PixelShader;

public:
    Impl(NativeHandle device, PixelShader& pixel_shader, const String& source,
         Bool is_binary);
    ~Impl();

    Impl& operator=(const Impl&) = delete;

private:
    PixelShader& pixel_shader_;
};

}  // namespace graphics
}  // namespace temp

#endif

#endif  // GUARD_20c2ec6370ae44c09a4ef3ec8fb6b83c
