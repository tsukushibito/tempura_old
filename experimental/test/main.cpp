#include <temp.h>

int main() {
  using namespace temp;
  auto app = createApplication();
  auto exit_code = app->run();
  return exit_code;
}