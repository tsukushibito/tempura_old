#pragma once
#include <memory>
#include "temp/core/core.h"
#include "temp/graphics/graphics.h"

namespace temp {
namespace rendering {

class Renderer;
using RendererSPtr = std::shared_ptr<Rendering>;

class Model {
  friend class Renderer;

 private:
  Model() = default;

 public:
  virtual ~Model();

 private:
  UInt32 layer_bit_flags_;
};
}  // namespace rendering
}  // namespace temp