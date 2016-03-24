/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include <cassert>
#include "temp.h"

class TestResource : public temp::resource::ResourceBase<TestResource> {
    // friend class temp::resource::ResourceBase<Test>;
public:
    TestResource(const temp::system::Path &path) : ResourceBase(path) {}
private:
    virtual void loginImpl(){}
    virtual void logoutImpl(){}
};

class TestObj
{
public:
	explicit TestObj(const std::function<void(void)> &f){ f_ = f; }

	void func() {
		f_();
	}
	
private:
	std::function<void(void)> f_;
};

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
    temp::graphics::Device::SPtr device_;
    temp::system::ThreadPool::SPtr load_thread_;
    temp::system::ThreadPool::SPtr render_thread_;
    temp::system::ThreadPool::SPtr worker_threads_;
	temp::render::Renderer::SPtr renderer_;

public:
	TestObj *createTestObj(){ 
		auto test_private = [this](){ testPrivate(); };
		return new TestObj(test_private); 
	};

	void testPrivate() {
		std::cout << "testPrivate called!" << std::endl;
	}
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

    ConsoleLogger::initialize();

    setCurrentDirectory("../");
    ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());


    TestResource::initialize(load_thread_);
    auto res = TestResource::create("");

    window_ = Window::create();

    // レンダラクラスで処理すべき
    graphics::DeviceParameter devParam;
    devParam.load_thread = load_thread_;
    devParam.render_thread = render_thread_;
    devParam.worker_thread = worker_threads_;
    devParam.window = window_;
    device_ = graphics::Device::create(devParam);

    String clear_vs_source_path = "shader/glsl/clear_glsl.vert";
    std::ifstream ifs(clear_vs_source_path);
    if (ifs.fail()) {
        ConsoleLogger::error("Not found {0}!", clear_vs_source_path);
    }
    String clear_vs_source((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    graphics::VertexShader::SPtr clear_vs;
    auto createClearVs = [this, &clear_vs, &clear_vs_source](){
        clear_vs = device_->createVertexShaderFromSource(clear_vs_source);
    };
    auto future = load_thread_->pushJob(createClearVs);
    future.wait();

	renderer_ = render::Renderer::create(device_);
	auto camera = renderer_->createCamera();
}

void Test::term()
{
    using namespace temp;
    using namespace temp::system;

    device_ = nullptr;
    window_ = nullptr;

    load_thread_ = nullptr;
    render_thread_ = nullptr;
    worker_threads_ = nullptr;

    ConsoleLogger::terminate();
}

void Test::update() {
}

void Test::run() {
    using temp::system::Application;
    application_->run();
}

int main(/*int argc, char const* argv[]*/)
{
    Test test;
	auto obj = test.createTestObj();
	obj->func();
    test.run();
    
    return 0;
}
