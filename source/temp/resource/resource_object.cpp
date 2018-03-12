#include <fstream>
#include <functional>

#include "temp/resource/resource_manager.h"
#include "temp/resource/resource_object.h"

namespace temp {
namespace resource {

ResourceObject::ResourceObject(
    const filesystem::path& path, ResourceManager* manager,
    std::function<void(const ResourceId&)> on_destroy)
    : manager_(manager),
      path_(path),
      state_(ResourceState::kNotLoaded),
      on_destroy_(on_destroy) {
  id_ = manager->resourceIdFromPath(path_);
}

ResourceObject::~ResourceObject() { on_destroy_(id_); }

void ResourceObject::load(Bool is_sync) {
  if (state_ != ResourceState::kNotLoaded) return;

  auto task = [this]() { loadImpl(false); };
  if (is_sync) {
    execTaskInLoadThreadSync(task);
  } else {
    manager_->loadThread()->pushTask(0, task);
  }
}

void ResourceObject::reload(Bool is_sync) {
  auto task = [this]() { loadImpl(true); };
  if (is_sync) {
    execTaskInLoadThreadSync(task);
  } else {
    manager_->loadThread()->pushTask(0, task);
  }
}

void ResourceObject::save() {
  execTaskInLoadThreadSync([this]() {
    auto lock = std::unique_lock<std::mutex>(mutex_);
    auto byte_data = serialize();
    std::ofstream ofs(path_.string(), std::ios::binary);
    ofs.write(reinterpret_cast<char*>(&byte_data[0]), byte_data.size());
  });
}

void ResourceObject::loadImpl(Bool is_reload) {
  auto lock = std::unique_lock<std::mutex>(mutex_);

  state_ = ResourceState::kLoading;

  if (!filesystem::exists(path_)) {
    state_ = ResourceState::kNotExists;
    return;
  }

  std::ifstream ifs(path_.string());

  std::istreambuf_iterator<char> beg(ifs);
  std::istreambuf_iterator<char> end;

  ByteData byte_data(beg, end);

  deserialize(byte_data);
}

void ResourceObject::execTaskInLoadThreadSync(std::function<void(void)> task) {
  Bool is_load_thread = false;

  auto&& this_thread_id = std::this_thread::get_id();
  auto&& load_thread_id = manager_->loadThread()->threadId(0);
  if (this_thread_id == load_thread_id) {
    is_load_thread = true;
  }

  if (is_load_thread) {
    task();
  } else {
    auto&& future = manager_->loadThread()->pushTask(0, task);
    future.wait();
  }
}
}  // namespace resource
}  // namespace temp
