#include <temp/tempura.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
  using namespace temp;

  auto allocator = std::allocator<int>();
  auto task_manager = TaskManager::AllocateShared(allocator, "TaskManager", 4);
  auto load_task_manager =
      TaskManager::AllocateShared(allocator, "LoadTaskManager", 1);
  auto resource_manager = resource::ResourceManager::AllocateShared(
      allocator, load_task_manager, "./");
  auto renderer = rendering::Renderer::AllocateShared(allocator, task_manager,
                                                      resource_manager);
  TEMP_LOG_TRACE("test", "Create application.");
  auto app = system::Application::MakeUnique();
  app->Run();

  return 0;
}
