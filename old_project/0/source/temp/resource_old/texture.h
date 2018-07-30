/**
 * @file texture.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-19
 */
#pragma once
#ifndef GUARD_43ac592c05d74a69a4f60d7fce55d9ce
#define GUARD_43ac592c05d74a69a4f60d7fce55d9ce

#include "temp/resource_old/resource_base.h"

#include "temp/graphics_/graphics.h"

namespace temp {
namespace resource_old {

class Texture : public ResourceBase<Texture> {
    friend class ResourceBase<Texture>;

    using Super = ResourceBase<Texture>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread,
                           const graphics_::Device::SPtr&   device);

    static void terminate();

private:
    static temp::graphics_::Device::SPtr s_graphics_device;

    static const String kTypeName;

public:
    using TextureSPtr = temp::graphics_::Texture::SPtr;

private:
    Texture(const system::Path& path);

    void deserialize(std::ifstream& ifs);
    void serialize(std::ofstream& ofs);

public:
    TextureSPtr texture() const { return texture_; }

    void replaceTexture(const TextureSPtr& texture) { texture_ = texture; }

private:
    temp::graphics_::Texture::SPtr texture_;
};

}
}

#endif  // GUARD_43ac592c05d74a69a4f60d7fce55d9ce
