#include <functional>
#include "temp/temp_assert.h"
#include "temp/render/renderer.h"

namespace temp {
namespace render {

Renderer::Renderer(const graphics::DeviceSPtr &graphics_device) : device_(graphics_device) {
}

Renderer::SPtr Renderer::create(const graphics::DeviceSPtr &graphics_device) {
	struct Creator : public Renderer {
		Creator(const graphics::DeviceSPtr &graphics_device) 
			: Renderer(graphics_device) {
		}
	};

	auto ptr = std::make_shared<Creator>(graphics_device);
	return std::move(ptr);
}

CameraSPtr Renderer::createCamera() {
	std::lock_guard<std::mutex> lock(camera_list_mutex_);
	auto ptr = std::make_shared<Camera>(std::bind(&Renderer::removeCamera, this, std::placeholders::_1));
	camera_list_.push_back(ptr);
	return ptr;
}

void Renderer::removeCamera(const Camera *camera) {
	std::lock_guard<std::mutex> lock(camera_list_mutex_);
	auto new_end = std::remove_if(camera_list_.begin(), camera_list_.end(), 
		[&camera](CameraWPtr wptr){ return (wptr.lock().get() == nullptr) || (wptr.lock().get() == camera); });
	TEMP_ASSERT(new_end != camera_list_.end());
	auto top = camera_list_[0].lock().get();
	auto end = (*new_end).lock().get();
	camera_list_.erase(new_end, camera_list_.end());
}

}
}