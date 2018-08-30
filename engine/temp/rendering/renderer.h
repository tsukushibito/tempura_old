#pragma once
#include "temp/core/core.h"

namespace temp {

class TaskManager;

namespace resource {

class ResourceManager;
}

namespace rendering {

class SwapChain;

class Renderer : public SmartPointerType<Renderer> {
  friend class SmartPointerType<Renderer>;
  using TaskManagerSPtr = std::shared_ptr<TaskManager>;
  using ResourceManagerSPtr = std::shared_ptr<resource::ResourceManager>;

 private:
  Renderer(const TaskManagerSPtr& task_manager,
           const ResourceManagerSPtr& resource_manager);

 public:
  ~Renderer();

 public:
  void Render();

 private:
  class Impl;
  static const Size kImplSize = 1024 * 2 + 512;
  static const Size kImplAlignment = std::alignment_of<std::max_align_t>::value;
  using ImplStorage = std::aligned_storage<kImplSize, kImplAlignment>::type;
  ImplStorage impl_strage_;
  Impl* impl_;

  TaskManagerSPtr task_manager_;
  ResourceManagerSPtr resource_manager_;
};
}  // namespace rendering
}  // namespace temp
