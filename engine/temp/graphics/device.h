#pragma once
#include <memory>

namespace temp {
namespace graphics {

enum class GraphicsApi {
  kVulkan,
  kOpenGl,
  kD3d12,
  kD3d11,
};

class SwapChain;
using SwapChainSPtr = std::shared_ptr<SwapChain>;

class Device {
 public:
  Device() {}

  virtual ~Device() = default;

  virtual SwapChainSPtr CreateSwapChain(const void* window) = 0;
};

using DeviceSPtr = std::shared_ptr<Device>;

DeviceSPtr CreateDevice(GraphicsApi api);

}  // namespace graphics
}  // namespace temp
