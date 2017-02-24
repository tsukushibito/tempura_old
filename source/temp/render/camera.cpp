#include "temp/render/camera.h"

namespace temp {
namespace render {

namespace {
std::vector<CameraData> cameraDataTable;
}

Camera::Camera(const RendererWPtr& renderer) : renderer_(renderer) {}

Camera::~Camera() {}

void Camera::setTransform(const math::Transform& transform) {
    transform_  = transform;
    auto&& wmat = transform_.toMatrix();
    wmat.inverse();
}

void Camera::setPerspective(Float32 fovy, Float32 aspect, Float32 znear,
                            Float32 zfar) {}

void Camera::setOrthographic(Float32 left, Float32 right, Float32 top,
                             Float32 bottom, Float32 znear, Float32 zfar) {}

const Camera::CameraData& getData() const {}

void cameraDataGavageCollect() {}
}
}
