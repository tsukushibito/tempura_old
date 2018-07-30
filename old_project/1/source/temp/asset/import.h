#pragma once
#include "temp/common/common.h"
#include "temp/core/filesystem.h"
#include "temp/resource/texture.h"

namespace temp {
namespace asset {

resource::Texture::SPtr importTexture(const filesystem::path& path);

}  // namespace asset
}  // namespace temp