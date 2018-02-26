namespace temp
{
namespace core
{

ThreadPool::ThreadPool(const String &name, Size thread_count)
    : name_(name), task_queues_(thread_count), stopped_(false)
{
    for (Int32 i = 0; i < thread_count; ++i)
    {
        auto worker_function = [this, i]() {
            for (;;)
            {
                PackagedTaskType pack;
                std::unique_lock<std::mutex> lock(task_queues_[i].mutex_);
                task_queues_[i].condition_.wait(lock, [this, i]() {
                    return stopped_ || !task_queues_[i].queue_.empty();
                });

                if (stopped_ && task_queues_[i].queue_.empty())
                {
                    return;
                }

                if (!task_queues_[i].queue_.empty())
                {
                    pack = std::move(task_queues_[i].queue_.front());
                    task_queues_[i].queue_.pop();
                }

                if (pack)
                {
                    pack();
                }
            }
        };

        worker_threads_.emplace_back(worker_function);
    }

    for (auto &&thread : worker_threads_)
    {
        thread_id_list_.emplace_back(thread.get_id());
    }
}

ThreadPool::~ThreadPool()
{
    for (auto &&set : task_queues_)
    {
        set.mutex_.lock();
    }

    stopped_ = true;

    for (auto &&set : task_queues_)
    {
        set.mutex_.unlock();
    }

    for (auto &&set : task_queues_)
    {
        set.condition_.notify_all();
    }

    for (auto &&thread : worker_threads_)
    {
        thread.join();
    }
}

template <typename Task, typename... Args>
auto ThreadPool::pushTask(Int32 thread_index, Task &&task, Args &&... args)
    -> std::future<typename std::result_of<Task(Args...)>::type>
{
    using ReturnType = typename std::result_of<Task(Args...)>::type;
    using PackagedTask = std::packaged_task<ReturnType()>;

    auto pack = std::make_shared<PackagedTask>(
        std::bind(std::forward<Task>(task), std::forward<Args>(args)...));
    std::future<ReturnType> result = pack->get_future();

    Int32 index = 0;
    if (thread_index >= worker_threads_.size() || thread_index < 0)
    {
        Size task_count_min = (Size)(-1);
        for (Int32 i = 0; i < task_queues_.size(); ++i)
        {
            auto &&task_queue = task_queues_[i].queue_;
            if (task_queue_.size() < task_count_min)
            {
                task_count_min = task_queue_.size();
                index = i;
            }
        }
    }
    else
    {
        index = thread_index;
    }

    std::unique_lock<std::mutex> lock(task_queues_[index].mutex_);
    if (stopped_)
    {
        return result;
    }

    task_queues_[index].queue_.emplace([task]() { (*task)(); });
    task_queues_[index].condition_.notify_all();

    return result;
}

ThreadPool::PackagedTaskType ThreadPool::popTask(Int32 thread_index)
{
    Int32 index = 0;
    if (thread_index >= worker_threads_.size() || thread_index < 0)
    {
        Size task_count_max = 0;
        for (Int32 i = 0; i < task_queues_.size(); ++i)
        {
            auto &&task_queue = task_queues_[i].queue_;
            if (task_queue.size() > task_count_max)
            {
                task_count_max = task_queue.size();
                index = i;
            }
        }
    }
    else
    {
        index = thread_index;
    }

    std::unique_lock<std::mutex> lock(task_queues_[index].mutex_);
    if (task_queues_[index].queue_.empty())
    {
        return PackagedTaskType();
    }

    auto pack = std::move(task_queues_[index].queue_.front());
    task_queues_[index].queue_.pop();

    return pack;
}

Size ThreadPool::taskCount(Int32 thread_index) const
{
    if (thread_index >= worker_threads_.size())
    {
        return 0;
    }
    else if (thread_index < 0)
    {
        Size count = 0;
        for (auto &&set : task_queues_)
        {
            count += set.queue_.size();
        }
        return count;
    }
    else
    {
        return task_queues_[thread_index].queue_.size();
    }
}

Bool ThreadPool::taskEmpty(Int32 thread_index) const
{
    if (thread_index >= worker_threads_.size())
    {
        return true;
    }
    else if (thread_index < 0)
    {
        Bool empty = true;
        for (auto &&set : task_queues_)
        {
            empty &= set.queue_.empty();
        }
        return empty;
    }
    else
    {
        return task_queues_[thread_index].queue_.empty();
    }
}
}
}