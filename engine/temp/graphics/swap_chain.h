#pragma once
#include <memory>

namespace temp {
namespace graphics {

class SwapChain {
 public:
  virtual void Present() = 0;
};

using SwapChainSPtr = std::shared_ptr<SwapChain>;

}  // namespace graphics
}  // namespace temp
