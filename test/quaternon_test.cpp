#include <gtest/gtest.h>
#include <temp.h>

class QuaternionTest : public testing::Test {
 protected:
  virtual void SetUp() { using namespace temp::math; }
};

TEST_F(QuaternionTest, Angles) {
  using namespace temp::math;
  auto id = Quaternion::identity();
  auto mat = id.toMatrix();
  auto angles = id.eulerAngles();
  EXPECT_TRUE(angles == Vector3::zero());
}
