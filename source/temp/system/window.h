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

namespace temp {
namespace system {

class Window;
using WindowHandle = temp::Handle<Window>;

class Window : public SmartPointerObject<Window> {
private:
    Window(Size width = 1280, Size height = 720);

public:
    ~Window();

public:
    static SPtr create(Size width = 1280, Size height = 720);

    WindowHandle windowHandle() const { return handle_; }
    Size         width() const { return width_; }
    Size         height() const { return height_; }

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

    WindowHandle handle_;
    Size         width_;
    Size         height_;
};

}
}

#endif  // GUARD_7436746b1e0349869c4b963feb8fcded
