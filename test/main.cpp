#include <temp/tempura.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  using namespace temp;
  class Test : public SmartPointerType<Test> {
   public:
    Test(Size v) : value_(v) {
      // TEMP_LOG_TRACE("Test", fmt::format("Test::Test({0})", value_));
    }
    virtual ~Test() {
      // TEMP_LOG_TRACE("Test", fmt::format("Test::~Test() {0}", value_));
    }

    void Wait() { usleep(10); }

   private:
    Size value_;
  };

  unsigned num_cpus = std::thread::hardware_concurrency();
  std::cout << "Launching " << num_cpus << " threads\n";

  auto allocator = std::allocator<Test>();
  HashTable<std::thread::id, Size> count_table;
  {
    const Size kThreadCount = 4;
    auto task_manager =
        TaskManager::AllocateUnique(allocator, "TestTaskManager", kThreadCount);
    for (int i = 0; i < kThreadCount; ++i) {
      auto id = task_manager->thread_id(i);
      count_table[id] = 0;
    }

    for (auto i = 0; i < 100000; ++i) {
      task_manager->PushTask([&allocator, &count_table]() {
        auto hasher = std::hash<std::thread::id>();
        auto this_thread_id = std::this_thread::get_id();
        auto thread_hash = hasher(this_thread_id);
        auto u = Test::AllocateUnique(allocator, thread_hash);
        u->Wait();
        count_table[this_thread_id] += 1;
      });
      // TEMP_LOG_TRACE("Test", fmt::format("Pushed: {0}", i));
    }
    TEMP_LOG_TRACE("Test", "waiting...");
  }

  auto hasher = std::hash<std::thread::id>();
  for (auto pair : count_table) {
    TEMP_LOG_TRACE("Test",
                   fmt::format("{0}:{1}", hasher(pair.first), pair.second));
  }

  return 0;
}
