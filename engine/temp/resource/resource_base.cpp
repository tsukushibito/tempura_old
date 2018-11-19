
#include <fstream>
#include <functional>

#include "temp/resource/resource_base.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

ResourceBase::ResourceBase(const std::string& type_name,
                           const filesystem::path& path,
                           ResourceManager* manager,
                           std::function<void(const ResourceId&)> on_destroy)
    : manager_(manager),
      path_(path),
      state_(ResourceState::kNotLoaded),
      on_destroy_(on_destroy) {
  id_ = manager->ResourceIdFromTypeNameAndPath(type_name, path_);
}

ResourceBase::~ResourceBase() { on_destroy_(id_); }

void ResourceBase::Load(bool is_sync) {
  if (state_ != ResourceState::kNotLoaded) return;

  auto task = [this]() { LoadImpl(false); };
  if (is_sync) {
    ExecTaskInLoadThreadSync(task);
  } else {
    manager_->task_manager()->PushTask(task);
  }
}

void ResourceBase::Reload(bool is_sync) {
  auto task = [this]() { LoadImpl(true); };
  if (is_sync) {
    ExecTaskInLoadThreadSync(task);
  } else {
    manager_->task_manager()->PushTask(task);
  }
}

void ResourceBase::Save() {
  ExecTaskInLoadThreadSync([this]() {
    auto lock = std::unique_lock<std::mutex>(mutex_);
    auto byte_data = Serialize();
    auto full_path = manager_->resource_root() / path_;
    std::ofstream ofs(full_path.string(), std::ios::binary);
    ofs.write(reinterpret_cast<char*>(&byte_data[0]), byte_data.size());
  });
}

void ResourceBase::LoadImpl(bool is_reload) {
  auto lock = std::unique_lock<std::mutex>(mutex_);

  state_ = ResourceState::kLoading;

  auto full_path = manager_->resource_root() / path_;
  if (!filesystem::exists(full_path)) {
    state_ = ResourceState::kNotExists;
    return;
  }

  std::ifstream ifs(full_path.string());

  std::istreambuf_iterator<char> beg(ifs);
  std::istreambuf_iterator<char> end;

  ByteData byte_data(beg, end);

  Deserialize(byte_data);

  state_ = ResourceState::kLoaded;
}

void ResourceBase::ExecTaskInLoadThreadSync(std::function<void(void)> task) {
  auto is_load_thread = false;

  auto&& this_thread_id = std::this_thread::get_id();
  auto&& load_thread_id = manager_->task_manager()->thread_id(0);
  if (this_thread_id == load_thread_id) {
    is_load_thread = true;
  }

  if (is_load_thread) {
    task();
  } else {
    auto&& future = manager_->task_manager()->PushTask(task);
    future.wait();
  }
}
}  // namespace resource
}  // namespace temp
