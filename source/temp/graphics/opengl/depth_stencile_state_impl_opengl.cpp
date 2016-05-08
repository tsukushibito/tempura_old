/**
 * @file depth_stencile_state_impl_opengl.cpp
 * @brief OpenGL Depth Stencile State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-24
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/depth_stencile_state.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/depth_stencile_state_impl_opengl.h"

namespace temp {
namespace graphics {

DepthStencileState::Impl::Impl(NativeHandle device, DepthStencileState &depth_stencile_state, DepthStencileFunc depth_func,
                               DepthStencileFunc stencile_func)
    : depth_stencile_state_(depth_stencile_state) {
    auto depthStencileFuncToGLenum = [](DepthStencileFunc func) {
        GLenum glenum = GL_ALWAYS;
        switch (func) {
        case DepthStencileFunc::Never:
            glenum = GL_NEVER;
            break;
        case DepthStencileFunc::Less:
            glenum = GL_LESS;
            break;
        case DepthStencileFunc::LessEqual:
            glenum = GL_LEQUAL;
            break;
        case DepthStencileFunc::Equal:
            glenum = GL_EQUAL;
            break;
        case DepthStencileFunc::GreaterEqual:
            glenum = GL_GEQUAL;
            break;
        case DepthStencileFunc::Greater:
            glenum = GL_GREATER;
            break;
        case DepthStencileFunc::NotEqual:
            glenum = GL_NOTEQUAL;
            break;
        case DepthStencileFunc::Always:
            glenum = GL_ALWAYS;
            break;
        }
        return glenum;
    };

    arg_.depth_func = depthStencileFuncToGLenum(depth_func);
    arg_.stencile_func = depthStencileFuncToGLenum(stencile_func);

    depth_stencile_state.native_handle_.pointer_ = &arg_;
    temp::system::ConsoleLogger::trace("OpenGL Depth Stencile State has created!");

    (void)device;
}

DepthStencileState::Impl::~Impl() {
    using namespace opengl;
    temp::system::ConsoleLogger::trace("OpenGL Depth Stencile State has deleted!");
}

} // namespace graphics
} // namespace temp

#endif
