/**
 * @file camera.h
 * @brief Camera class
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-08-23
 */
#pragma once
#ifndef GUARD_082c71951f804213bb68ce9b2d068884
#define GUARD_082c71951f804213bb68ce9b2d068884

#include "temp/type.h"
#include "temp/container.h"

namespace temp {
namespace render {

class Renderer;
using RendererSPtr = std::shared_ptr< Renderer >;

class Camera : public SmartPointerObject< Camera > {
public:
    explicit Camera() {}

};

} // namespace render
} // namespace temp

#endif // GUARD_082c71951f804213bb68ce9b2d068884
