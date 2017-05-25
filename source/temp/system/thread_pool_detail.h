namespace temp {
namespace system {

inline ThreadPool::ThreadPool(const String& name, Size threadCount)
    : name_(name), specific_job_queues_(threadCount), stop_(false) {
    for (Size i = 0; i < threadCount; ++i) {
        auto worker_function = [this, i]() {
            for (;;) {
                JobType job;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex_);
                    this->condition_.wait(lock, [this, i]() {
                        return this->stop_ || !this->job_queue_.empty()
                               || !this->specific_job_queues_[i].empty();
                    });

                    if (this->stop_ && this->job_queue_.empty()
                        && this->specific_job_queues_[i].empty()) {
                        return;
                    }

                    if (!specific_job_queues_[i].empty()) {
                        job = std::move(this->specific_job_queues_[i].front());
                        this->specific_job_queues_[i].pop();

                    } else if (!this->job_queue_.empty()) {
                        job = std::move(this->job_queue_.front());
                        this->job_queue_.pop();
                    }
                }
                if (job) job();
            }
        };
        worker_threads_.emplace_back(worker_function);
    }
    for (auto&& thread : worker_threads_) {
        thread_id_list_.emplace_back(thread.get_id());
    }
}

inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }

    condition_.notify_all();
    for (auto&& worker_thread : worker_threads_) {
        worker_thread.join();
    }
}

template <typename F, typename... Args>
auto ThreadPool::pushJob(F&& function, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
    using ReturnType   = typename std::result_of<F(Args...)>::type;
    using PackagedTask = std::packaged_task<ReturnType()>;

    auto task = std::make_shared<PackagedTask>(
        std::bind(std::forward<F>(function), std::forward<Args>(args)...));

    std::future<ReturnType> result = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (stop_) {
            // TEMP_ASSERT(false, "");
            return result;
        }

        job_queue_.emplace([task]() { (*task)(); });
    }

    condition_.notify_one();
    return result;
}

template <typename F, typename... Args>
auto ThreadPool::pushJobToSpecificThreadQueue(Size threadIndex, F&& function,
                                              Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
    using ReturnType   = typename std::result_of<F(Args...)>::type;
    using PackagedTask = std::packaged_task<ReturnType()>;

    auto task = std::make_shared<PackagedTask>(
        std::bind(std::forward<F>(function), std::forward<Args>(args)...));
    std::future<ReturnType> result = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (stop_) {
            // TEMP_ASSERT(false, "");
            return result;
        }

        specific_job_queues_[threadIndex].emplace([task]() { (*task)(); });
    }

    condition_.notify_all();
    return result;
}

inline ThreadPool::JobType ThreadPool::popJob() {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    if (this->job_queue_.empty()) {
        return JobType();
    }
    auto job = std::move(this->job_queue_.front());
    this->job_queue_.pop();

    return job;
}

inline ThreadPool::JobType ThreadPool::popJobFromSpecificThreadQueue(
    Size thread_index) {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    if (this->specific_job_queues_[thread_index].empty()) {
        return JobType();
    }
    auto job = std::move(this->specific_job_queues_[thread_index].front());
    this->specific_job_queues_[thread_index].pop();

    return job;
}

}  // namespace system
}  // namespace temp
