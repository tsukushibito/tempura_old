#pragma once
#include <algorithm>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include "common/type.h"
#include "common/container.h"

namespace temp
{
namespace core
{

class ThreadPool : public SmartPointerObject<ThreadPool>
{
    friend class SmartPointerObject<ThreadPool>;

  public:
    using PackagedTaskType = std::function<void(void)>;

  private:
    ThreadPool(const String &name, Size thread_count);

  public:
    ~ThreadPool();

    template <typename Task, typename... Args>
    auto pushTask(Int32 thread_index, Task &&task, Args &&... args)
        -> std::future<typename std::result_of<Task(Args...)>::type>;

    PackagedTaskType popTask(Int32 thread_index);

    const String &name() const { return name_; }

    Size threadCount() const { return worker_threads_.size(); }

    Size taskCount(Int32 thread_index) const;
    Bool taskEmpty(Int32 thread_index) const;

    const Vector<std::thread::id> &threadIdList() { return thread_id_list_; }

  private:
    using TaskQueueType = Queue<PackagedTaskType>;
    struct TaskQueueSet
    {
        TaskQueueType queue_;
        std::mutex mutex_;
        std::condition_variable condition_;
	};

    String name_;

    Vector<std::thread> worker_threads_;
    Vector<std::thread::id> thread_id_list_;

    Vector<TaskQueueSet> task_queues_;

    Bool stopped_;
};
}
}

#include "core/thread_pool_detail.h"