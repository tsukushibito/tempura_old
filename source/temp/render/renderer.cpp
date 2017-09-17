#include "temp/render/renderer.h"

#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/render/opengl/opengl_renderer.h"
#endif

namespace temp {
namespace render {

Renderer::Renderer(const ThreadPoolSPtr&     command_thread,
                   const ThreadPoolSPtr&     render_thread,
                   const GraphicsDeviceSPtr& device,
                   const DrawAreaSize&       draw_area_size,
                   const Path&               shader_directory)
    : command_thread_(command_thread)
    , render_thread_(render_thread)
    , graphics_device_(device)
    , draw_area_size_(draw_area_size)
    , shader_directory_(shader_directory) {
    impl_.reset(new Impl(*this));
}

Renderer::~Renderer() {}

Renderer::RenderTargetSPtr Renderer::createRenderTarget(
    const RenderTargetDesc& desc) {
    return impl_->createRenderTarget(desc);
}

Camera::SPtr Renderer::createCamera() {
    struct Creator : public Camera {
        Creator(std::function<void(Camera*)> on_destroy) : Camera(on_destroy) {}
    };

    Camera::SPtr camera = std::make_shared<Creator>([this](Camera* camera) {
        impl_->onCameraDestory(camera);
        std::unique_lock<std::mutex> lock(camera_list_mutex_);
        auto                         new_end
            = std::remove_if(camera_list_.begin(), camera_list_.end(),
                             [camera](Camera* elem) { return elem == camera; });
        camera_list_.erase(new_end, camera_list_.end());
    });

    {
        std::unique_lock<std::mutex> lock(camera_list_mutex_);
        camera_list_.push_back(camera.get());
    }

    return camera;
}

void Renderer::setMainCamera(const Camera::SPtr& camera) {
    main_camera_ = camera;
}

void Renderer::render() { impl_->render(); }

}
}
