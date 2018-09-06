#pragma once
#include <functional>
#include <mutex>
#include <utility>
#include "temp/core/core.h"

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

using ByteData = Vector<UInt8>;

class ResourceManager;

template <typename T>
class ResourcePointer : private Uncopyable {
  friend class ResourceManager;

 public:
  using UPtr = std::unique_ptr<T>;
  using SPtr = std::shared_ptr<T>;
  using WPtr = std::weak_ptr<T>;

 private:
  template <typename... Args>
  static SPtr MakeShared(Args&&... args) {
    struct Creator : public T {
      Creator(Args&&... args) : T(std::forward<Args>(args)...) {}
    };

    return std::make_shared<Creator>(std::forward<Args>(args)...);
  }
};

class ResourceBase {
 public:
  using UPtr = std::unique_ptr<ResourceBase>;
  using SPtr = std::shared_ptr<ResourceBase>;
  using WPtr = std::weak_ptr<ResourceBase>;

  ResourceBase(const std::string& type_name, const filesystem::path& path,
               ResourceManager* manager,
               std::function<void(const ResourceId&)> on_destroy);

  virtual ~ResourceBase();

  void Load(Bool is_sync = false);

  void Reload(Bool is_sync = false);

  void Save();

  const ResourceManager& manager() const { return *manager_; }

  const ResourceId& id() const { return id_; }
  const filesystem::path& path() const { return path_; }
  const ResourceState& state() const { return state_; }

 private:
  void LoadImpl(Bool is_reload);

  void ExecTaskInLoadThreadSync(std::function<void(void)> task);

  virtual ByteData Serialize() const = 0;
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
