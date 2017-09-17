/**
 * @file material.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-07-11
 */
#pragma once
#ifndef GUARD_7f5cd58930d54c3abac6b518bbd1e9e5
#define GUARD_7f5cd58930d54c3abac6b518bbd1e9e5

#include "temp/container.h"
#include "temp/temp_math.h"

#include "temp/resource/resource_base.h"
#include "temp/resource/texture.h"

namespace temp {
namespace resource {

class Material : public ResourceBase<Material> {
    friend class ResourceBase<Material>;

    using Super = ResourceBase<Material>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread);

    static void terminate();

private:
    static const temp::String kTypeName;

public:
private:
    explicit Material(const system::Path& path);

    void deserialize(std::ifstream& ifs);
    void serialize(std::ofstream& ofs);

public:
    const Color&  baseColor() const { return base_color_; }
    Float32       roughness() const { return roughness_; }
    Float32       metalic() const { return metalic_; }
    const Texture::SPtr albedoMap() const { return albedo_map_; }
    const Texture::SPtr roughnessMap() const { return roughness_map_; }
    const Texture::SPtr metalicMap() const { return metalic_map_; }
    const Texture::SPtr normalMap() const { return normal_map_; }

    void replaceBaseColor(const Color& color) { base_color_ = color; }
    void replaceRoughness(Float32 roughness) { roughness_ = roughness; }
    void replaceMetalic(Float32 metalic) { metalic_ = metalic; }
    void replaceAlbedoMap(const Texture::SPtr& tex) { albedo_map_ = tex; }
    void replaceRoughnessMap(const Texture::SPtr& tex) { roughness_map_ = tex; }
    void replaceMetalicMap(const Texture::SPtr& tex) { metalic_map_ = tex; }
    void replaceNormalMap(const Texture::SPtr& tex) { normal_map_ = tex; }

private:
    Color   base_color_;
    Float32 roughness_;
    Float32 metalic_;

    Texture::SPtr albedo_map_;
    Texture::SPtr roughness_map_;
    Texture::SPtr metalic_map_;
    Texture::SPtr normal_map_;
};
}
}

#endif  // GUARD_7f5cd58930d54c3abac6b518bbd1e9e5
