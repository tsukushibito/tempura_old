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
    Material(const system::Path& path);

    void loginImpl();

public:

private:
}

#endif // GUARD_7f5cd58930d54c3abac6b518bbd1e9e5
