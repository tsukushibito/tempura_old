#include <temp/tempura.h>
#include <cstdlib>
#include <string>

void* operator new(size_t size) { return malloc(size); }
void operator delete(void* p) { free(p); }

int main(int argc, char* argv[]) {
  using namespace temp;

  {
    TEMP_LOG_TRACE("test", "Create application.");
    auto app = system::Application::MakeUnique();
    auto task_manager = TaskManager::MakeShared("TaskManager", 4);
    auto device = graphics::CreateDevice(graphics::GraphicsApi::kVulkan,
                                         app->native_window_handle());
    auto load_task_manager = TaskManager::MakeShared("LoadTaskManager", 1);
    auto resource_manager =
        resource::ResourceManager::MakeShared("./", load_task_manager, device);

    auto vert = resource_manager->CreateAndLoad<resource::VertexShader>(
        "shaders/default.vert.spv");
    auto frag = resource_manager->CreateAndLoad<resource::FragmentShader>(
        "shaders/default.frag.spv");

    app->on_initialize() = []() {};
    app->on_update() = []() {};
    app->on_terminate() = []() {};
    app->Run();
  }

  return 0;
}
