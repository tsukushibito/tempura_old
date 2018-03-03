#include <memory>
#define TEMP_EXPORT
#include "temp.h"
#if defined(TEMP_PLATFORM_WINDOWS)
#include "temp/app/windows/windows_application.h"
#elif defined(TEMP_PLATFORM_MAC)
#include "temp/app/mac/mac_application.h"
#endif
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/opengl_device.h"
#else
#endif

namespace temp {

class TempuraImpl : public Tempura {
 public:
  TempuraImpl(void* window_handle) {
    render_thread_ = core::ThreadPool::makeShared("Render", 1);
    load_thread_ = core::ThreadPool::makeShared("Load", 1);
#ifdef TEMP_GRAPHICS_OPENGL
    graphics_device_ = graphics::opengl::OpenGLDevice::create(
        window_handle, render_thread_, load_thread_);
#else
#endif
    renderer_ =
        renderer::Renderer::makeShared(render_thread_, graphics_device_);
    math::Vector2 vec1, vec2(1.0f, 1.0f);
    auto d = math::dot(vec1, vec2);
  }
  void update(){/*core::Logger::trace("Tempura", "update");*/};

 private:
  core::ThreadPool::SPtr render_thread_;
  core::ThreadPool::SPtr load_thread_;
  graphics::Device::SPtr graphics_device_;
  renderer::Renderer::SPtr renderer_;
};

TEMP_DECLSPEC TempSPtr create(void* window_handle) {
  return std::make_shared<TempuraImpl>(window_handle);
}

TEMP_DECLSPEC temp::app::ApplicationSPtr createApplication() {
#if defined(TEMP_PLATFORM_WINDOWS)
  return std::make_shared<temp::app::windows::WindowsApplication>();
#elif defined(TEMP_PLATFORM_MAC)
  return std::make_shared<temp::app::mac::MacApplication>();
#endif
}
}  // namespace temp
