#include <gtest/gtest.h>
#include <temp.h>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  auto result = RUN_ALL_TESTS();
  std::cout << "Test return " << result << std::endl;

  using namespace temp;
  auto app = createApplication();
  auto engine = create(app->getNativeWindowHandle());
  auto res_manager = engine->resourceManager();
  auto mesh = res_manager->create<resource::Mesh>("test.tmsh");
  app->setOnUpdateCallback([&engine]() { engine->update(); });
  auto exit_code = app->run();
  return exit_code;
}
