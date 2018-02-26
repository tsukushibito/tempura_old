#pragma once
#include <algorithm>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include "temp/common/container.h"
#include "temp/common/type.h"

namespace temp {
namespace core {

class ThreadPool : public SmartPointerObject<ThreadPool> {
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

  Size threadCount() const { return worker_thread_list_.size(); }

  Size taskCount(Int32 thread_index) const;
  Bool taskEmpty(Int32 thread_index) const;

  const std::thread::id &threadId(Int32 thread_index) {
    return worker_thread_list_[thread_index].thread_id_;
  }

 private:
  using TaskQueueType = Queue<PackagedTaskType>;
  struct WorkerThreadSet {
    std::thread thread_;
    std::thread::id thread_id_;
    TaskQueueType task_queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
  };

  String name_;

  Vector<WorkerThreadSet> worker_thread_list_;

  Bool stopped_;
};
}  // namespace core
}  // namespace temp

#include "temp/core/thread_pool_detail.h"