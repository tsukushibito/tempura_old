#include <temp/tempura.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
  using namespace temp;

  {
    TEMP_LOG_TRACE("test", "Create application.");
    auto app = system::Application::MakeUnique();
    auto task_manager = TaskManager::MakeShared("TaskManager", 4);
    auto load_task_manager = TaskManager::MakeShared("LoadTaskManager", 1);
    auto resource_manager =
        resource::ResourceManager::MakeShared(load_task_manager, "./");
    auto renderer = rendering::CreateRenderer(rendering::GraphicsApi::kVulkan,
                                              task_manager, resource_manager);

    app->on_initialize() = []() {};
    app->on_update() = []() {};
    app->on_terminate() = []() {};
    app->Run();
  }

  return 0;
}
