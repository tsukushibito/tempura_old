#include "temp/core/task_manager.h"
namespace temp {

TaskManager::TaskManager(const String &name, Size thread_count)
    : name_(name), worker_thread_list_(thread_count), stopped_(false) {
  for (Int32 i = 0; i < thread_count; ++i) {
    auto worker_function = [this, i]() {
      for (;;) {
        PackagedTaskType pack;
        {
          std::unique_lock<std::mutex> lock(worker_thread_list_[i].mutex_);
          worker_thread_list_[i].condition_.wait(lock, [this, i]() {
            return stopped_ || !worker_thread_list_[i].task_queue_.empty();
          });

          if (stopped_ && worker_thread_list_[i].task_queue_.empty()) {
            return;
          }

          if (!worker_thread_list_[i].task_queue_.empty()) {
            pack = std::move(worker_thread_list_[i].task_queue_.front());
            worker_thread_list_[i].task_queue_.pop();
          }
        }

        if (pack) {
          pack();
        }
      }
    };

    worker_thread_list_[i].thread_ = std::thread(worker_function);
    worker_thread_list_[i].thread_id_ = worker_thread_list_[i].thread_.get_id();
  }
}

TaskManager::~TaskManager() {
  for (auto &&worker : worker_thread_list_) {
    worker.mutex_.lock();
  }

  stopped_ = true;

  for (auto &&worker : worker_thread_list_) {
    worker.mutex_.unlock();
  }

  for (auto &&worker : worker_thread_list_) {
    worker.condition_.notify_all();
  }

  for (auto &&worker : worker_thread_list_) {
    worker.thread_.join();
  }
}

TaskManager::PackagedTaskType TaskManager::PopTask(Int32 thread_index) {
  Int32 index = 0;
  if (thread_index >= worker_thread_list_.size() || thread_index < 0) {
    Size task_count_max = 0;
    for (Int32 i = 0; i < worker_thread_list_.size(); ++i) {
      auto &&task_queue = worker_thread_list_[i].task_queue_;
      if (task_queue.size() > task_count_max) {
        task_count_max = task_queue.size();
        index = i;
      }
    }
  } else {
    index = thread_index;
  }

  std::unique_lock<std::mutex> lock(worker_thread_list_[index].mutex_);
  if (worker_thread_list_[index].task_queue_.empty()) {
    return PackagedTaskType();
  }

  auto pack = std::move(worker_thread_list_[index].task_queue_.front());
  worker_thread_list_[index].task_queue_.pop();

  return pack;
}

Size TaskManager::task_count(Int32 thread_index) const {
  if (thread_index >= worker_thread_list_.size()) {
    return 0;
  } else if (thread_index < 0) {
    Size count = 0;
    for (auto &&set : worker_thread_list_) {
      count += set.task_queue_.size();
    }
    return count;
  } else {
    return worker_thread_list_[thread_index].task_queue_.size();
  }
}

Bool TaskManager::is_task_empty(Int32 thread_index) const {
  if (thread_index >= worker_thread_list_.size()) {
    return true;
  } else if (thread_index < 0) {
    Bool empty = true;
    for (auto &&set : worker_thread_list_) {
      empty &= set.task_queue_.empty();
    }
    return empty;
  } else {
    return worker_thread_list_[thread_index].task_queue_.empty();
  }
}
}  // namespace temp