/**
 * @file texture.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-21
 */
#include "temp/resource/texture.h"

namespace temp {
namespace resource {

Texture::Texture(const system::Path& path) : ResourceBase<Texture>(path) {}

void Texture::loginImpl() {}
}
}
