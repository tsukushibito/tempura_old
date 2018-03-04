#include <gtest/gtest.h>
#include <temp.h>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ApplicationTest, Run) {
  using namespace temp;
  auto app = createApplication();
  auto engine = create(app->getNativeWindowHandle());
  app->setOnUpdateCallback([&engine]() { engine->update(); });
  auto exit_code = app->run();
  EXPECT_EQ(exit_code, 0);
}
