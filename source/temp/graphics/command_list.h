/**
 * @file command_list.h
 * @brief command list
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-01
 */
#pragma once
#ifndef GUARD_ddb195f6591a469189350d1a8a9e8daf
#define GUARD_ddb195f6591a469189350d1a8a9e8daf

#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class CommandList : public SmartPointerObject< CommandList >, public FastPImpl {
    friend class Device;

private:
    static SPtr create();

    CommandList();

public:
    ~CommandList();

    const NativeHandle &getNativehandle() const { return native_handle_; }

private:
    class Impl;
    Impl *impl_;

    NativeHandle native_handle_;
};
}
}

#endif // GUARD_ddb195f6591a469189350d1a8a9e8daf
