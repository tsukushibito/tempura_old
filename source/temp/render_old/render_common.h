/**
 * @file render_common.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-16
 */
#pragma once
#ifndef GUARD_a4aa86077059460f897b1d3ba549f427
#define GUARD_a4aa86077059460f897b1d3ba549f427

#include "temp/temp_assert.h"

namespace temp {
namespace render_old {

enum class TextureAttribute {
    kAlbedoMap,
    kRoughnessMap,
    kMetalicMap,
    kNormalMap,

    COUNT,
};

template <typename T = TextureAttribute>
String textureAttributeString(TextureAttribute attribute) {
    switch (attribute) {
    case TextureAttribute::kAlbedoMap:
        return "AlbedoMap";
    case TextureAttribute::kRoughnessMap:
        return "RoughnessMap";
    case TextureAttribute::kMetalicMap:
        return "MetalicMap";
    case TextureAttribute::kNormalMap:
        return "NormalMap";
    case TextureAttribute::COUNT:
        TEMP_ASSERT(false, "Invalid TextureAttribute!");
        return "";
    }

    TEMP_ASSERT(false, "Invalid TextureAttribute!");
    return "";
}

struct DrawAreaSize {
    Size width;
    Size height;
};

}
}

#endif  // GUARD_a4aa86077059460f897b1d3ba549f427
