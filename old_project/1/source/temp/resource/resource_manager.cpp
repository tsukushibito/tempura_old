#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

namespace {
const Char* kResourceManagerTag = "ResourceManager";
}

ResourceManager::ResourceManager(const core::ThreadPool::SPtr& load_thread,
                                 const graphics::Device::SPtr& graphics_device,
                                 const filesystem::path& resource_root)
    : load_thread_(load_thread),
      graphics_device_(graphics_device),
      resource_root_(resource_root) {
  resource_root_ = filesystem::absolute(resource_root_);
  resource_root_ = filesystem::canonical(resource_root_);
}

ResourceManager::~ResourceManager() {
  auto size = resource_table_.size();
  TEMP_LOG_DEBUG(kResourceManagerTag,
                 fmt::format("unloaded resource count {0}", size));
}

ResourceId ResourceManager::resourceIdFromPath(const filesystem::path& path) {
  auto hash = std::hash<std::string>{}(path.string());

  auto&& path_list = hash_to_path_table_[hash];

  auto&& iter = std::find(path_list.begin(), path_list.end(), path);

  ResourceId id;
  id.hash_value = hash;
  if (iter == path_list.end()) {
    id.index = static_cast<Int32>(path_list.size());
    path_list.push_back(path);
  } else {
    id.index = std::distance(path_list.begin(), iter);
  }

  return id;
}
}  // namespace resource
}  // namespace temp
