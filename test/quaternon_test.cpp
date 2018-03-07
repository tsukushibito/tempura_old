#include <gtest/gtest.h>
#include <temp.h>

class QuaternionTest : public testing::Test {
 protected:
  virtual void SetUp() { using namespace temp::math; }
};

TEST_F(QuaternionTest, Angles) {
  using namespace temp::math;
  // auto matZ90 = Matrix4x4(0, -1, 0, 0,  //
  //                         1, 0, 0, 0,   //
  //                         0, 0, 1, 0,   //
  //                         0, 0, 0, 1);
  auto quatX90 = Quaternion::fromXAxisAngle(90);
  auto quatY90 = Quaternion::fromYAxisAngle(90);
  auto quatZ90 = Quaternion::fromZAxisAngle(90);
  auto quatX180 = Quaternion::fromXAxisAngle(180);
  auto quatY180 = Quaternion::fromYAxisAngle(180);
  auto quatZ180 = Quaternion::fromZAxisAngle(180);
  auto matX90 = quatX90.toMatrix();
  auto matY90 = quatY90.toMatrix();
  auto matZ90 = quatZ90.toMatrix();
  auto right = Vector3::right();
  auto up = quatZ90 * right;
  auto forward = quatX90 * up;
  auto right_ = quatY90 * forward;
  auto right4 = Vector4(right);
  auto up4 = matZ90 * right4;
  auto forward4 = matX90 * up4;
  auto right4_ = matY90 * forward4;
  EXPECT_TRUE(right == right_);
}
