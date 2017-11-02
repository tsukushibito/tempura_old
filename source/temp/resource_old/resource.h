/**
 * @file resource.h
 * @brief resource headers
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-28
 */
#pragma once
#ifndef GUARD_36db4a3c442d4852b700c9f980eef17b
#define GUARD_36db4a3c442d4852b700c9f980eef17b

#include "temp/resource_old/material.h"
#include "temp/resource_old/mesh.h"
#include "temp/resource_old/pixel_shader.h"
#include "temp/resource_old/texture.h"
#include "temp/resource_old/vertex_shader.h"

namespace temp {
namespace resource_old {
void initialize(const system::ThreadPool::SPtr& loading_thread,
                const graphics_::Device::SPtr&   device);

void terminate();
}
}

#endif  // GUARD_36db4a3c442d4852b700c9f980eef17b
