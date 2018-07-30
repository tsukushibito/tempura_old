/**
 * @file texture.h
 * @brief テクスチャGPUリソース
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-17
 */
#pragma once
#ifndef GUARD_70686145556f45efb5ba565866b86464
#define GUARD_70686145556f45efb5ba565866b86464

#include "temp/graphics_/graphics_common.h"

namespace temp {
namespace graphics_ {

template <typename T, typename NativeHandle>
class TextureBase : public SmartPointerObject<T> {
protected:
    TextureBase(NativeHandle native_handle, const TextureDesc& desc,
                const std::function<void(NativeHandle)> on_destroy)
        : native_handle_(native_handle)
        , description_(desc)
        , on_destroy_(on_destroy) {}

public:
    ~TextureBase() { on_destroy_(native_handle_); }

    NativeHandle       nativeHandle() const { return native_handle_; }
    const TextureDesc& description() const { return description_; }

private:
    T* derived() { return static_cast<T*>(this); }

protected:
    NativeHandle                      native_handle_;
    TextureDesc                       description_;
    std::function<void(NativeHandle)> on_destroy_;
};
}
}

#endif  // GUARD_70686145556f45efb5ba565866b86464
