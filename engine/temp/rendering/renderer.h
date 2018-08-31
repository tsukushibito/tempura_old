#pragma once
#include <memory>

namespace temp {
class TaskManager;
}

namespace temp {
namespace resource {
class ResourceManager;
}
}  // namespace temp

namespace temp {
namespace rendering {

enum class GraphicsApi {
  kVulkan,
  kOpenGl,
  kD3d12,
  kD3d11,
};

using TaskManagerSPtr = std::shared_ptr<TaskManager>;
using ResourceManagerSPtr = std::shared_ptr<resource::ResourceManager>;

class SwapChain;
using SwapChainSPtr = std::shared_ptr<SwapChain>;

class Renderer {
 public:
  Renderer(const TaskManagerSPtr& task_manager,
           const ResourceManagerSPtr& resource_manager)
      : task_manager_(task_manager), resource_manager_(resource_manager) {}

  virtual ~Renderer() = default;

  virtual SwapChainSPtr CreateSwapChain(const void* window) = 0;

  virtual void Render() = 0;

 protected:
  TaskManagerSPtr task_manager_;
  ResourceManagerSPtr resource_manager_;
};

using RendererSPtr = std::shared_ptr<Renderer>;

RendererSPtr CreateRenderer(GraphicsApi api,
                            const TaskManagerSPtr& task_manager,
                            const ResourceManagerSPtr& resource_manager);

}  // namespace rendering
}  // namespace temp
