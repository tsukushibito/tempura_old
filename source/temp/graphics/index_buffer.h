/**
 * @file index_buffer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-26
 */
#pragma once
#ifndef GUARD_afea9b7b65864af8986474830ef5aa51
#define GUARD_afea9b7b65864af8986474830ef5aa51
#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

template <typename T, typename NativeHandle>
class IndexBufferBase : public SmartPointerObject<T> {
    friend Device;

protected:
    IndexBufferBase(NativeHandle native_handle, const ByteData& data,
                    const std::function<void(NativeHandle)> on_destroy)
        : native_handle_(native_handle), data_(data), on_destroy_(on_destroy) {}

public:
    ~IndexBufferBase() { on_destroy_(native_handle_); }

    NativeHandle    nativeHandle() const { return native_handle_; }
    const ByteData& data() const { return data_; }

private:
    NativeHandle                      native_handle_;
    ByteData                          data_;
    std::function<void(NativeHandle)> on_destroy_;
};
}
}
#endif  // GUARD_afea9b7b65864af8986474830ef5aa51
