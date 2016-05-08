/**
 * @file depth_stencile_state_impl_opengl.h
 * @brief OpenGL Depth Stencile State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-24
 */
#pragma once
#ifndef GUARD_7e9447a6a8f64b71867066fa2dfd9614
#define GUARD_7e9447a6a8f64b71867066fa2dfd9614
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/depth_stencile_state.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics { 

class DepthStencileState::Impl {
    friend class DepthStencileState;
public:
    Impl(NativeHandle device, DepthStencileState &depth_stencile_state, DepthStencileFunc depth_func, DepthStencileFunc stencile_func);
    ~Impl();

    Impl &operator=(const Impl&) = delete;
private:
    DepthStencileState &depth_stencile_state_;
    opengl::DepthStencileFuncArg arg_; 
};


} // namespace graphics
} // namespace temp

#endif // TEMP_GRAPHICS_OPENGL
#endif // GUARD_7e9447a6a8f64b71867066fa2dfd9614
