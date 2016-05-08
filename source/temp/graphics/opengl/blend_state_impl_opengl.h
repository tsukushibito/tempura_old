/**
 * @file blend_state_impl_opengl.h
 * @brief OpenGL blend state implementation
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-20
 */
#pragma once
#ifndef GUARD_7ca082beb10544afa098f75d457b37a9
#define GUARD_7ca082beb10544afa098f75d457b37a9
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/blend_state.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class BlendState::Impl {
    friend class BlendState;
public:
    Impl(NativeHandle device, BlendState &blend_state, BlendMode blend_mode);
    ~Impl();

    Impl &operator=(const Impl&) = delete;
private:
    BlendState &blend_state_;
    opengl::BlendFuncArg arg_; 
};
    
} // namespace graphics
} // namespace temp

#endif
#endif // GUARD_7ca082beb10544afa098f75d457b37a9
