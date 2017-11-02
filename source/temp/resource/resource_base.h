/**
 * @file resource_base.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-10-21
 */
#pragma once
#ifndef GUARD_360187526cfb4535afe399af584e6498
#define GUARD_360187526cfb4535afe399af584e6498

#include <utility>

#include "temp/system/thread_pool.h"

#include "temp/resource/resource_base.h"
#include "temp/resource/resource_common.h"

namespace temp {
namespace resource {

using Path       = filesystem::Path;
using ThreadPool = system::ThreadPool;

enum class ResourceState {
    kNotLoaded,
    kLoading,
    kLoaded,
    kNotExists,
};

class ResourceBase {
public:
    using UPtr = std::unique_ptr<ResourceBase>;
    using SPtr = std::shared_ptr<ResourceBase>;
    using WPtr = std::weak_ptr<ResourceBase>;

    ResourceBase(const Path& path, const ThreadPool::SPtr& load_thread,
                 std::function<void(void)> on_destroy);

    virtual ~ResourceBase();

    void load(Bool is_sync = false);

    void reload(Bool is_sync = false);

private:
    void loadImpl(Bool is_reload);

    void execJobSyncInLoadThread(std::function<void(void)> job);

    virtual void prepare(const ByteData& byte_data) = 0;

private:
    std::mutex                mutex_;
    ThreadPool::SPtr          load_thread_;
    ResourceState             state_;
    ResourceId                id_;
    Path                      path_;
    std::function<void(void)> on_destroy_;
};
}
}

#endif  // GUARD_360187526cfb4535afe399af584e6498
