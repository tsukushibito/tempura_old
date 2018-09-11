#pragma once
#include <memory>

#include "temp/core/core.h"
#include "temp/graphics/graphics.h"

namespace temp {
namespace rendering {

class Camera;
using CameraSPtr = std::shared_ptr<Camera>;
using CameraWPtr = std::weak_ptr<Camera>;

class Light;
using LightSPtr = std::shared_ptr<Light>;
using LightWPtr = std::weak_ptr<Light>;

class Model;
using ModelSPtr = std::shared_ptr<Model>;
using ModelWPtr = std::weak_ptr<Model>;

class Renderer {
 public:
  Renderer() = default;
  virtual ~Renderer() = default;

  CameraSPtr CreateCamera() { return nullptr; }

  ModelSPtr CreateModel() { return nullptr;}

  virtual void Draw() = 0;

 private:
  std::vector<CameraWPtr> camera_list_;
  std::vector<ModelWPtr> model_list_;
};

using RendererSPtr = std::shared_ptr<Renderer>;

RendererSPtr CreateRenderer(const temp::graphics::DeviceSPtr& device);

}  // namespace rendering
}  // namespace temp
