/**
 * @file renderer.h
 * @brief renderer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-18
 */
#pragma once
#ifndef GUARD_0c103a63ba65427bbd196ab3610f2b5e
#define GUARD_0c103a63ba65427bbd196ab3610f2b5e

#include <mutex>
#include "temp/type.h"
#include "temp/container.h"
#include "temp/resource/vertex_shader_resource.h"
#include "temp/resource/pixel_shader_resource.h"

namespace temp {
namespace graphics_old {
class Device; 
using DeviceSPtr = std::shared_ptr<Device>;
} // namespace graphics
} // namespace temp

namespace temp {
namespace render {

class Camera;
using CameraSPtr = std::shared_ptr<Camera>;
using CameraWPtr = std::weak_ptr<Camera>;


// 仮----------------------------
class Camera : public SmartPointerObject<Camera> {
public:
    explicit Camera(const std::function<void(const Camera*)> &on_destroy) : on_destroy_(on_destroy) {}
    ~Camera(){ 
        on_destroy_(this);
    }
private:
    std::function<void(const Camera*)> on_destroy_;
};
// ----------------------------

class Renderer : public SmartPointerObject<Renderer> {
private:
    Renderer(const graphics_old::DeviceSPtr &graphics_device);

public:
    static SPtr create(const graphics_old::DeviceSPtr &graphics_device);

    CameraSPtr createCamera();

    void renderAllViews();

    void swapBackBuffers();

private:
    void removeCamera(const Camera *camera);

private:
    graphics_old::DeviceSPtr device_;
    std::mutex camera_list_mutex_;
    Vector<Camera*> camera_list_;

    resource::VertexShaderResource::SPtr clear_vs_res_;
    resource::PixelShaderResource::SPtr clear_ps_res_;
};
    
} // namespace render
} // namespace temp

#endif // GUARD_0c103a63ba65427bbd196ab3610f2b5e
