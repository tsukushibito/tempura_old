#include <gtest/gtest.h>
#include <temp.h>

class Vector3Test : public testing::Test {
 protected:
  virtual void SetUp() { using namespace temp::math; }
};

TEST_F(Vector3Test, Add) {
  using namespace temp::math;
  auto r = Vector3::one() + Vector3::zero();
  EXPECT_TRUE(r == Vector3::one());
  r = Vector3::one() + Vector3::one();
  EXPECT_TRUE(r == Vector3(2.0f, 2.0f, 2.0f));
}

TEST_F(Vector3Test, Sub) {
  using namespace temp::math;
  auto r = Vector3::one() - Vector3::zero();
  EXPECT_TRUE(r == Vector3::one());
  r = Vector3::one() - Vector3::one();
  EXPECT_TRUE(r == Vector3::zero());
}

TEST_F(Vector3Test, Mod) {
  using namespace temp::math;
  auto r = 2 * Vector3(1.0f, 2.0f, 0.0f);
  EXPECT_TRUE(r == Vector3(2.0f, 4.0f, 0.0f));
  r = Vector3::one() * 2;
  EXPECT_TRUE(r == Vector3(2.0f, 2.0f, 2.0f));
}

TEST_F(Vector3Test, Div) {
  using namespace temp::math;
  auto r = Vector3(2.0f, 2.0f, 2.0f) / 2;
  EXPECT_TRUE(r == Vector3::one());
}

TEST_F(Vector3Test, Dot) {
  using namespace temp::math;
  auto r = dot(Vector3::right(), Vector3::up());
  EXPECT_TRUE(r == 0);
  r = dot(Vector3::forward(), Vector3::forward());
  EXPECT_TRUE(r == 1);
}

TEST_F(Vector3Test, Cross) {
  using namespace temp::math;
  auto r = cross(Vector3::right(), Vector3::up());
  EXPECT_TRUE(r == Vector3::forward());
}

TEST_F(Vector3Test, Magnitude) {
  using namespace temp::math;
  auto r = Vector3::up().magnitude();
  EXPECT_TRUE(r == 1.0f);
  r = Vector3::one().magnitude();
  EXPECT_TRUE(sqrt(3) - 0.0001f < r && r < sqrt(3) + 0.0001f);
}

TEST_F(Vector3Test, Normalize) {
  using namespace temp::math;
  auto r = Vector3(1.0f, 2.0f, 3.0f).normalized().magnitude();
  EXPECT_TRUE(1.0f - 0.0001f < r && r < 1.0f + 0.0001f);
}

TEST_F(Vector3Test, Angle) {
  using namespace temp::math;
  auto r = angle(Vector3::right(), Vector3::up());
  EXPECT_TRUE(0.5f * kPi - 0.0001f < r && r < 0.5f * kPi + 0.0001f);
  r = angle(Vector3::right(), Vector3(1.0f, 1.0f, 0.0f));
  EXPECT_TRUE(0.25f * kPi - 0.0001f < r && r < 0.25f * kPi + 0.0001f);
}

TEST_F(Vector3Test, Lerp) {
  using namespace temp::math;
  auto a = Vector3();
  auto b = Vector3(2.0f, 3.0f, 4.0f);
  auto m = Vector3(1.0f, 1.5f, 2.0f);
  auto r = lerp(a, b, 0.0f);
  EXPECT_TRUE(r == a);
  r = lerp(a, b, 1.0f);
  EXPECT_TRUE(r == b);
  r = lerp(a, b, 0.5f);
  EXPECT_TRUE(r == m);
}
