#include <gtest/gtest.h>
#include <temp.h>

class Vector2Test : public testing::Test {
 protected:
  virtual void SetUp() {
    using namespace temp::math;
    x0y0 = Vector2();
    x1y1 = Vector2(1.0f, 1.0f);
    x1y0 = Vector2(1.0f, 0.0f);
    x0y1 = Vector2(0.0f, 1.0f);
    x2y1 = Vector2(2.0f, 1.0f);
    x1y2 = Vector2(1.0f, 2.0f);
    x2y0 = Vector2(2.0f, 0.0f);
    x0y2 = Vector2(0.0f, 2.0f);
    x2y2 = Vector2(2.0f, 2.0f);
  }

  temp::math::Vector2 x0y0;
  temp::math::Vector2 x1y1;
  temp::math::Vector2 x1y0;
  temp::math::Vector2 x0y1;
  temp::math::Vector2 x2y1;
  temp::math::Vector2 x1y2;
  temp::math::Vector2 x2y0;
  temp::math::Vector2 x0y2;
  temp::math::Vector2 x2y2;
};

TEST_F(Vector2Test, Add) {
  using namespace temp::math;
  auto r = x0y0 + x1y0;
  EXPECT_TRUE(r == x1y0);
  r = x0y1 + x1y1;
  EXPECT_TRUE(r == x1y2);
}

TEST_F(Vector2Test, Sub) {
  using namespace temp::math;
  auto r = x1y0 - x1y0;
  EXPECT_TRUE(r == x0y0);
  r = x2y1 - x1y1;
  EXPECT_TRUE(r == x1y0);
}

TEST_F(Vector2Test, Mod) {
  using namespace temp::math;
  auto r = 2 * x1y0;
  EXPECT_TRUE(r == x2y0);
  r = x1y0 * 2;
  EXPECT_TRUE(r == x2y0);
}

TEST_F(Vector2Test, Div) {
  using namespace temp::math;
  auto r = x2y2 / 2;
  EXPECT_TRUE(r == x1y1);
}

TEST_F(Vector2Test, Dot) {
  using namespace temp::math;
  auto r = dot(x1y0, x0y1);
  EXPECT_TRUE(r == 0);
  r = dot(x1y0, x1y0);
  EXPECT_TRUE(r == 1);
  r = dot(x1y1, x1y0);
  EXPECT_TRUE(r == 1);
}

TEST_F(Vector2Test, Magnitude) {
  using namespace temp::math;
  auto r = x1y1.magnitude();
  EXPECT_TRUE(sqrt(2) - 0.0001f < r && r < sqrt(2) + 0.0001f);
}

TEST_F(Vector2Test, Normalize) {
  using namespace temp::math;
  auto r = x2y1.normalized().magnitude();
  EXPECT_TRUE(1.0f - 0.0001f < r && r < 1.0f + 0.0001f);
}

TEST_F(Vector2Test, Angle) {
  using namespace temp::math;
  auto r = angle(x1y0, x0y1);
  EXPECT_TRUE(0.5f * kPi - 0.0001f < r && r < 0.5f * kPi + 0.0001f);
  r = angle(x1y0, x2y2);
  EXPECT_TRUE(0.25f * kPi - 0.0001f < r && r < 0.25f * kPi + 0.0001f);
}
