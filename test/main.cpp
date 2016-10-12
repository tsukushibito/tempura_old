/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include <cassert>
#include "temp.h"
// #include <OpenGL/gl3.h>

class Test {
public:
    Test();

    void init();
    void update();
    void term();

    void run();

    void testMath();

private:
    temp::system::Application::SPtr application_;
    temp::system::Window::SPtr window_;
    temp::system::ThreadPool::SPtr load_thread_;
    temp::system::ThreadPool::SPtr render_thread_;
    temp::system::ThreadPool::SPtr worker_threads_;
    temp::graphics::Device::SPtr device_;
    temp::render::Renderer::SPtr renderer_;
};

Test::Test() {
    using temp::system::Application;
    using temp::system::ThreadPool;

    load_thread_ = ThreadPool::create("Load", 1);
    render_thread_ = ThreadPool::create("Render", 1);
    worker_threads_ = ThreadPool::create("Worker", 3);

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

    ConsoleLogger::initialize();

    setCurrentDirectory("../../");
    ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());

    window_ = Window::create();

    graphics::DeviceParameter devParam;
    devParam.main_thread = application_->getMainThread();
    devParam.load_thread = load_thread_;
    devParam.render_thread = render_thread_;
    devParam.worker_thread = worker_threads_;
    devParam.window = window_;
    device_ = graphics::Device::create(devParam);
    auto blend_state = device_->createBlendState(graphics::BlendMode::None);
    auto depth_stencile_state =
        device_->createDepthStencileState(graphics::DepthStencileFunc::Always, graphics::DepthStencileFunc::Always);
    graphics::RasterizerDesc desc;
    desc.front_face = graphics::FrontFace::CounterClockWise;
    desc.fill_mode = graphics::FillMode::Fill;
    desc.cull_mode = graphics::CullingMode::CullingNone;
    auto rasterizer_state = device_->createRasterizerState(desc);
    String data;
    temp::Float32 vertics[][3] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
    temp::Int16 indics[] = { 0, 1, 2, };
    auto vertex_buffer = device_->createVertexBuffer(sizeof(vertics), vertics);
    auto index_buffer = device_->createIndexBuffer(sizeof(indics), indics);

    VertexShaderResource::initialize(load_thread_, device_);
    PixelShaderResource::initialize(load_thread_, device_);

    renderer_ = render::Renderer::create(device_);
    auto camera = renderer_->createCamera();

    testMath();
}

void Test::term() {
    using namespace temp;
    using namespace temp::system;
    using namespace temp::resource;

    renderer_ = nullptr;

    PixelShaderResource::terminate();
    VertexShaderResource::terminate();

    device_ = nullptr;
    window_ = nullptr;

    application_ = nullptr;

    load_thread_ = nullptr;
    render_thread_ = nullptr;
    worker_threads_ = nullptr;

    ConsoleLogger::terminate();
}

void Test::update() {
    auto future = render_thread_->pushJob([this]() {
        renderer_->renderAllViews();
        renderer_->swapBackBuffers();
    });
    future.wait();
}

void Test::run() {
    using temp::system::Application;
    application_->run();
}

void Test::testMath() {
    using namespace temp;
    using namespace temp::math;
    using temp::system::ConsoleLogger;
    ConsoleLogger::trace("Vector2::kUp = {0}", Vector2::kUp.toString());
    ConsoleLogger::trace("Vector2::kDown = {0}", Vector2::kDown.toString());
    ConsoleLogger::trace("Vector2::kLeft = {0}", Vector2::kLeft.toString());
    ConsoleLogger::trace("Vector2::kRight = {0}", Vector2::kRight.toString());

    ConsoleLogger::trace("-Vector3::kUp = {0}", (-Vector2::kUp).toString());
    ConsoleLogger::trace("-Vector3::kDown = {0}", (-Vector2::kDown).toString());
    ConsoleLogger::trace("-Vector3::kLeft = {0}", (-Vector2::kLeft).toString());
    ConsoleLogger::trace("-Vector3::kRight = {0}", (-Vector2::kRight).toString());

    auto v0 = Vector2(1.0f, 1.0f);
    auto v1 = Vector2(-1.0f, 1.0f);
    ConsoleLogger::trace("Vector2::dot(v0, v1) = {0}", Vector2::dot(v0, v1));

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
    
    Matrix44 mat(RowOrder(),
        Vector4( 2,  0,  1,  1), 
        Vector4( 1,  1,  2,  3),
        Vector4(-1,  2,  0,  0),
        Vector4( 1,  0,  1, 10));
	ConsoleLogger::trace("\n{0}", mat.toString());
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
    //TEMP_ASSERT(transformed == vec4, "");

    auto mat2 = mat * id;
    TEMP_ASSERT(mat == mat2, "");

    auto tmat = mat.transpose();
	ConsoleLogger::trace("\n{0}", tmat.toString());

    auto r = std::sin(math::pi()/2.0f);
    ConsoleLogger::trace("sin(PI) = {0}", r);

    Quaternion quat(Vector3(math::pi()/2.0f, 0.0f, 0.0f));
    auto abs = quat.absolute();
    ConsoleLogger::trace("quat abs = {0}", abs);
    auto euler = quat.toEulerAnglesZXY();
    ConsoleLogger::trace("euler = {0}", euler.toString());

    Vector3 forward = Vector3::kForward;
    Quaternion rot(Vector3(math::pi()/2.0f, math::pi()/2.0f, math::pi()));
    auto rotated = rot.rotateVector3(forward);
    ConsoleLogger::trace("rotated = {0}", rotated.toString());
    auto rotMat = rot.toRotateMatrix();
    auto rotated2 = Vector4(forward[0], forward[1], forward[2], 0) * rotMat;
    ConsoleLogger::trace("rotated2 = {0}", rotated2.toString());

	Transform t1;
	ConsoleLogger::trace("t1 = \n{0}", t1.toString());
	ConsoleLogger::trace("t1.Matrix = \n{0}", t1.toMatrix().toString());

	Transform t2(Vector3(2.0f, 3.0f, 1.0f), Quaternion(Vector3(pi()/2, 0, 0)), Vector3(1, 1, 1));
	Transform t3(Vector3(1.0f, 2.0f, 4.0f), Quaternion(Vector3(0, pi()/2, 0)), Vector3(1, 1, 1));

	auto t12 = t1 * t2;
	ConsoleLogger::trace("t12 = \n{0}", t12.toString());

	auto t23 = t2 * t3;
	ConsoleLogger::trace("t23 = \n{0}", t23.toString());
}

int main(/*int argc, char const* argv[]*/) {

    Test test;
    test.run();

    return 0;
}
