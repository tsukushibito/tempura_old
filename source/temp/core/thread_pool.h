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

template <typename Task, typename... Args>
auto ThreadPool::pushTask(Int32 thread_index, Task &&task, Args &&... args)
    -> std::future<typename std::result_of<Task(Args...)>::type> {
  using ReturnType = typename std::result_of<Task(Args...)>::type;
  using PackagedTask = std::packaged_task<ReturnType()>;

  auto pack = std::make_shared<PackagedTask>(
      std::bind(std::forward<Task>(task), std::forward<Args>(args)...));
  std::future<ReturnType> result = pack->get_future();

  Int32 index = 0;
  if (thread_index >= worker_thread_list_.size() || thread_index < 0) {
    Size task_count_min = (Size)(-1);
    for (Int32 i = 0; i < worker_thread_list_.size(); ++i) {
      auto &&task_queue = worker_thread_list_[i].task_queue_;
      if (task_queue.size() < task_count_min) {
        task_count_min = task_queue.size();
        index = i;
      }
    }
  } else {
    index = thread_index;
  }

  std::unique_lock<std::mutex> lock(worker_thread_list_[index].mutex_);
  if (stopped_) {
    return result;
  }

  worker_thread_list_[index].task_queue_.emplace([pack]() { (*pack)(); });
  worker_thread_list_[index].condition_.notify_all();

  return result;
}

}  // namespace core
}  // namespace temp