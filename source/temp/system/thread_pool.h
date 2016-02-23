/**
 * @file ThreadPool.h
 * @brief thread pool class
 * @author tsukushibito
 * @version 0.1.1
 * @date 2014-10-27
 */
#pragma once
#ifndef GUARD_45b24cf7bd344c0aadb1e393915359dd
#define GUARD_45b24cf7bd344c0aadb1e393915359dd

#include <deque>
#include <queue>
#include <functional>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

namespace temp {
namespace system {

class ThreadPool : public SmartPointerObject<ThreadPool> {
public:
    using JobType = std::function< void(void)>;

private:
    ThreadPool(const String &name, Size threadCount);

protected:
    ~ThreadPool();

public:
    static SPtr create(const String &name, Size threadCount);

    template < typename F, typename... Args >
    auto pushJob(F &&function, Args &&... args) -> std::future< typename std::result_of< F(Args...) >::type >;

    template < typename F, typename... Args >
    auto pushJobToSpecificThreadQueue(Size threadIndex, F &&function, Args &&... args)
        -> std::future< typename std::result_of< F(Args...) >::type >;

    JobType popJob();
    JobType popJobFromSpecificThreadQueue(Size threadIndex);

    const String &getName() const { return name_; }
    Size getThreadCount() const { return worker_threads_.size(); }
    Bool isJobQueueEmpty() const { return job_queue_.empty(); }
    Size getJobCount() const { return job_queue_.size(); }
    Bool isSpecificJobQueueEmpty(Size threadCount) const { return specific_job_queues_[threadCount].empty(); }
    Size getSpecificJobCount() const { return specific_job_queues_.size(); }

private:
    String name_;

    Vector< std::thread > worker_threads_;

    using JobContainerType = Deque< JobType >;
    using JobQueueType = std::queue< JobType, JobContainerType >;
    JobQueueType job_queue_;
    Vector< JobQueueType > specific_job_queues_;

    std::mutex queue_mutex_;
    std::condition_variable condition_;
    Bool stop_;
};
} // namespace system
} // namespace temp

#include "thread_pool_detail.h"

#endif // GUARD_45b24cf7bd344c0aadb1e393915359dd
