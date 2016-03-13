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


class Test {
public:
	Test();

	void init();
	void update();
	void term();

	void run();

private:
	temp::system::Window::SPtr window_;
	temp::graphics::Device::SPtr device_;
};

Test::Test()
{
	using temp::system::Application;
	Application::getInstance().setInitializeFunction(std::bind(&Test::init, this));
	Application::getInstance().setUpdateFunction(std::bind(&Test::update, this));
	Application::getInstance().setTerminateFunction(std::bind(&Test::term, this));
}

void Test::init()
{
    using namespace temp;
    using namespace temp::system;

	ConsoleLogger::initialize();

	setCurrentDirectory("../");
	ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());

	auto load_thread = ThreadPool::create("Load", 1);
	auto render_thread = ThreadPool::create("Render", 1);
	auto worker_thread = ThreadPool::create("Worker", 1);

	TestResource::initialize(load_thread);
	auto res = TestResource::create("");

    window_ = Window::create();

	graphics::DeviceParameter devParam;
	devParam.load_thread = load_thread;
	devParam.render_thread = render_thread;
	devParam.worker_thread = worker_thread;
	devParam.window = window_;
	device_ = graphics::Device::create(devParam);
	// device->createVertexShaderFromSource(String());
}

void Test::term()
{
    using namespace temp;
    using namespace temp::system;

	device_ = nullptr;
	window_ = nullptr;

	ConsoleLogger::terminate();
}

void Test::update()
{
}

void Test::run() {
	using temp::system::Application;
    Application::getInstance().run();
}

int main(int argc, char const* argv[])
{
	Test test;
	test.run();
    
    return 0;
}
