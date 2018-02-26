namespace temp {
namespace core {

ThreadPool::ThreadPool(const String &name, Size thread_count)
    : name_(name), worker_thread_list_(thread_count), stopped_(false) {
  for (Int32 i = 0; i < thread_count; ++i) {
    auto worker_function = [this, i]() {
      for (;;) {
        PackagedTaskType pack;
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

        if (pack) {
          pack();
        }
      }
    };

    worker_thread_list_[i].thread_ = std::thread(worker_function);
    worker_thread_list_[i].thread_id_ = worker_thread_list_[i].thread_.get_id();
  }
}

ThreadPool::~ThreadPool() {
  for (auto &&set : worker_thread_list_) {
    set.mutex_.lock();
  }

  stopped_ = true;

  for (auto &&set : worker_thread_list_) {
    set.mutex_.unlock();
  }

  for (auto &&set : worker_thread_list_) {
    set.condition_.notify_all();
  }

  for (auto &&set : worker_thread_list_) {
    set.thread_.join();
  }
}

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

ThreadPool::PackagedTaskType ThreadPool::popTask(Int32 thread_index) {
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

Size ThreadPool::taskCount(Int32 thread_index) const {
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

Bool ThreadPool::taskEmpty(Int32 thread_index) const {
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
}  // namespace core
}  // namespace temp