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
        static_cast<graphics::WindowHandle>(window_handle), render_thread_,
        load_thread_);
#else
#endif
    resource_manager_ =
        resource::ResourceManager::makeShared(load_thread_, graphics_device_);

    TEMP_LOG_INFO("Tempra", filesystem::current_path().string());

    auto mesh = resource_manager_->create<resource::Mesh>("test.tmsh");
    mesh->load(true);
#if 0
    auto graphics_device = engine->graphicsDevice();
    Float32 vertices[] = {
        -1.0f, -1.0f, -1.0f, 0.0f,  //
        0.0f,  0.0f,  -1.0f, 0.0f,  //
        -1.0f, 1.0f,  -1.0f, 0.0f,  //
        0.0f,  0.0f,  -1.0f, 0.0f,  //
        1.0f,  -1.0f, -1.0f, 0.0f,  //
        0.0f,  0.0f,  -1.0f, 0.0f,  //
        1.0f,  1.0f,  -1.0f, 0.0f,  //
        0.0f,  0.0f,  -1.0f, 0.0f,  //

        1.0f,  -1.0f, -1.0f, 0.0f,  //
        1.0f,  0.0f,  0.0f,  0.0f,  //
        1.0f,  1.0f,  -1.0f, 0.0f,  //
        1.0f,  0.0f,  0.0f,  0.0f,  //
        1.0f,  -1.0f, 1.0f,  0.0f,  //
        1.0f,  0.0f,  0.0f,  0.0f,  //
        1.0f,  1.0f,  1.0f,  0.0f,  //
        1.0f,  0.0f,  0.0f,  0.0f,  //

        1.0f,  -1.0f, 1.0f,  0.0f,  //
        0.0f,  0.0f,  1.0f,  0.0f,  //
        1.0f,  1.0f,  1.0f,  0.0f,  //
        0.0f,  0.0f,  1.0f,  0.0f,  //
        -1.0f, -1.0f, 1.0f,  0.0f,  //
        0.0f,  0.0f,  1.0f,  0.0f,  //
        -1.0f, 1.0f,  1.0f,  0.0f,  //
        0.0f,  0.0f,  1.0f,  0.0f,  //

        -1.0f, -1.0f, 1.0f,  0.0f,  //
        -1.0f, 0.0f,  0.0f,  0.0f,  //
        -1.0f, 1.0f,  1.0f,  0.0f,  //
        -1.0f, 0.0f,  0.0f,  0.0f,  //
        -1.0f, -1.0f, -1.0f, 0.0f,  //
        -1.0f, 0.0f,  0.0f,  0.0f,  //
        -1.0f, 1.0f,  -1.0f, 0.0f,  //
        -1.0f, 0.0f,  0.0f,  0.0f,  //
    };
    graphics::VertexBufferDesc vb_desc;
    vb_desc.element_count = 2;
    vb_desc.element_descs[0].format = graphics::VertexFormat::kFloat32x4;
    vb_desc.element_descs[0].attribute = graphics::VertexAttribute::kPosition;
    vb_desc.element_descs[1].format = graphics::VertexFormat::kFloat32x4;
    vb_desc.element_descs[1].attribute = graphics::VertexAttribute::kNormal;
    vb_desc.size = sizeof(vertices);
    auto vb = graphics_device->createVertexBuffer(vb_desc, vertices);
    mesh->replaceVertexBuffer(vb);
    Float32 indices[] = {
        0, 1, 2, 3,  //
        3, 2,        //
        2, 3, 4, 5,  //
        5, 4,        //
        4, 5, 6, 7,  //
        7, 6,        //
        6, 7, 0, 1,  //
    };
    graphics::IndexBufferDesc ib_desc;
    ib_desc.format = graphics::IndexBufferFormat::kUInt16;
    ib_desc.primitive_type = graphics::PrimitiveType::kTriangleStrip;
    ib_desc.size = sizeof(indices);
    auto ib = graphics_device->createIndexBuffer(ib_desc, indices);
    mesh->replaceIndexBuffer(ib);
    mesh->save();
#endif
  }
  void update(){/*core::Logger::trace("Tempura", "update");*/};

  graphics::Device::SPtr graphicsDevice() { return graphics_device_; }

  resource::ResourceManager::SPtr resourceManager() {
    return resource_manager_;
  }

 private:
  core::ThreadPool::SPtr render_thread_;
  core::ThreadPool::SPtr load_thread_;
  graphics::Device::SPtr graphics_device_;
  resource::ResourceManager::SPtr resource_manager_;
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
