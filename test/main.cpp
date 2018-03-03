#include <temp.h>

int main() {
  using namespace temp;
  auto app = createApplication();
  auto engine = create(app->getNativeWindowHandle());
  app->setOnUpdateCallback([&engine]() { engine->update(); });
  auto exit_code = app->run();
  return exit_code;
}