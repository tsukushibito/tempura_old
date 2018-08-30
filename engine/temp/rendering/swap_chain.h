#pragma once
#include "temp/core/core.h"

namespace temp {
namespace rendering {

class Renderer;

class SwapChain : public SmartPointerType<SwapChain> {
  friend class SmartPointerType<SwapChain>;
  using RendererSPtr = std::shared_ptr<Renderer>;

  SwapChain(const RendererSPtr& renderer, void* native_window_handle);

 public:
  void Present();

 private:
  class Impl;
  static const Size kImplSize = 128;
  static const Size kImplAlignment = std::alignment_of<std::max_align_t>::value;
  using ImplStorage = std::aligned_storage<kImplSize, kImplAlignment>::type;
  ImplStorage impl_strage_;
  Impl* impl_;
};

}  // namespace rendering
}  // namespace temp
