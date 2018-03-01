/**
 * @file resource_manager.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-10-20
 */
#pragma once
#ifndef GUARD_4d222f293b7d4645b5cfb16091da105f
#define GUARD_4d222f293b7d4645b5cfb16091da105f

#include "temp/system/thread_pool.h"

#include "temp/resource/resource_base.h"
#include "temp/resource/resource_common.h"

namespace temp {
namespace resource {

class ResourceManager : Singleton<ResourceManager> {
public:
private:
};
}
}

#endif  // GUARD_4d222f293b7d4645b5cfb16091da105f
