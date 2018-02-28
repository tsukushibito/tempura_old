#include <temp.h>

int main() {
  using namespace temp;
  auto engine = create();
  auto app = createApplication();
  app->setOnUpdateCallback([&engine]() { engine->update(); });
  auto exit_code = app->run();
  return exit_code;
}