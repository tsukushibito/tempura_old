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

union WindowHandle {
    void* pointer_;
    Size  value_;
};

class Window : public SmartPointerObject<Window> {
private:
    Window(Size width = 1280, Size height = 720);

public:
    ~Window();

public:
    static SPtr create(Size width = 1280, Size height = 720);

    WindowHandle getWindowHandle() const;
    Size         getWidth() const { return width_; }
    Size         getHeight() const { return height_; }

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

    Size width_;
    Size height_;
};
}
}

#endif  // GUARD_7436746b1e0349869c4b963feb8fcded
