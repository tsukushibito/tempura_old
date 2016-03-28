/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include <cassert>
#include "temp.h"

class Test {
public:
    Test();

    void init();
    void update();
    void term();

    void run();

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

void Test::init()
{
    using namespace temp;
    using namespace temp::system;
	using namespace temp::graphics;
	using namespace temp::resource;
	using namespace temp::render;

    ConsoleLogger::initialize();

    setCurrentDirectory("../");
    ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());

    window_ = Window::create();

    graphics::DeviceParameter devParam;
	devParam.main_thread = application_->getMainThread();
    devParam.load_thread = load_thread_;
    devParam.render_thread = render_thread_;
    devParam.worker_thread = worker_threads_;
    devParam.window = window_;
    device_ = graphics::Device::create(devParam);

    
    VertexShaderResource::initialize(load_thread_, device_);
    PixelShaderResource::initialize(load_thread_, device_);

	renderer_ = render::Renderer::create(device_);
	auto camera = renderer_->createCamera();
}

void Test::term()
{
    using namespace temp;
    using namespace temp::system;

	renderer_ = nullptr;

    device_ = nullptr;
    window_ = nullptr;

    load_thread_ = nullptr;
    render_thread_ = nullptr;
    worker_threads_ = nullptr;

    ConsoleLogger::terminate();
}

void Test::update() {
	auto future = render_thread_->pushJob([this]() { renderer_->renderAllViews(); renderer_->swapBackBuffers(); });
	future.wait();
}

void Test::run() {
    using temp::system::Application;
    application_->run();
}

int main(/*int argc, char const* argv[]*/)
{
    Test test;
	test.run();

    return 0;
}
