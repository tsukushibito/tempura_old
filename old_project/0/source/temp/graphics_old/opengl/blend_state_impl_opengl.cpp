/**
 * @file blend_state_impl_opengl.cpp
 * @brief OpenGL blend state implementation
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-20
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/blend_state.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/blend_state_impl_opengl.h"
#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

BlendState::Impl::Impl(NativeHandle device, BlendState& blend_state,
                       BlendMode blend_mode)
    : blend_state_(blend_state) {
    switch (blend_mode) {
    case BlendMode::None:
        arg_.sfactor = GL_ONE;
        arg_.dfactor = GL_ZERO;
        break;
    case BlendMode::AlphaBlending:
        arg_.sfactor = GL_SRC_ALPHA;
        arg_.dfactor = GL_ONE_MINUS_SRC_ALPHA;
        break;
    case BlendMode::Add:
        arg_.sfactor = GL_ONE;
        arg_.dfactor = GL_ONE;
        break;
    case BlendMode::Subtract:
        arg_.sfactor = GL_ONE_MINUS_DST_COLOR;
        arg_.dfactor = GL_ZERO;
        break;
    case BlendMode::Multiply:
        arg_.sfactor = GL_ZERO;
        arg_.dfactor = GL_SRC_COLOR;
        break;
    case BlendMode::Screen:
        arg_.sfactor = GL_ONE;
        arg_.dfactor = GL_ONE_MINUS_SRC_COLOR;
        break;
    }
    blend_state_.native_handle_.pointer = &arg_;
    temp::system::Logger::trace("OpenGL Blend State has created!");

    (void)device;
}

BlendState::Impl::~Impl() {
    using namespace opengl;
    temp::system::Logger::trace("OpenGL Blend State has deleted!");
}

}  // namespace graphics
}  // namespace temp
#endif
