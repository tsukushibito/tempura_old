#include "temp/resource/resource_manager.h"

namespace temp {
namespace resource {

class TestRes : public ResourceBase {
public:
    TestRes(const Path& path, const ThreadPool::SPtr& load_thread,
            std::function<void(void)> on_destroy)
        : ResourceBase(path, load_thread, on_destroy) {}

private:
	virtual void prepare(const ByteData& byte_data) { (void*)(&byte_data); }
};

void f() {
    auto thread_pool = ThreadPool::makeShared("test", 1);

    TestRes res("test", thread_pool, []() {});
}
}
}
