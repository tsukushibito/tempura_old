/**
 * @file loading_thread.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-08
 */
#pragma once
#ifndef GUARD_94efd64dcded497bbdd4645c4894cb57
#define GUARD_94efd64dcded497bbdd4645c4894cb57

#include "temp/system/thread_pool.h"

namespace temp {
namespace resource {

class LoadingThread {
private:
    LoadingThread() = delete;

public:
    using ThreadPool = temp::system::ThreadPool;

    static void initialize(const temp::system::ThreadPool::SPtr& thread_pool) {
        s_thread_pool = thread_pool;
    }
    static std::future<void> pushJob(const ThreadPool::JobType& job) {
        return s_thread_pool->pushJob(job);
    }

private:
    static temp::system::ThreadPool::SPtr s_thread_pool;
};
}
}

#endif  // GUARD_94efd64dcded497bbdd4645c4894cb57
