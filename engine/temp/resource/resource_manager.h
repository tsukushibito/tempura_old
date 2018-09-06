#pragma once
#include <mutex>
#include <unordered_map>
#include <vector>

#include "temp/core/core.h"
#include "temp/resource/resource_base.h"

namespace temp {
namespace graphics {
class Device;
using DeviceSPtr = std::shared_ptr<Device>;
}  // namespace graphics
}  // namespace temp

namespace temp {
namespace resource {
class ResourceManager : public temp::SmartPointerType<ResourceManager> {
 public:
  ResourceManager(const filesystem::path& resource_root,
                  const TaskManager::SPtr& task_manager,
                  const graphics::DeviceSPtr& graphics_device);

  ~ResourceManager();

  ResourceId ResourceIdFromTypeNameAndPath(const std::string& type_name,
                                           const filesystem::path& path);

  template <typename T>
  std::shared_ptr<T> Create(const filesystem::path& path);

  template <typename T>
  std::shared_ptr<T> CreateAndLoad(const filesystem::path& path);

  const filesystem::path& resource_root() const { return resource_root_; }
  TaskManager::SPtr task_manager() const { return task_manager_; }
  graphics::DeviceSPtr graphics_device() const { return graphics_device_; }

 private:
  filesystem::path resource_root_;
  TaskManager::SPtr task_manager_;
  graphics::DeviceSPtr graphics_device_;

  std::unordered_map<Size, std::vector<filesystem::path>> hash_to_path_table_;

  std::mutex resource_table_mutex_;
  std::unordered_map<ResourceId, ResourceBase::WPtr, ResourceIdHash>
      resource_table_;
};

template <typename T>
std::shared_ptr<T> ResourceManager::Create(const filesystem::path& path) {
  std::unique_lock<std::mutex> lock(resource_table_mutex_);

  auto id = ResourceIdFromTypeNameAndPath(T::type_name(), path);
  auto iter = resource_table_.find(id);

  if (iter != resource_table_.end()) {
    auto res = iter->second.lock();
    TEMP_ASSERT(res != nullptr, "res must not be nullptr");
    TEMP_ASSERT(std::dynamic_pointer_cast<T>(res) != nullptr,
                "Type of res must be T");
    res->Load();

    return std::static_pointer_cast<T>(res);

  } else {
    auto remove_from_table = [this](const ResourceId id) {
      std::unique_lock<std::mutex> lock(resource_table_mutex_);
      auto iter = resource_table_.find(id);
      TEMP_ASSERT(iter != resource_table_.end(), "");
      if (iter == resource_table_.end()) return;
      resource_table_.erase(id);
    };

    auto res = T::MakeShared(path, this, remove_from_table);
    resource_table_[id] = res;

    return std::static_pointer_cast<T>(res);
  }
}

template <typename T>
std::shared_ptr<T> ResourceManager::CreateAndLoad(
    const filesystem::path& path) {
  auto res = Create<T>(path);
  res->Load();
  return res;
}

}  // namespace resource
}  // namespace temp
