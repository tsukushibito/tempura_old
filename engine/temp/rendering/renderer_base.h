#pragma once
#include "temp/rendering/swap_chain_base.h"

namespace temp {
namespace rendering {

template <typename T>
using SwapChainSPtr = std::shared_ptr<SwapChainBase<T>>;

template <typename T>
class RendererBase : public SmartPointerType<T> {
 protected:
  RendererBase() = default;

 public:
  void Render() { static_cast<T*>(this)->Render(); }
};
}  // namespace rendering
}  // namespace temp
