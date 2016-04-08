/**
 * @file command_list_impl_opengl.cpp
 * @brief OpenGL command list
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-07
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/command_list_impl_opengl.h"

namespace  {
const temp::Size kCommandCount = 32;
} // namespace 


namespace temp {
namespace graphics {

CommandList::Impl::Impl(CommandList &command_list)
    : command_list_(command_list) 
	, command_buffer_(new CommandBuffer) {
	command_list_.native_handle_.pointer_ = command_buffer_.get();
}

} // namespace graphics
} // namespace temp
#endif // TEMP_GRAPHICS_OPENGL
