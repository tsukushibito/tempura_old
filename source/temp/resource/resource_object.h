#pragma once
#include <utility>
#include "temp/common/common.h"
#include "temp/core/filesystem.h"
#include "temp/core/thread_pool.h"

namespace temp {
namespace resource {

enum class ResourceState {
  kNotLoaded,
  kLoading,
  kLoaded,
  kNotExists,
};

struct ResourceId {
  Size hash_value_;
  Int32 index_;
}

using ByteData = Vector<Int8>;

class ResourceObject {
 public:
  using UPtr = std::unique_ptr<ResourceBase>;
  using SPtr = std::shared_ptr<ResourceBase>;
  using WPtr = std::weak_ptr<ResourceBase>;

  ResourceObject(const filesystem::path& path,
                 const core::ThreadPool::SPtr& load_thread,
                 std::function<void(void)> on_destroy);

  virtual ~ResourceBase();

  void load(Bool is_sync = false);

  void reload(Bool is_sync = false);

 private:
  void loadImpl(Bool is_reload);

  void execTaskInLoadThreadSync(std::function<void(void)> task);

  virtual void prepare(const ByteData& byte_data) = 0;

 private:
  std::mutex mutex_;
  core::ThreadPool::SPtr load_thread_;
  ResourceState state_;
  ResourceId id_;
  filesystem::path path_;
  std::function<void(void)> on_destroy_;
};
}  // namespace resource
}  // namespace temp
