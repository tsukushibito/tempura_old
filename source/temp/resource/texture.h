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

#include "temp/resource/resource_base.h"

#include "temp/graphics/device.h"
#include "temp/graphics/texture.h"

namespace temp {
namespace resource {

class Texture : public ResourceBase<Texture> {
    friend class ResourceBase<Texture>;

    using Super = ResourceBase<Texture>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread,
                           const graphics::DeviceSPtr&     device);

    static void terminate();

private:
    static temp::graphics::DeviceSPtr s_graphics_device;

private:
    Texture(const system::Path& path);

    void loginImpl();
};
}
}

#endif  // GUARD_43ac592c05d74a69a4f60d7fce55d9ce
