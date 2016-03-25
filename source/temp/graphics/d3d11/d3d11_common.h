/**
 * @file d3d11_common.h
 * @brief D3D11共通
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-25
 */
#pragma once
#ifndef GUARD_a3b226fa524a44aa93e7c88477086311
#define GUARD_a3b226fa524a44aa93e7c88477086311

#include "temp/define.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <memory>
#include <Windows.h>

namespace temp {
namespace graphics {
namespace d3d11 {

struct ComDeleter {
    void operator()(IUnknown *com){
        com->Release();
    }
};

template < typename T >
class com_unique_ptr : public std::unique_ptr < T, ComDeleter > {
public:
    com_unique_ptr()
        : unique_ptr(nullptr) {}
    com_unique_ptr(T * p) : unique_ptr(p) {}
    T **get_pp() {
        buf_ = get();
        return &buf_;
    }
    void reset(T * com) { unique_ptr::reset(com); }

private:
    T *buf_;
};

} // namespace d3d11
} // namespace graphics
} // namespace temp

#endif

#endif // GUARD_a3b226fa524a44aa93e7c88477086311
