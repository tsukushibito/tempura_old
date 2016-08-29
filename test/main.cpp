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
    ConsoleLogger::trace("Vector2::kUp = {0}", Vector2::kUp.ToString());
    ConsoleLogger::trace("Vector2::kDown = {0}", Vector2::kDown.ToString());
    ConsoleLogger::trace("Vector2::kLeft = {0}", Vector2::kLeft.ToString());
    ConsoleLogger::trace("Vector2::kRight = {0}", Vector2::kRight.ToString());

    ConsoleLogger::trace("-Vector3::kUp = {0}", (-Vector2::kUp).ToString());
    ConsoleLogger::trace("-Vector3::kDown = {0}", (-Vector2::kDown).ToString());
    ConsoleLogger::trace("-Vector3::kLeft = {0}", (-Vector2::kLeft).ToString());
    ConsoleLogger::trace("-Vector3::kRight = {0}", (-Vector2::kRight).ToString());

    auto v0 = Vector2(1.0f, 1.0f);
    auto v1 = Vector2(-1.0f, 1.0f);
    ConsoleLogger::trace("Vector2::dot(v0, v1) = {0}", Vector2::dot(v0, v1));

}

int main(/*int argc, char const* argv[]*/) {

    Test test;
    test.run();

    return 0;
}
