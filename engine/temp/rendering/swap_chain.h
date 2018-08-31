#pragma once
#include <memory>

namespace temp {
namespace rendering {

class Renderer;

class SwapChain {
 public:
  virtual void Present() = 0;
};

using SwapChainSPtr = std::shared_ptr<SwapChain>;

}  // namespace rendering
}  // namespace temp
