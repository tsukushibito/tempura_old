#pragma once
#include "temp/core/core.h"
namespace temp {
namespace rendering {

class SwapChain : public SmartPointerType<SwapChain> {
  friend class Renderer;

 public:
  void Present();
};

}  // namespace rendering
}  // namespace temp
