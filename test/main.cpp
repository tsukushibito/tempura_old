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

class Test {
   public:
    Test();

    void init();
    void update();
    void term();

    void run();

    void testResource();
    void testMath();

   private:
    temp::system::Application::SPtr application_;
    temp::system::Window::SPtr window_;
    temp::system::ThreadPool::SPtr load_thread_;
    temp::system::ThreadPool::SPtr render_thread_;
    temp::system::ThreadPool::SPtr worker_threads_;
    temp::graphics::Device::SPtr device_;
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
    using namespace temp::graphics;
    using namespace temp::resource;
    using namespace temp::render;

    Logger::initialize();

    setCurrentDirectory("../../");
    Logger::trace("Current directory : {}", getCurrentDirectory().absolute());

    window_ = Window::makeUnique();
    device_ = Device::makeShared(window_->nativeHandle());
    TextureDesc texDesc(TextureFormat::kRGBA32, 128, 128, 0);

    ShaderCode vscode;
    {
        std::ifstream ifs("shader/glsl/clear_glsl.vert");
        std::istreambuf_iterator<Char> it(ifs);
        std::istreambuf_iterator<Char> last;
        vscode.code_ = String(it, last);
    }

    ShaderCode pscode;
    {
        std::ifstream ifs("shader/glsl/clear_glsl.frag");
        std::istreambuf_iterator<Char> it(ifs);
        std::istreambuf_iterator<Char> last;
        pscode.code_ = String(it, last);
    }

    {
        auto tex1 = device_->createTexture(texDesc);
        auto tex2 = device_->createTexture(texDesc);
        auto tex3 = device_->createTexture(texDesc);
        auto vshader = device_->createVertexShader(vscode);
        auto pshader = device_->createPixelShader(pscode);
    }

    testResource();

    testMath();
}

void Test::term() {
    using namespace temp;
    using namespace temp::system;
    using namespace temp::resource;

    window_ = nullptr;

    application_ = nullptr;

    load_thread_ = nullptr;
    render_thread_ = nullptr;
    worker_threads_ = nullptr;

    Logger::terminate();
}

void Test::update() {
    auto future = render_thread_->pushJob([this]() {});
    future.wait();
}

void Test::run() {
    using temp::system::Application;
    application_->run();
}

void Test::testResource() {
    using temp::resource::Texture;
    using temp::resource::Mesh;
    using temp::system::Path;
    using namespace temp::math;

    Texture::initialize(load_thread_, device_);
    Mesh::initialize(load_thread_, device_);

    {
        // テストデータ
        Vector4 cube_vertices[8] = {
            {1, 1, 1, 1},  {1, 1, -1, 1},  {-1, 1, -1, 1},  {-1, 1, 1, 1},
            {1, -1, 1, 1}, {1, -1, -1, 1}, {-1, -1, -1, 1}, {-1, -1, 1, 1},
        };
        temp::ByteData cube_vertex_data(sizeof(cube_vertices));
        memcpy(&cube_vertex_data[0], cube_vertices, sizeof(cube_vertices));

        using namespace temp::graphics;
        VertexBufferDesc vb_desc;

        vb_desc.format = VertexBufferFormat::kFloat32x4;
        vb_desc.attribute = VertexAttribute::kPosition;
        vb_desc.size = sizeof(cube_vertices);
        auto vb = device_->createVertexBuffer(vb_desc, cube_vertex_data);
        
        temp::UInt16 cube_faces[36] = {
            0, 1, 2, 0, 2, 3, 3, 2, 6, 3, 6, 7, 7, 6, 5, 7, 5, 4,
            4, 5, 1, 4, 1, 0, 0, 3, 7, 0, 7, 4, 2, 1, 5, 2, 5, 6,
        };
        temp::ByteData cube_face_data(sizeof(cube_faces));
        memcpy(&cube_face_data[0], cube_faces, sizeof(cube_faces));
        
        IndexBufferDesc ib_desc;
        ib_desc.format = IndexBufferFormat::kUInt16;
        ib_desc.size = sizeof(cube_faces);
        ib_desc.primitive_type = PrimitiveType::kTriangleList;
        auto ib = device_->createIndexBuffer(ib_desc, cube_face_data);

        temp::resource::Mesh::VertexBufferTable vb_table;
        vb_table[VertexAttribute::kPosition] = vb;
        temp::resource::tmsh::Tmsh tmsh(vb_table, ib);        

        auto tmsh_byte_data = tmsh.byteData();

        std::ofstream ofs("resource/mesh/test.tmsh");
    }

    {
        auto mesh = Mesh::create(Path("resource/mesh/test.tmsh"));
        mesh->load();
    }
    Texture::terminate();
    Mesh::terminate();
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
    auto axisZ = Vector3::cross(Vector3(1, 0, 0), Vector3(0, 1, 0));
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

int main(/*int argc, char const* argv[]*/) {
    using temp::system::Logger;

    Test test;
    test.run();

    return 0;
}
