#include <gtest/gtest.h>
#include <temp.h>

class Matrix4x4Test : public testing::Test {
 protected:
  virtual void SetUp() { using namespace temp::math; }
};

TEST_F(Matrix4x4Test, Detarminant) {
  using namespace temp::math;
  Matrix4x4 mat = Matrix4x4::identity();
  auto d = mat.determinant();
  EXPECT_TRUE(d == 1);
  mat = Matrix4x4(
      Vector4(1.0f, 1.0f, 1.0f, -1.0f), Vector4(1.0f, 1.0f, -1.0f, 1.0f),
      Vector4(1.0f, -1.0f, 1.0f, 1.0f), Vector4(-1.0f, 1.0f, 1.0f, 1.0f));
  d = mat.determinant();
  EXPECT_TRUE(d == -16);
}

TEST_F(Matrix4x4Test, Inverse) {
  using namespace temp::math;
  Matrix4x4 mat = Matrix4x4::identity();
  auto inv = mat.inversed();
  EXPECT_TRUE(inv == mat);
  mat = Matrix4x4(
      Vector4(1.0f, 1.0f, 1.0f, -1.0f), Vector4(1.0f, 1.0f, -1.0f, 1.0f),
      Vector4(1.0f, -1.0f, 1.0f, 1.0f), Vector4(-1.0f, 1.0f, 1.0f, 1.0f));
  inv = mat.inversed();
  EXPECT_TRUE(mat * inv == Matrix4x4::identity());
}