#pragma once
#include <mutex>

#include "temp/common/common.h"
#include "temp/core/core.h"
#include "temp/graphics/graphics.h"
#include "temp/resource/resource_object.h"

namespace temp {
namespace resource {
class ResourceManager : public temp::SmartPointerObject<ResourceManager> {
 public:
  ResourceManager(const core::ThreadPool::SPtr& load_thread,
                  const graphics::Device::SPtr& graphics_device);

  ResourceId resourceIdFromPath(const filesystem::path& path);

  template <typename T>
  std::shared_ptr<T> createAndLoad(const filesystem::path& path);

  auto loadThread() -> core::ThreadPool::SPtr const { return load_thread_; }
  auto graphicsDevice() -> graphics::Device::SPtr const {
    return graphics_device_;
  }

 private:
  core::ThreadPool::SPtr load_thread_;
  graphics::Device::SPtr graphics_device_;

  HashTable<Size, Vector<ResourceId>> resource_id_table_;

  std::mutex resource_table_mutex_;
  HashTable<ResourceId, ResourceObject::WPtr, ResourceIdHash> resource_table_;
};

template <typename T>
std::shared_ptr<T> ResourceManager::createAndLoad(
    const filesystem::path& path) {
  std::unique_lock<std::mutex> lock(resource_table_mutex_);

  auto id = resourceIdFromPath(path);
  auto iter = resource_table_.find(id);

  if (iter != resource_table_.end()) {
    auto res = iter->second.lock();
    TEMP_ASSERT(res != null, "");
    res->load();

    return res;

  } else {
    auto remove_from_table = [this](const ResourceId id) {
      std::unique_lock<std::mutex> lock(resource_table_mutex_);
      auto iter = resource_table_.find(id);
      TEMP_ASSERT(iter != resource_table_.end(), "");
      auto res = iter->second.lock();
      if (res.use_count() == 1) {
        resource_table_.erase(id);
      }
    };

    auto res =
        T::makeShared(path, load_thread_, graphics_device_, remove_from_table);
    res->load();

    return res;
  }
}

}  // namespace resource
}  // namespace temp