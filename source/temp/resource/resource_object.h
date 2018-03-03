#pragma once
#include <functional>
#include <utility>
#include "temp/common/common.h"
#include "temp/core/filesystem.h"
#include "temp/core/thread_pool.h"
#include "temp/graphics/device.h"

namespace temp {
namespace resource {

enum class ResourceState {
  kNotLoaded,
  kLoading,
  kLoaded,
  kNotExists,
};

struct ResourceId {
  Size hash_value;
  Int32 index;
};

inline bool operator==(const ResourceId& lhs, const ResourceId& rhs) {
  return lhs.hash_value == rhs.hash_value && lhs.index == rhs.index;
}

inline bool operator!=(const ResourceId& lhs, const ResourceId& rhs) {
  return !(lhs == rhs);
}

struct ResourceIdHash {
  using result_type = Size;

  inline result_type operator()(const ResourceId& id) const {
    auto h1 = id.hash_value;
    auto h2 = std::hash<int>{}(id.index);
    return h1 ^ (h2 << 1);
  }
};

using ByteData = Vector<Int8>;

class ResourceManager;

class ResourceObject {
 public:
  using UPtr = std::unique_ptr<ResourceObject>;
  using SPtr = std::shared_ptr<ResourceObject>;
  using WPtr = std::weak_ptr<ResourceObject>;

  ResourceObject(const filesystem::path& path, ResourceManager* manager,
                 std::function<void(void)> on_destroy);

  virtual ~ResourceObject();

  void load(Bool is_sync = false);

  void reload(Bool is_sync = false);

  auto manager() -> ResourceManager* const { return manager_; }

  auto id() -> ResourceId const { return id_; }
  auto path() -> filesystem::path const { return path_; }
  auto state() -> ResourceState const { return state_; }

 private:
  void loadImpl(Bool is_reload);

  void execTaskInLoadThreadSync(std::function<void(void)> task);

  virtual void prepare(const ByteData& byte_data) = 0;

 private:
  std::mutex mutex_;
  ResourceManager* manager_;
  ResourceId id_;
  filesystem::path path_;
  ResourceState state_;
  std::function<void(void)> on_destroy_;
};
}  // namespace resource
}  // namespace temp
