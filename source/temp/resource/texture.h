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

namespace temp {
namespace resource {

class Texture : public ResourceBase<Texture> {
    friend class ResourceBase<Texture>;

private:
    Texture(const system::Path& path);

protected:
    void loginImpl();
};
}
}

#endif  // GUARD_43ac592c05d74a69a4f60d7fce55d9ce
