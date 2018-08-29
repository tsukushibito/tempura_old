#pragma once
namespace temp {
namespace rendering {

template <typename T>
class SwapChainBase : public SmartPointerType<T> {
 public:
  void Present() { static_cast<T*>(this)->Present(); }
};

}  // namespace rendering
}  // namespace temp