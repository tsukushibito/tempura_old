/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include "temp.h"

#include "temp/math_exp/vector.h"

class Test {
   public:
    Test();

    void init();
    void update();
    void term();

    void run();

    void testExp();
    void testResource();
    void testMath();
    void testRenderer();

   private:
    temp::system::Application::SPtr application_;
    temp::system::Window::SPtr window_;
    temp::system::ThreadPool::SPtr load_thread_;
    temp::system::ThreadPool::SPtr render_thread_;
    temp::system::ThreadPool::SPtr worker_threads_;
    temp::graphics_::Device::SPtr device_;
    temp::render_old::Renderer::SPtr renderer_;
    temp::render_old::Camera::SPtr camera_;
};

Test::Test() {
    using temp::system::Application;
    using temp::system::ThreadPool;

    load_thread_ = ThreadPool::makeUnique("Load", 1);
    render_thread_ = ThreadPool::makeUnique("Render", 1);
    worker_threads_ = ThreadPool::makeUnique("Worker", 3);

    application_ = Application::create();
    application_->setInitializeFunction(std::bind(&Test::init, this));
    application_->setUpdateFunction(std::bind(&Test::update, this));
    application_->setTerminateFunction(std::bind(&Test::term, this));
}

void Test::init() {
    using namespace temp;
    using namespace temp::system;
    using namespace temp::graphics_;
    using namespace temp::resource_old;
    using namespace temp::render_old;

    Logger::initialize();

    setCurrentDirectory("../../");

    Logger::trace("Current directory : {}", getCurrentDirectory().absolute());

    window_ = Window::makeUnique();
    device_ = Device::makeShared(window_->nativeHandle());

    temp::resource_old::initialize(load_thread_, device_);

    DrawAreaSize draw_area_size = {window_->width(), window_->height()};
    Path shader_directory("shader");
    renderer_ = Renderer::makeUnique(worker_threads_, render_thread_, device_,
                                     draw_area_size, shader_directory);

    RenderTargetDesc rt_desc;
    rt_desc.format = RenderTargetFormat::kRGBA32;
    rt_desc.width = window_->width();
    rt_desc.height = window_->height();
    auto render_target = renderer_->createRenderTarget(rt_desc);
    
    camera_ = renderer_->createCamera(render_target);

    renderer_->setMainCamera(camera_);

    // testExp();

    // testResource();

    // testMath();
}

void Test::term() {
    using namespace temp;
    using namespace temp::system;
    using namespace temp::resource_old;

    camera_ = nullptr;
    renderer_ = nullptr;

    temp::resource_old::terminate();

    window_ = nullptr;

    application_ = nullptr;

    load_thread_ = nullptr;
    render_thread_ = nullptr;
    worker_threads_ = nullptr;

    Logger::terminate();
}

void Test::update() { 
    temp::system::Timer timer;
    renderer_->render();
    auto ms = timer.milliseconds();
    std::cout << "Delta time : " << ms << " ms" << std::endl;
}

void Test::run() {
    using temp::system::Application;
    application_->run();
}

void Test::testExp() {
    using namespace temp;
    using namespace temp::math_exp;
}

void Test::testResource() {
    using temp::resource_old::Texture;
    using temp::resource_old::Mesh;
    using temp::resource_old::VertexShader;
    using temp::system::Path;
    using namespace temp::math;

#if 0
#else

    // テストデータ
    temp::UInt16 cube_faces[36] = {
        0, 1, 2, 0, 2, 3, 3, 2, 6, 3, 6, 7, 7, 6, 5, 7, 5, 4,
        4, 5, 1, 4, 1, 0, 0, 3, 7, 0, 7, 4, 2, 1, 5, 2, 5, 6,
    };

    Vector4 cube_vertices[8] = {
        {1, 1, 1, 1},  {1, 1, -1, 1},  {-1, 1, -1, 1},  {-1, 1, 1, 1},
        {1, -1, 1, 1}, {1, -1, -1, 1}, {-1, -1, -1, 1}, {-1, -1, 1, 1},
    };

    {
        using namespace temp::graphics_;
        using namespace temp::resource_old;

        auto mesh = Mesh::create(Path("resource/mesh/test.tmsh"));

        // テストデータ
        auto device = Mesh::graphicsDevice();

        IndexBufferDesc ib_desc;
        ib_desc.format = IndexBufferFormat::kUInt16;
        ib_desc.primitive_type = PrimitiveType::kTriangleList;
        ib_desc.size = sizeof(cube_faces);
        auto ib = device->createIndexBuffer(ib_desc, cube_faces);

        mesh->replaceIndexBuffer(ib);

        VertexBufferDesc vb_desc;
        vb_desc.attribute = VertexAttribute::kPosition;
        vb_desc.format = VertexBufferFormat::kFloat32x4;
        vb_desc.size = sizeof(cube_vertices);
        auto vb = device->createVertexBuffer(vb_desc, cube_vertices);

        Mesh::VertexBufferTable vb_table;
        vb_table[VertexAttribute::kPosition] = vb;
        mesh->replaceVertexBufferTable(vb_table);

        mesh->save();
    }
#endif

    do {
        using namespace temp;
        auto mesh = Mesh::create(Path("resource/mesh/test.tmsh"));
        mesh->load();

        auto ib = mesh->indexBuffer();
        auto data = ib->data();
        UInt16* p = reinterpret_cast<UInt16*>(&data[0]);
        if (memcmp(p, cube_faces, data.size()) != 0) {
            system::Logger::error("Failed to Mesh save and load!");
        }
        printf("***** cube_faces *****\n");
        printf("{\n");
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 16; ++j) {
                printf("%d, ", cube_faces[16 * i + j]);
            }
            printf("\n");
        }
        printf("}\n");
        printf("***** ********** *****\n");
        printf("\n");
        printf("***** loaded ib data *****\n");
        printf("{\n");
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 16; ++j) {
                printf("%d, ", p[16 * i + j]);
            }
            printf("\n");
        }
        printf("}\n");
        printf("***** ********** *****\n");

        auto vb_table = mesh->vertexBufferTable();
        auto key_value = vb_table.find(graphics_::VertexAttribute::kPosition);
        if (key_value == vb_table.end()) break;

        auto vb = key_value->second;
        data = vb->data();
        Vector4* vertics = reinterpret_cast<Vector4*>(&data[0]);

        if (memcmp(vertics, cube_vertices, data.size()) != 0) {
            system::Logger::error("Failed to Mesh save and load!");
        }

        printf("***** cube_vertices *****\n");
        for (int i = 0; i < 8; ++i) {
            printf("%s\n", cube_vertices[i].toString().c_str());
        }
        printf("***** ********** *****\n");
        printf("\n");
        printf("***** cube_vertices *****\n");
        for (int i = 0; i < 8; ++i) {
            printf("%s\n", vertics[i].toString().c_str());
        }
        printf("***** ********** *****\n");

    } while (false);

    {
        auto vs = VertexShader::create(Path("shader/glsl/test/glsl.vert"));
        vs->load();
    }
}

void Test::testMath() {
    using namespace temp;
    using namespace temp::math;
    using temp::system::Logger;
    Logger::trace("Vector2::kUp = {0}", Vector2::kUp.toString());
    Logger::trace("Vector2::kDown = {0}", Vector2::kDown.toString());
    Logger::trace("Vector2::kLeft = {0}", Vector2::kLeft.toString());
    Logger::trace("Vector2::kRight = {0}", Vector2::kRight.toString());

    Logger::trace("-Vector3::kUp = {0}", (-Vector2::kUp).toString());
    Logger::trace("-Vector3::kDown = {0}", (-Vector2::kDown).toString());
    Logger::trace("-Vector3::kLeft = {0}", (-Vector2::kLeft).toString());
    Logger::trace("-Vector3::kRight = {0}", (-Vector2::kRight).toString());

    auto v0 = Vector2(1.0f, 1.0f);
    auto v1 = Vector2(-1.0f, 1.0f);
    Logger::trace("Vector2::dot(v0, v1) = {0}", Vector2::dot(v0, v1));

    Vector3 x = Vector3::kRight;
    Vector3 nx = Vector3::kLeft;
    auto z = x + nx;

    Vector3 vec3(3, 4, 5);
    Vector3 vec3xyz = vec3.xyz();
    Vector3 vec3xzy = vec3.xzy();
    Vector3 vec3yxz = vec3.yxz();
    Vector3 vec3yzx = vec3.yzx();
    Vector3 vec3zxy = vec3.zxy();
    Vector3 vec3zyx = vec3.zyx();
    TEMP_ASSERT(vec3xyz == Vector3(3, 4, 5), "");
    TEMP_ASSERT(vec3xzy == Vector3(3, 5, 4), "");
    TEMP_ASSERT(vec3yxz == Vector3(4, 3, 5), "");
    TEMP_ASSERT(vec3yzx == Vector3(4, 5, 3), "");
    TEMP_ASSERT(vec3zxy == Vector3(5, 3, 4), "");
    TEMP_ASSERT(vec3zyx == Vector3(5, 4, 3), "");
    TEMP_ASSERT(Vector3(3, 4, 0).lengthSquared() == 25, "");
    TEMP_ASSERT(Vector3(3, 4, 0).length() == 5, "");
    auto norm = Vector3(3, 3, 3).normalized();
    auto angle = Vector3::angle(Vector3(1, 0, 0), Vector3(0, 1, 0));
    TEMP_ASSERT(angle, "");
    auto axisZ = Vector3::cross(Vector3(1, 0, 0), Vector3(0, 1, 0));
    TEMP_ASSERT(axisZ.x() == 0 && axisZ.y() == 0 && axisZ.z() == 0, "");
    auto zero = Vector3::dot(Vector3(1, 0, 0), Vector3(0, 1, 0));
    TEMP_ASSERT(zero == 0, "");

    Matrix44 mat(RowOrder(), Vector4(2, 0, 1, 1), Vector4(1, 1, 2, 3),
                 Vector4(-1, 2, 0, 0), Vector4(1, 0, 1, 10));
    Logger::trace("\n{0}", mat.toString());
    auto det = mat.determinant();
    TEMP_ASSERT(det == -23, "");
    auto id = Matrix44::kIdentity;
    auto inv = id.inverse();
    TEMP_ASSERT(*inv == id, "");

    Vector4 vec4(1, 3, 4, 1);
    auto transformed = vec4 * id;
    TEMP_ASSERT(transformed == vec4, "");

    inv = mat.inverse();
    transformed = vec4 * mat * (*inv);
    transformed = vec4 * (mat * (*inv));
    // TEMP_ASSERT(transformed == vec4, "");

    auto mat2 = mat * id;
    TEMP_ASSERT(mat == mat2, "");

    auto tmat = mat.transpose();
    Logger::trace("\n{0}", tmat.toString());

    auto r = std::sin(math::pi() / 2.0f);
    Logger::trace("sin(PI) = {0}", r);

    Quaternion quat(Vector3(math::pi() / 2.0f, 0.0f, 0.0f));
    auto abs = quat.absolute();
    Logger::trace("quat abs = {0}", abs);
    auto euler = quat.toEulerAnglesZXY();
    Logger::trace("euler = {0}", euler.toString());

    Vector3 forward = Vector3::kForward;
    Quaternion rot(Vector3(math::pi() / 2.0f, math::pi() / 2.0f, math::pi()));
    auto rotated = rot.rotateVector3(forward);
    Logger::trace("rotated = {0}", rotated.toString());
    auto rotMat = rot.toRotateMatrix();
    auto rotated2 = Vector4(forward[0], forward[1], forward[2], 0) * rotMat;
    Logger::trace("rotated2 = {0}", rotated2.toString());

    Transform t1;
    Logger::trace("t1 = \n{0}", t1.toString());
    Logger::trace("t1.Matrix = \n{0}", t1.toMatrix().toString());

    Transform t2(Vector3(2.0f, 3.0f, 1.0f), Quaternion(Vector3(pi() / 2, 0, 0)),
                 Vector3(1, 1, 1));
    Transform t3(Vector3(1.0f, 2.0f, 4.0f), Quaternion(Vector3(0, pi() / 2, 0)),
                 Vector3(1, 1, 1));

    auto t12 = t1 * t2;
    Logger::trace("t12 = \n{0}", t12.toString());

    auto t23 = t2 * t3;
    Logger::trace("t23 = \n{0}", t23.toString());
}

void Test::testRenderer() {}

int main(/*int argc, char const* argv[]*/) {
    using temp::system::Logger;

    Test test;
    test.run();

    return 0;
}
