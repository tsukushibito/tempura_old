#pragma once
#include <functional>
#include <utility>
#include "temp/core/type.h"
#include "temp/core/container.h"
#include "temp/core/filesystem.h"

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
    return id.hash_value;
  }
};

using ByteData = Vector<Int8>;

class ResourceManager;

class ResourceBase {
 public:
  using UPtr = std::unique_ptr<ResourceBase>;
  using SPtr = std::shared_ptr<ResourceBase>;
  using WPtr = std::weak_ptr<ResourceBase>;

  ResourceBase(const filesystem::path& path, ResourceManager* manager,
               std::function<void(const ResourceId&)> on_destroy);

  virtual ~ResourceBase();

  void Load(Bool is_sync = false);

  void Reload(Bool is_sync = false);

  void Save();

  auto manager() -> ResourceManager* const { return manager_; }

  auto id() -> ResourceId const { return id_; }
  auto path() -> filesystem::path const { return path_; }
  auto state() -> ResourceState const { return state_; }

 private:
  void LoadImpl(Bool is_reload);

  void ExecTaskInLoadThreadSync(std::function<void(void)> task);

  virtual ByteData Serialize() = 0;
  virtual void Deserialize(const ByteData&) = 0;

 private:
  std::mutex mutex_;
  ResourceManager* manager_;
  ResourceId id_;
  filesystem::path path_;
  ResourceState state_;
  std::function<void(const ResourceId&)> on_destroy_;
};
}  // namespace resource
}  // namespace temp
