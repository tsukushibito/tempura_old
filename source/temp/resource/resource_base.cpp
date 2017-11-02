#include <fstream>
#include <iostream>
#include <iterator>

#include "temp/resource/resource_base.h"

namespace temp {
namespace resource {

ResourceBase::ResourceBase(const Path&               path,
                           const ThreadPool::SPtr&   load_thread,
                           std::function<void(void)> on_destroy)
    : load_thread_(load_thread)
    , state_(kNotLoaded)
    , path_(path)
    , on_destroy_(on_destroy) {
    id_ = std::hash<std::string>()(path_.string());
}

virtual ResourceBase::~ResourceBase() { on_destroy_(); }

void ResourceBase::load(Bool is_sync) {
    if (state_ != ResourceState::kNotLoaded) return;

    auto job = [this]() { load_impl(false); };
    if (is_sync) {
        execJobSyncInLoadThread(job);
    } else {
        load_thread_.pushJob(job);
    }
}

void ResourceBase::reload(Bool is_sync) {
    auto job = [this]() { load_impl(true); };
    if (is_sync) {
        execJobSyncInLoadThread(job);
    } else {
        load_thread_.pushJob(job);
    }
}

void ResourceBase::loadImpl(Bool is_reload) {
    std::unique_lock<std::mutex>(mutex_);

    if (is_reload) {
        on_destroy_();
    }

    state_ = ResourceState::kLoading;

    if (!filesystem::exists(path_)) {
        state_ = ResourceState::kNotExists;
        return;
    }

    std::ifstream ifs(path_);

    std::istreambuf_iterator<ByteData::value_type> beg;
    std::istreambuf_iterator<ByteData::value_type> end;

    ByteData byte_data(beg, end);

    prepare(byte_data);
}

void ResourceBas::execJobSyncInLoadThread(std::function<void(void)> job) {
    Bool is_load_thread = false;

    auto&& thread_id      = std::this_thread::get_id();
    auto&& thread_id_list = load_thread_->threadIdList();
    for (auto&& i : thread_id_list) {
        if (i == thread_id) {
            is_load_thread = true;
        }
    }

    if (is_load_thread) {
        job();
    } else {
        auto&& future = load_thread_->pushJob(job);
        future.wait();
    }
}
}
}
