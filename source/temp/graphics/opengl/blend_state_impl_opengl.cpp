/**
 * @file blend_state_impl_opengl.cpp
 * @brief OpenGL blend state implementation
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-20
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/blend_state.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/blend_state_impl_opengl.h"

namespace temp {
namespace graphics {

BlendState::Impl::Impl(BlendState &blend_state, BlendMode blend_mode) : blend_state_(blend_state) {
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
    blend_state_.native_handle_.pointer_ = &arg_;
    temp::system::ConsoleLogger::trace("OpenGL Blend State has created!");
}

BlendState::Impl::~Impl() {
    using namespace opengl;
    temp::system::ConsoleLogger::trace("OpenGL Blend State has deleted!");
}

} // namespace graphics
} // namespace temp
#endif
