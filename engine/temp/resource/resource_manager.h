#pragma once
#include <mutex>

#include "temp/core/core.h"
#include "temp/resource/resource_base.h"

namespace temp {
namespace resource {
class ResourceManager : public temp::SmartPointerType<ResourceManager> {
 public:
  ResourceManager(const TaskManager::SPtr& task_manager,
                  const filesystem::path& resource_root);

  ~ResourceManager();

  ResourceId ResourceIdFromPath(const filesystem::path& path);

  template <typename T>
  std::shared_ptr<T> Create(const filesystem::path& path);

  template <typename T>
  std::shared_ptr<T> CreateAndLoad(const filesystem::path& path);

  auto task_manager() -> TaskManager::SPtr const { return task_manager_; }
  auto resource_root() -> filesystem::path const { return resource_root_; }

 private:
  TaskManager::SPtr task_manager_;
  filesystem::path resource_root_;

  HashTable<Size, Vector<filesystem::path>> hash_to_path_table_;

  std::mutex resource_table_mutex_;
  HashTable<ResourceId, ResourceBase::WPtr, ResourceIdHash> resource_table_;
};

template <typename T>
std::shared_ptr<T> ResourceManager::Create(const filesystem::path& path) {
  std::unique_lock<std::mutex> lock(resource_table_mutex_);

  auto id = ResourceIdFromPath(path);
  auto iter = resource_table_.find(id);

  if (iter != resource_table_.end()) {
    auto res = iter->second.lock();
    TEMP_ASSERT(res != nullptr, "");
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

    auto res = T::makeShared(path, this, remove_from_table);
    resource_table_[id] = res;

    return std::static_pointer_cast<T>(res);
  }
}

template <typename T>
std::shared_ptr<T> ResourceManager::CreateAndLoad(
    const filesystem::path& path) {
  auto res = Create<T>(path);
  res->load();
  return res;
}

}  // namespace resource
}  // namespace temp
