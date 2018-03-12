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
  mesh->load(true);
#if 0
  auto graphics_device = engine->graphicsDevice();
  Float32 vertices[] = {
      -1.0f, -1.0f, -1.0f, 0.0f,  //
      0.0f,  0.0f,  -1.0f, 0.0f,  //
      -1.0f, 1.0f,  -1.0f, 0.0f,  //
      0.0f,  0.0f,  -1.0f, 0.0f,  //
      1.0f,  -1.0f, -1.0f, 0.0f,  //
      0.0f,  0.0f,  -1.0f, 0.0f,  //
      1.0f,  1.0f,  -1.0f, 0.0f,  //
      0.0f,  0.0f,  -1.0f, 0.0f,  //

      1.0f,  -1.0f, -1.0f, 0.0f,  //
      1.0f,  0.0f,  0.0f,  0.0f,  //
      1.0f,  1.0f,  -1.0f, 0.0f,  //
      1.0f,  0.0f,  0.0f,  0.0f,  //
      1.0f,  -1.0f, 1.0f,  0.0f,  //
      1.0f,  0.0f,  0.0f,  0.0f,  //
      1.0f,  1.0f,  1.0f,  0.0f,  //
      1.0f,  0.0f,  0.0f,  0.0f,  //

      1.0f,  -1.0f, 1.0f,  0.0f,  //
      0.0f,  0.0f,  1.0f,  0.0f,  //
      1.0f,  1.0f,  1.0f,  0.0f,  //
      0.0f,  0.0f,  1.0f,  0.0f,  //
      -1.0f, -1.0f, 1.0f,  0.0f,  //
      0.0f,  0.0f,  1.0f,  0.0f,  //
      -1.0f, 1.0f,  1.0f,  0.0f,  //
      0.0f,  0.0f,  1.0f,  0.0f,  //

      -1.0f, -1.0f, 1.0f,  0.0f,  //
      -1.0f, 0.0f,  0.0f,  0.0f,  //
      -1.0f, 1.0f,  1.0f,  0.0f,  //
      -1.0f, 0.0f,  0.0f,  0.0f,  //
      -1.0f, -1.0f, -1.0f, 0.0f,  //
      -1.0f, 0.0f,  0.0f,  0.0f,  //
      -1.0f, 1.0f,  -1.0f, 0.0f,  //
      -1.0f, 0.0f,  0.0f,  0.0f,  //
  };
  graphics::VertexBufferDesc vb_desc;
  vb_desc.element_count = 2;
  vb_desc.element_descs[0].format = graphics::VertexFormat::kFloat32x4;
  vb_desc.element_descs[0].attribute = graphics::VertexAttribute::kPosition;
  vb_desc.element_descs[1].format = graphics::VertexFormat::kFloat32x4;
  vb_desc.element_descs[1].attribute = graphics::VertexAttribute::kNormal;
  vb_desc.size = sizeof(vertices);
  auto vb = graphics_device->createVertexBuffer(vb_desc, vertices);
  mesh->replaceVertexBuffer(vb);
  Float32 indices[] = {
      0, 1, 2, 3,  //
      3, 2,        //
      2, 3, 4, 5,  //
      5, 4,        //
      4, 5, 6, 7,  //
      7, 6,        //
      6, 7, 0, 1,  //
  };
  graphics::IndexBufferDesc ib_desc;
  ib_desc.format = graphics::IndexBufferFormat::kUInt16;
  ib_desc.primitive_type = graphics::PrimitiveType::kTriangleStrip;
  ib_desc.size = sizeof(indices);
  auto ib = graphics_device->createIndexBuffer(ib_desc, indices);
  mesh->replaceIndexBuffer(ib);
  mesh->save();
#endif
  app->setOnUpdateCallback([&engine]() { engine->update(); });
  auto exit_code = app->run();
  return exit_code;
}
