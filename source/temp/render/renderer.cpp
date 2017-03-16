#include <functional>
#include "temp/temp_assert.h"
#include "temp/graphics/device.h"
#include "temp/render/renderer.h"

namespace temp {
namespace render {

Renderer::Renderer(const graphics_old::DeviceSPtr &graphics_device) : device_(graphics_device) {
    clear_vs_res_ = resource::VertexShaderResource::create("shader/glsl/clear_glsl.vert");
    clear_vs_res_->load();
    clear_ps_res_ = resource::PixelShaderResource::create("shader/glsl/clear_glsl.frag");
    clear_ps_res_->load();
}

Renderer::SPtr Renderer::create(const graphics_old::DeviceSPtr &graphics_device) {
    struct Creator : public Renderer {
        Creator(const graphics_old::DeviceSPtr &graphics_device)
            : Renderer(graphics_device) {
        }
    };

    auto ptr = std::make_shared<Creator>(graphics_device);
    return std::move(ptr);
}

CameraSPtr Renderer::createCamera() {
    // リストから削除するファンクタをコンストラクタに渡してカメラを作成
    auto ptr = std::make_shared<Camera>(std::bind(&Renderer::removeCamera, this, std::placeholders::_1));

    {
        // リストに追加
        std::lock_guard<std::mutex> lock(camera_list_mutex_);
        camera_list_.push_back(ptr.get());
    }

    return ptr;
}

void Renderer::renderAllViews() {
}

void Renderer::swapBackBuffers() {
    device_->present();
}

void Renderer::removeCamera(const Camera *camera) {
    std::lock_guard<std::mutex> lock(camera_list_mutex_);

    // リストから削除
    auto new_end = std::remove_if(camera_list_.begin(), camera_list_.end(), 
        [&camera](Camera *ptr){ return ptr == camera; });
    TEMP_ASSERT(new_end != camera_list_.end(), ""); // 必ず削除されるべきカメラがあるはず
    camera_list_.erase(new_end, camera_list_.end());    // 削除処理
}

}
}
