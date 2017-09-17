/**
 * @file render_target.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-23
 */
#pragma once
#ifndef GUARD_023ee56626c24b119cbaac3b5fb02780
#define GUARD_023ee56626c24b119cbaac3b5fb02780

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

template <typename T, typename NativeHandle>
class RenderTargetBase : public SmartPointerObject<T> {
protected:
    RenderTargetBase(NativeHandle native_handle, const RenderTargetDesc& desc,
                     const std::function<void(NativeHandle)> on_destroy)
        : native_handle_(native_handle)
        , description_(desc)
        , on_destroy_(on_destroy) {}

public:
    ~RenderTargetBase() { on_destroy_(native_handle_); }

    NativeHandle            nativeHandle() const { return native_handle_; }
    const RenderTargetDesc& description() const { return description_; }

private:
    T* derived() { return static_cast<T*>(this); }

protected:
    NativeHandle                      native_handle_;
    RenderTargetDesc                  description_;
    std::function<void(NativeHandle)> on_destroy_;
};
}
}

#endif  // GUARD_023ee56626c24b119cbaac3b5fb02780
