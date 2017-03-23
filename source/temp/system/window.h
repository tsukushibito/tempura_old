/**
 * @file window.h
 * @brief window class
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-21
 */
#pragma once
#ifndef GUARD_7436746b1e0349869c4b963feb8fcded
#define GUARD_7436746b1e0349869c4b963feb8fcded

#include "temp/type.h"
#include "temp/define.h"
#if defined(TEMP_PLATFORM_WINDOWS)
#include <Windows.h>
#endif

namespace temp {
namespace system {

class Window : public SmartPointerObject<Window> {
    friend SmartPointerObject<Window>;
public:
#if defined(TEMP_PLATFORM_MAC)
	using NativeHandle = void*;
#elif defined(TEMP_PLATFORM_WINDOWS)
	using NativeHandle = HWND;
#endif

private:
    Window(Size width = 1280, Size height = 720);

public:
    ~Window();

public:
	NativeHandle nativeHandle() const;

    Size         width() const { return width_; }
    Size         height() const { return height_; }

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

    Size width_;
    Size height_;
};
}
}

#endif  // GUARD_7436746b1e0349869c4b963feb8fcded
