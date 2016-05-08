/**
 * @file rasterizer_state_impl_opengl.h
 * @brief OpenGL Rasterizer State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-24
 */
#pragma once
#ifndef GUARD_8e889a9843bf41ee8656622398e4d2bd
#define GUARD_8e889a9843bf41ee8656622398e4d2bd
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/rasterizer_state.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class RasterizerState::Impl {
    friend class RasterizerState;
public:
    Impl(NativeHandle device, RasterizerState &rasterizer_state, RasterizerDesc desc);
    ~Impl();

    Impl &operator=(const Impl&) = delete;
private:
    RasterizerState &rasterizer_state_;
    opengl::RasterizerFuncArg arg_; 
};
    
} // namespace graphics
} // namespace temp

#endif

#endif // GUARD_8e889a9843bf41ee8656622398e4d2bd
