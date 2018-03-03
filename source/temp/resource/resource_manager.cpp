#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

ResourceManager::ResourceManager(const core::ThreadPool::SPtr& load_thread,
                                 const graphics::Device::SPtr& graphics_device)
    : load_thread_(load_thread), graphics_device_(graphics_device) {}

ResourceId ResourceManager::resourceIdFromPath(const filesystem::path& path) {
  auto hash = std::hash<std::string>{}(path.string());

  auto&& id_list = resource_id_table_[hash];

  ResourceId id;
  id.hash_value = hash;
  id.index = id_list.size();
  id_list.push_back(id);

  return id;
}
}  // namespace resource
}  // namespace temp