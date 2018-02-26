#include <temp/app/application.h>
#include <temp/core/thread_pool.h>

int main() {
  using namespace temp;
  app::Application app;
  auto exit_code = app.run();
  return exit_code;
}