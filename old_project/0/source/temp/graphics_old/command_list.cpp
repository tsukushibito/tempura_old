/**
 * @file command_list.cpp
 * @brief command list
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-01
 */
#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/system/thread_pool.h"

#include "temp/graphics_old/command_list.h"
#if defined TEMP_GRAPHICS_D3D11
// #include "temp/graphics_old/d3d11/command_list_impl_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/opengl/command_list_impl_opengl.h"
#endif

namespace temp {
namespace graphics_old {

CommandList::SPtr CommandList::create() {
    struct Creator : public CommandList {
        Creator() {}
    };

    auto ptr = std::make_shared<Creator>();
    return std::move(ptr);
}

CommandList::CommandList() {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_),
                  "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(*this);
}

CommandList::~CommandList() { impl_->~Impl(); }
}
}
